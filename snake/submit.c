#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h> 

#include "menu.h"
#include "game_modes.h"
#include "buttons.h"
#include "draw_px_or_char.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "submit.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void submit(SnakeBig* snake) {

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;

    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    int letter_button = 1;
    int ptr = 0;
    int curr_green = (((r>>8)&0xff));
    int prev_green = (((r>>8)&0xff));

    char alphabet[26];

    for (int i = 0; i < 26; i++) {
        alphabet[i] = 'A' + i;
    }

    char name[20];
    name[0] = '\0';
    int name_len = 0;

    while (1) {
        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        curr_green = (((r>>8)&0xff));

        letter_button = modify_while_rotating(curr_green, prev_green, letter_button, 28);

        make_buttons();

        switch(letter_button) {
            case 1:
                draw_outer_lines(10, 5, 80, 55);
                break;
            case 2:
                draw_outer_lines(85, 5, 155, 55);
                break;
            case 3:
                draw_outer_lines(160, 5, 230, 55);
                break;
            case 4:
                draw_outer_lines(235, 5, 305, 55);
                break;
            case 5:
                draw_outer_lines(310, 5, 380, 55);
                break;
            case 6:
                draw_outer_lines(385, 5, 455, 55);
                break;
            case 7:
                draw_outer_lines(10, 60, 80, 110);
                break;
            case 8:
                draw_outer_lines(85, 60, 155, 110);
                break;
            case 9:
                draw_outer_lines(160, 60, 230, 110);
                break;
            case 10:
                draw_outer_lines(235, 60, 305, 110);
                break;
            case 11:
                draw_outer_lines(310, 60, 380, 110);
                break;
            case 12:
                draw_outer_lines(385, 60, 455, 110);
                break;
            case 13:
                draw_outer_lines(10, 115, 80, 155);
                break;
            case 14:
                draw_outer_lines(85, 115, 155, 155);
                break;
            case 15:
                draw_outer_lines(160, 115, 230, 155);
                break;
            case 16:
                draw_outer_lines(235, 115, 305, 155);
                break;
            case 17:
                draw_outer_lines(310, 115, 380, 155);
                break;
            case 18:
                draw_outer_lines(385, 115, 455, 155);
                break;
            case 19:
                draw_outer_lines(10, 160, 80, 210);
                break;
            case 20:
                draw_outer_lines(85, 160, 155, 210);
                break;
            case 21:
                draw_outer_lines(160, 160, 230, 210);
                break;
            case 22:
                draw_outer_lines(235, 160, 305, 210);
                break;
            case 23:
                draw_outer_lines(310, 160, 380, 210);
                break;
            case 24:
                draw_outer_lines(385, 160, 455, 210);
                break;
            case 25:
                draw_outer_lines(10, 225, 80, 265);
                break;
            case 26:
                draw_outer_lines(85, 225, 155, 265);
                break;
            case 27:
                draw_outer_lines(160, 225, 340, 265);
                break;
            case 28:
                draw_outer_lines(345, 225, 455, 265);
            default:
                break;
        }

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    
        if ((r&0x7000000)!=0) {

            if (letter_button == 27 && name_len > 0) {
                name[name_len - 1] = '\0';
                name_len = name_len - 1;
                printf("%s\n", name);
            } else if (letter_button == 28) {
                save_score(name, snake->lenght);
                break;
            
            } else if (name_len < 20) {
                name[name_len] = alphabet[letter_button - 1];
                name_len++;
                name[name_len] = '\0';
                printf("%s\n", name);
            } 
        }
        
        for (ptr = 0; ptr < 320*480 ; ptr++) {
            fb[ptr]=0u;
        } 
        prev_green = curr_green;
    }
}

void make_buttons() {
    char c = 'A';
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            char str[2];
            sprintf(str, "%c", c);
            draw_button(10 + j * 75, 5 + i * 55, 80 + j * 75, 55 + i * 55);
            write_text(30 + j * 75, 5 + i * 55, str, 0x0010, 3, 0);
            c++;
        }
    }

    draw_button(10, 225, 80, 265);
    write_text(30, 225, "Y", 0x0010, 3, 0);
    draw_button(85, 225, 155, 265);
    write_text(105, 225, "Z", 0x0010, 3, 0);
    
    draw_button(160, 225, 340, 265);
    write_text(165, 225, "DELETE", 0x0010, 3, 20);

    draw_button(345, 225, 455, 265);
    write_text(345, 225, "DONE", 0x0010, 3, 20);
}

void save_score(char name[], int score) {
    FILE *file = fopen("scores.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: file coulnd be opened on line %d\n", __LINE__);
        exit(-1);
    }
    fprintf(file, "%s, with score %d\n", name, score);

    fclose(file);
}
