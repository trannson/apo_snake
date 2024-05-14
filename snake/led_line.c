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
#include "led_line.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

void display_lenght(int blue_lenght, int red_lenght) {
        uint16_t bl = display_snake_lenght1(blue_lenght);
        uint16_t rd = display_snake_lenght2(red_lenght);
        uint32_t led_line = combine_uint16(rd, bl);
        *((volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o )) = led_line;
}

uint32_t combine_uint16(uint16_t value1, uint16_t value2) {
    uint32_t combined_value = ((uint32_t)value1 << 16);
    combined_value |= value2;
    return combined_value;
}

uint16_t display_snake_lenght1(int lenght) {
    int len = lenght / 3;
    uint16_t result = 0; 
    for (int i = 0; i < len; i++) {
        result |= (1 << i);
    }
    return result;
}

uint16_t display_snake_lenght2(int lenght) {
    int len = lenght / 3;
    uint16_t result = 0;
    for (int i = 16; i >= 16 - len; i--) {
        result |= (1 << i);
    }
    return result;
}
