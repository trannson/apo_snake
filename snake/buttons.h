/**
 * @file buttons.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for drawing buttons, their outer lines and text displayed on those buttons
*/

#ifndef BUTTONS_H
#define BUTTONS_H

// In buttons.c there is macro SENSITIVITY, which modifies sensitivity for button rotating

/**
 * @brief Modifies the action number based on knob rotation.
 * 
 * This function adjusts the action number based on the direction and magnitude of the knob rotation.
 * 
 * @param cur_value The current value of the knob (0 - 256).
 * @param prev_value The previous value of the knob (0 - 256).
 * @param action_num The current action number.
 * @param upper_range The upper range of the action number.
 * @return The modified action number.
 */
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range);

/**
 * @brief Writes text on the screen.
 * 
 * This function writes text on the screen at the specified position with the given color, scale, and offset.
 * 
 * @param x The x-coordinate of the starting position.
 * @param y The y-coordinate of the starting position.
 * @param text The text to be written.
 * @param color The color of the text.
 * @param scale The scale of the text.
 * @param offset The offset between characters.
 */
void write_text(int x, int y, char text[], unsigned short color, int scale, int offset);

/**
 * @brief Draws a button on the screen.
 * 
 * This function draws a button with the specified start and end coordinates.
 * 
 * @param start_x The x-coordinate of the top-left corner.
 * @param start_y The y-coordinate of the top-left corner.
 * @param end_x The x-coordinate of the bottom-right corner.
 * @param end_y The y-coordinate of the bottom-right corner.
 */
void draw_button(int start_x, int start_y, int end_x, int end_y);

/**
 * @brief Draws outer lines around a button.
 * 
 * This function draws outer lines around a button to highlight it.
 * 
 * @param start_x The x-coordinate of the top-left corner.
 * @param start_y The y-coordinate of the top-left corner.
 * @param end_x The x-coordinate of the bottom-right corner.
 * @param end_y The y-coordinate of the bottom-right corner.
 */
void draw_outer_lines(int start_x, int start_y, int end_x, int end_y);

#endif // BUTTONS_H
