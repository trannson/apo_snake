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
#include "multiplayer.h"
#include "RGB_led.h"
#include "led_line.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void multiplayer(bool timerush) {

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;
    int ptr;
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    SnakeBig* Bblue_snake = build_snake(2, 3, ((r&0xff)), ((r&0xff)), 0x7ff, 140, 160, 140);
    SnakeBig* Bred_snake = build_snake(2, 1, (((r>>16)&0xff)), (((r>>16)&0xff)), 0xF000, 400, 420, 140);

    int apple_x = 200;
    int apple_y = 200;
    
    while (1) {
        display_color_led1(0, 255, 0);
        display_color_led2(0, 255, 0);

        display_lenght(Bblue_snake->lenght, Bred_snake->lenght);
        r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

        Bblue_snake->curr_dir = ((r&0xff));
        Bred_snake->curr_dir = (((r>>16)&0xff));

        Bblue_snake->dir = modify_while_rotating(Bblue_snake->curr_dir, Bblue_snake->prev_dir, Bblue_snake->dir, 4);
        Bred_snake->dir = modify_while_rotating(Bred_snake->curr_dir, Bred_snake->prev_dir, Bred_snake->dir, 4);

        Bblue_snake->prev_dir = Bblue_snake->curr_dir;
        Bred_snake->prev_dir = Bred_snake->curr_dir;

        move_snakes_body(Bblue_snake->tail);
        move_snakes_body(Bred_snake->tail);

        move_snakes_head(Bblue_snake->dir, Bblue_snake->snake);
        move_snakes_head(Bred_snake->dir, Bred_snake->snake);
        
        // Black screen
        for (ptr = 0; ptr < 320*480 ; ptr++) {
            fb[ptr]=0u; 
        }
        
        draw_snake(Bblue_snake->snake, Bblue_snake->color);
        draw_snake(Bred_snake->snake, Bred_snake->color);

        draw_apple(apple_x, apple_y);

        if(check_collisions(Bblue_snake, Bred_snake, &apple_x, &apple_y, true)) {
            break;
        }

        // Painting the LCD display
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
}
