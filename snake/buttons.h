#ifndef BUTTONS_H
#define BUTTONS_H

// In buttons.c there is macro SENSITIVITY, which modifies sensitivity for button rotating

/*
* Modifies action_num, which represents some actions, each has it's given number
* If the button moved to the left, then prev_value is higher then current
* If the button moved to the right, then prev_value is lower then current
* If prev_value and curr_value are the same, then button didn't move enough
*
* @param cur_value: current value of some periphery (button in our case)
* @param prev_value: the value of the same periphery, as in cur_value, but the value is from the previous refresh of the (while) loop
* @param action_num: number of the current action, this value can be within 1 nad upper_range, each number represents different action that takes place
* @param upper_range: indicates the highest value @param action_num can have
* @return action_num: is new action number, which will take place
*/
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range);

/*
* Writes a given text to specific location
*
* @param x: starting x coordinate
* @param y: starting y coordinate
* @param text[]: text to be written
* @param color: color of the text
* @param scale: multiplicator of how big the text will be (recommended 2 - 6)
* @param offset: amount of pixels for extra space between characters
*/
void write_text(int x, int y, char text[], unsigned short color, int scale, int offset);

/*
* Gets two points of the rectangle (top left and down right corners) and fill this area with color
*
* @param start_x: x coordinate of the first point
* @param start_y: y coordinate of the first point
* @param end_x: x coordinate of the second point
* @param end_y: y coordinate of the second point
*/
void draw_button(int start_x, int start_y, int end_x, int end_y);

/*
* Draws outher lines around button with these two points
*
* @param start_x: x coordinate of the first point
* @param start_y: y coordinate of the first point
* @param end_x: x coordinate of the second point
* @param end_y: y coordinate of the second point
*/
void draw_outer_lines(int start_x, int start_y, int end_x, int end_y);

#endif // BUTTONS_H
