#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

#include "collisions.h"
#include "menu.h"
#include "buttons.h"
#include "draw_px_or_char.h"
#include "food_maker.h"
#include "snake_prop.h"
#include "singleplayer.h"
#include "multiplayer.h"
#include "end_state.h"
#include "submit.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void init_screen_state(SnakeBig* loser_snake, SnakeBig* winner_snake, bool multiplayer) {
    int ptr = 0;
    // Blackscreen
    for (int i = 0; i < 320 ; i++) {
        for (int j = 0; j < 480 ; j++) {
        int c = 0;
        fb[ptr]=c;
        parlcd_write_data(parlcd_mem_base, fb[ptr++]);
        }
    }

    if (multiplayer) {
        draw_died_screen_multi(loser_snake, winner_snake);
    } else {
        draw_died_screen_single(loser_snake);
    }
}

void draw_died_screen_single(SnakeBig* big_snake) {
    char* message = NULL;
    char score[20];

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;

    switch (big_snake->color) {
        case 0x7ff:
            message = "Blue died";
            break;
        case 0xF000:
            message = "Red  died";
            break;
        default:
            break;
    }
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    int end_state_button = 1;
    int ptr = 0;
    int curr_green = (((r>>8)&0xff));
    int prev_green = (((r>>8)&0xff));

    while (1) {
        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        curr_green = (((r>>8)&0xff));
        end_state_button = modify_while_rotating(curr_green, prev_green, end_state_button, 2);

        write_text(97, 30, message, big_snake->color, 4, 25);
        sprintf(score, "Your score is %d", big_snake->lenght);
        write_text(50, 90, score, big_snake->color, 3, 20);

        draw_button(110, 150, 370, 200);
        write_text(120, 155, "TO MENU", 0xF000, 3, 25);

        draw_button(110, 220, 370, 270);
        write_text(135, 225, "SUBMIT", 0xF000, 3, 25);

        switch(end_state_button) {
            case 1:
                draw_outer_lines(110, 150, 370, 200);
                break;
            case 2:
                draw_outer_lines(110, 220, 370, 270);
                break;
            default:
                break;
        }

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    
        if ((r&0x7000000)!=0) {
            clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
            if (end_state_button == 1) {
                break;
            } else if (end_state_button == 2) {
                submit(big_snake);
            }
        }
        
        for (ptr = 0; ptr < 320*480 ; ptr++) {
            fb[ptr]=0u;
        } 
        prev_green = curr_green;
    }
}

void draw_died_screen_multi(SnakeBig* loser_snake, SnakeBig* winner_snake) {
    char* message = NULL;
    char blue_score[20];
    char red_score[20];

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;

    switch (loser_snake->color) {
        case 0x7ff:
            message = "Red  snake won";
            break;
        case 0xF000:
            message = "Blue snake won";
            break;
        default:
            break;
    }

    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    int end_state_button = 1;
    int ptr = 0;
    int curr_green = (((r>>8)&0xff));
    int prev_green = (((r>>8)&0xff));

    while (1) {
        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        curr_green = (((r>>8)&0xff));
        end_state_button = modify_while_rotating(curr_green, prev_green, end_state_button, 2);

        write_text(10, 30, message, winner_snake->color, 4, 25);
        sprintf(blue_score, "Winner score: %d", winner_snake->lenght);
        write_text(40, 90, blue_score, winner_snake->color, 2, 15);
        sprintf(red_score, "Loser score: %d", loser_snake->lenght);
        write_text(40, 120, red_score, winner_snake->color, 2, 15);

        draw_button(110, 170, 370, 220);
        write_text(120, 175, "TO MENU", 0xF000, 3, 25);

        draw_button(110, 240, 370, 290);
        write_text(135, 245, "SUBMIT", 0xF000, 3, 25);

        switch(end_state_button) {
            case 1:
                draw_outer_lines(110, 170, 370, 220);
                break;
            case 2:
                draw_outer_lines(110, 240, 370, 290);
                break;
            default:
                break;
        }

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    
        if ((r&0x7000000)!=0) {
            clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
            if (end_state_button == 1) {
                break;
            } else if (end_state_button == 2) {
                //TODO
            }
        }
        
        for (ptr = 0; ptr < 320*480 ; ptr++) {
            fb[ptr]=0u;
        } 
        prev_green = curr_green;
    }
}
