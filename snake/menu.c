#include "menu.h"

#include <stdint.h>
#include <stdio.h>

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;

void show_menu() {

    draw_button(140, 30, 340, 100);

    draw_button(140, 130, 340, 200);

    draw_button(140, 230, 340, 300);

}

/*
@param start_x: x coordinate of the starting pixel of the button
@param start_y: y coordinate of the starting pixel of the button
@param end_x: x coordinate of the ending pixel of the button
@param end_y: y coordinate of the ending pixel of the button
*/
void draw_button(int start_x, int start_y, int end_x, int end_y) {
    for (int i = 0; i < end_x - start_x; ++i) {
        for (int j = 0; j < end_y - start_y; ++j) {
            fb[start_x + i + (start_y + j)*480] = 0x7ff;    
        }
    }
}

/*
@param start_x: x coordinate of the starting pixel of the button
@param start_y: y coordinate of the starting pixel of the button
@param end_x: x coordinate of the ending pixel of the button
@param end_y: y coordinate of the ending pixel of the button
*/
void draw_outer_lines(int start_x, int start_y, int end_x, int end_y) {
    // 'k' represents the thickness of the outer lines
    for (int k = 0; k < 5; ++k) {
        for (int i = 0; i < end_x - start_x; ++i) {
            for (int j = 0; j < end_y - start_y; ++j) {
                if ((i == 0) || (i == end_x - start_x - 1) || (j == 0) || (j == end_y - start_y  - 1)) {
                    fb[start_x + i - k + (start_y + j - k)*480] = 0xf000;
                }
            }
        }
    }
}
