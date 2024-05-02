#ifndef BUTTONS_H
#define BUTTONS_H

/*
This function modifies action_num, which represents a number in a certain range,
where each number indicates a different action that will take place
when there is a difference between cur_value and prev_value, then new action_num 
will be different, this happens when value of some periphery (button) changes 
since last refresh, when those values are the same, then action_num stays the same
*/
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range);

void write_text(int x, int y, char text[], unsigned short color, int scale, int offset);

/*
Gets two points and paints the space between them with one color
Color can be changed in menu.c
*/
void draw_button(int start_x, int start_y, int end_x, int end_y);

/*
Draws outer lines around button
*/
void draw_outer_lines(int start_x, int start_y, int end_x, int end_y);

#endif // BUTTONS_H