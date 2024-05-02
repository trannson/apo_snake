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
    // Start button
    int start_txt_x = 145;
    int start_txt_y = 40;
    char start_txt_txt[] = "START";
    unsigned short start_txt_clr = 0xF000; 

    // Select mode button
    int gmode_txt_x = 145;
    int gmode_txt_y = 140;
    char gmode_txt_txt[] = "MODE";
    unsigned short gmode_txt_clr = 0xF000; 

    // Last button TODO
    // int gmode_txt_x = 145;
    // int gmode_txt_y = 40;
    // char gmode_txt_txt[] = "START";
    // unsigned short gmode_txt_clr = 0xF000;

    int offset = 30;
    
    /*
    END OF TEXT PROPERTIES
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

        /*
        Drawing buttons with their texts
        ********************************************************************************
        */
        draw_button(140, 30, 340, 100);
        draw_button(140, 130, 340, 200);
        draw_button(140, 230, 340, 300);

        write_text(start_txt_x, start_txt_y, start_txt_txt, start_txt_clr, 4, offset);
        write_text(gmode_txt_x, gmode_txt_y, gmode_txt_txt, gmode_txt_clr, 4, offset);
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
        draw_outer_lines(140, 30, 340, 100);      
        break;
        case 2:
        draw_outer_lines(140, 130, 340, 200);
        break;
        case 3:
        draw_outer_lines(140, 230, 340, 300);
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

            }
        }
    prev_green = curr_green;
    }

    return ret;
}
