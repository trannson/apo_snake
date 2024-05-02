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
#include "buttons.h"
#include "draw_px_or_char.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "game_modes.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

int show_game_modes() {

    // There will be 4 modes
    int ret = 1;

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;
    int ptr;

    /*
    TEXTS PROPERTIES
    Here are defined properties for texts, that will display on buttons
    ********************************************************************************
    */
    // Single text
    int single_x = 145;
    int single_y1 = 10;
    int single_y2 = 90;
    char single_txt[] = "SINGLE";
    unsigned short single_clr = 0xF000;

    // Classic text
    int classic_x = 125;
    int classic_y1 = 45;
    int classic_y2 = 205;
    char classic_txt[] = "CLASSIC";
    unsigned short classic_clr = 0xF000;

    // Multiplayer text
    int multi_x = 160;
    int multi_y1 = 170;
    int multi_y2 = 250;
    char multi_txt[] = "MULTI";
    unsigned short multi_clr = 0xF000; 

    // Time rush text
    int timerush_x = 110;
    int timerush_y1 = 125;
    int timerush_y2 = 285;
    char timerush_txt[] = "TIMERUSH";
    unsigned short timerush_clr = 0xF000;

    int offset = 25;
    
    /*
    END OF TEXT PROPERTIES
    ********************************************************************************
    */

    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // These two store value of the green knob
    int curr_green = (((r>>8)&0xff));
    int prev_green = (((r>>8)&0xff));

    int gmode_button = 1;

    bool gmode_running = true;

    while(gmode_running) {

        /*
        Drawing buttons with their texts
        ********************************************************************************
        */
        // draw_button(40, 50, 220, 120); 
        // draw_button(240, 50, 420, 120);
        // draw_button(40, 230, 220, 300);
        // draw_button(240, 230, 420, 300);

        draw_button(100, 10, 380, 80); 
        draw_button(100, 90, 380, 160);
        draw_button(100, 170, 380, 240); 
        draw_button(100, 250, 380, 320);
        
        // Single classic
        write_text(single_x, single_y1, single_txt, single_clr, 2, offset);
        write_text(classic_x, classic_y1, classic_txt, classic_clr, 2, offset);

        // Single time rush
        write_text(single_x, single_y2, single_txt, single_clr, 2, offset);
        write_text(timerush_x, timerush_y1, timerush_txt, timerush_clr, 2, offset);

        // Multiplayer classic
        write_text(multi_x, multi_y1, multi_txt, multi_clr, 2, offset);
        write_text(classic_x, classic_y2, classic_txt, classic_clr, 2, offset);

        // Multiplayer time rush
        write_text(multi_x, multi_y2, multi_txt, multi_clr, 2, offset);
        write_text(timerush_x, timerush_y2, timerush_txt, timerush_clr, 2, offset);

        /*
        End of drawing buttons with their texts
        ********************************************************************************
        */

        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        curr_green = (((r>>8)&0xff)); // green knob

        gmode_button = modify_while_rotating(curr_green, prev_green, gmode_button, 4);

        // Drawing outer lines around the button the cursor is currently on
        switch (gmode_button)
        {
        case 1:
            draw_outer_lines(100, 10, 380, 80);      
            break;
        case 2:
            draw_outer_lines(100, 90, 380, 160);
            break;
        case 3:
            draw_outer_lines(100, 170, 380, 240);
            break;
        case 4:
            draw_outer_lines(100, 250, 380, 320);
            break;
        }

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }

        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

        // Clearing the screen (setting all pixels to black)
        for (ptr = 0; ptr < 320*480 ; ptr++) {
            fb[ptr]=0u;
        } 

        // If green knob pressed
        if ((r&0x7000000)!=0) {
            switch(gmode_button) {
                case 1:
                    ret = 1;
                    break;
                case 2:
                    ret = 2;
                    break;
                case 3:
                    ret = 3;
                    break;
                case 4:
                    ret = 4;
                    break;
            }
            gmode_running = false;
        }
    prev_green = curr_green;
    }

    return ret;
}