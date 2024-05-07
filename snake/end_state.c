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



void init_screen_state(SnakeBig* Bigsnake) {
    int ptr = 0;
    unsigned short *fb;
    unsigned char *parlcd_mem_base;
    unsigned char *mem_base;

    for (int i = 0; i < 320 ; i++) {
        for (int j = 0; j < 480 ; j++) {
        int c = 0;
        fb[ptr]=c;
        parlcd_write_data(parlcd_mem_base, fb[ptr++]);
        }
    }

    while (1) {
        int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
        draw_died(Bigsnake);

        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, 0);
        }

         if ((r&0x7000000)!=0) {
            break;
        }
    
    }

}

void draw_died(SnakeBig* Bigsnake) {
    char* message;
    char back_to_menu[] = "MENU";
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

    write_text(90, 90, message, Bigsnake->color, 4, 20);

    draw_button(140, 230, 340, 300);

    write_text(145, 240, back_to_menu, 0xF000, 4, 20);


}