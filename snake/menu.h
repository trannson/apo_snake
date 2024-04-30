#ifndef MENU_H
#define MENU_H

/*
This will call draw_button() 3 times with different numbers, which
will make 3 buttons in the menu scene
*/
void show_menu();

/*
Gets two points and paints the space between them with one color
Color can be changed in menu.c
*/
void draw_button(int start_x, int start_y, int end_x, int end_y);

/*
Draws outer lines around button
*/
void draw_outer_lines(int start_x, int start_y, int end_x, int end_y);

#endif // MENU_H