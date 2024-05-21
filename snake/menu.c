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

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

int show_menu() {

    // Represents game modes, each has it's own number, 1 is default
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

    // START button
    int start_txt_x = 32;
    int start_txt_y = 150;
    char start_txt_txt[] = "START";
    unsigned short start_txt_clr = 0x0010; 

    // SELECT MODE button
    int gmode_txt_x = 270;
    int gmode_txt_y = 150;
    char gmode_txt_txt[] = "MODE";
    unsigned short gmode_txt_clr = 0x0010; 

    // Last button TODO
    int exit_txt_x = 155;
    int exit_txt_y = 240;
    char exit_txt_txt[] = "EXIT";
    unsigned short exit_txt_clr = 0x0010;

    // Extra space between letters
    int offset = 30;
    
    /*
    THE END OF THE TEXT PROPERTIES
    ********************************************************************************
    */
    
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // These two store value of the green knob
    int curr_green = (((r>>8)&0xff));
    int prev_green = (((r>>8)&0xff));

    /*
    Indicates which button in the menu the cursor is currently on
    1 means START GAME (top), 2 means SETTINGS (middle), 3 means EXIT (down)
    */
    int menu_button = 1;

    bool menu_running = true;

    while(menu_running) {

        write_text(20, 10, "SNAKE", 0xF00, 9, 80);

        /*
        Drawing buttons with their texts
        ********************************************************************************
        */
        draw_button(30, 140, 220, 210);
        draw_button(260, 140, 450, 210);
        draw_button(145, 230, 335, 300);

        write_text(start_txt_x, start_txt_y, start_txt_txt, start_txt_clr, 4, offset);
        write_text(gmode_txt_x, gmode_txt_y, gmode_txt_txt, gmode_txt_clr, 4, offset);
        write_text(exit_txt_x, exit_txt_y, exit_txt_txt, exit_txt_clr, 4, offset);
        /*
        End of drawing buttons with their texts
        ********************************************************************************
        */

        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        curr_green = (((r>>8)&0xff)); // green knob

        menu_button = modify_while_rotating(curr_green, prev_green, menu_button, 3);

        // Drawing outer lines around the button the cursor is currently on
        switch (menu_button)
        {
        case 1:
            draw_outer_lines(30, 140, 220, 210);      
            break;
        case 2:
            draw_outer_lines(260, 140, 450, 210);
            break;
        case 3:
            draw_outer_lines(145, 230, 335, 300);
            break;
        default:
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
            switch(menu_button) {
                case 1:
                    menu_running = false;
                    break;
                case 2:
                    ret = show_game_modes();
                    break;
                case 3:
                    ret = 5;
                    menu_running = false;
                    break;
            }
        }
    prev_green = curr_green;
    }

    return ret;
}
