#include "buttons.h"
#include "draw_px_or_char.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
extern unsigned char *mem_base;

/*
Each button (red, green and blue) can be rotated by 360 degrees
Each button's current position is represented by 8 bits (0 - 256)
and one piece of movement (when button clicks) will change the 
number by 4
SENSITIVITY is just to handle smaller changes, when rotating the button
this is caused by game loop refreshes
*/
#define SENSITIVITY 3

/*
@param cur_value: current value of some periphery (button in our case)
@param prev_value: the value of the same periphery, as in cur_value, but the
  value is form the previous refresh of the (while) loop
@param action_num: number of the current action, this value can be from
  1 to @param upper_range, each number represents different action that takes place
@param upper_range: indicates the highest value @param action_num can have

@return action_num: is new action number, which will take place
*/
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range) {

  // Button moved to the LEFT
  if (cur_value < prev_value && (abs(cur_value - prev_value) > SENSITIVITY)) {
    if (action_num == 1) {
      action_num = upper_range;
    } else {
      action_num -= 1;
    }
  // Button moved to the RIGHT
  } else if ((cur_value > prev_value) && (abs(cur_value - prev_value) > SENSITIVITY)) {
    if (action_num == upper_range) {
      action_num = 1;
    } else {
      action_num += 1;
    }
  }
  
  return action_num;
}

/*
@param x: x coordinate of the text
@param y: y coordinate of the text
@param text[]: is the text to be written
@param colot: color of the text
*/
void write_text(int x, int y, char text[], unsigned short color, int scale, int offset) {
    for (int i = 0; text[i] != '\0'; ++i) {
        draw_char(x,y, text[i], color, scale);
        x += char_width(text[i]) + offset;
        }
        x = 145;
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
