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
#include <stdint.h>
#include "RGB_led.h"


extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void display_color_led1(uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t rgb_value1 = (red << 16) | (green << 8) | blue;
    *((volatile uint32_t *)(mem_base + SPILED_REG_LED_RGB1_o)) = rgb_value1;

}

void display_color_led2(uint8_t red, uint8_t green, uint8_t blue) {
    uint32_t rgb_value2 = (red << 16) | (green << 8) | blue;
    *((volatile uint32_t *)(mem_base + SPILED_REG_LED_RGB2_o )) = rgb_value2;
}
