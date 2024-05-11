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


extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void draw_died_screen(SnakeBig* Bigsnake);

void init_screen_state(SnakeBig* Bigsnake) {
    int ptr = 0;

    for (int i = 0; i < 320 ; i++) {
        for (int j = 0; j < 480 ; j++) {
        int c = 0;
        fb[ptr]=c;
        parlcd_write_data(parlcd_mem_base, fb[ptr++]);
        }
    }

    draw_died_screen(Bigsnake);

}

void draw_died_screen(SnakeBig* Bigsnake) {
    char* message = NULL;
    char back_to_menu[] = "MENU";

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;

    switch (Bigsnake->color) {
        case 0x7ff:
            message = "Blue died";
            break;
        case 0xF000:
            message = "Red  died";
            break;
        default:
            break;
    }

    while (1) {
        int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        write_text(97, 90, message, Bigsnake->color, 4, 25);

        draw_button(140, 200, 340, 270);

        write_text(167, 205, back_to_menu, 0xF000, 4, 25);

        draw_outer_lines(140, 200, 340, 270);



        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (int ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }

         if ((r&0x7000000)!=0) {
            clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
            break;
        }


        
    }


}