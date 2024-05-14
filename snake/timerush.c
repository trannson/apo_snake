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
#include "RGB_led.h"
#include "led_line.h"

void decrease_time(int* time_amount, int* ticks) {
    if (*ticks > 5) {
        *time_amount -= 1;
        *ticks = 0;
    }
}

void reset_time(int* time_amount) {
    *time_amount = 8;
}

void display_time1(int time_amount) {
    char text[3];
    sprintf(text, "%d\n", time_amount);
    write_text(450, 20, text, 0xff, 2, 5);
}

void display_time2(int time_amount) {
    char text[3];
    sprintf(text, "%d\n", time_amount);
    write_text(20, 20, text, 0xF000, 2, 5);
}
