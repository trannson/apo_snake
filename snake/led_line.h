/**
 * @file led_line.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for displaying data on a led line, specifically depicts the lengths of the snakes
*/

#ifndef LED_LINE_H
#define LED_LINE_H

/**
 * @brief Displays the lengths of the blue and red snakes using LED line.
 * 
 * This function calculates the lengths of the blue and red snakes, combines their lengths
 * into a single 32-bit value, and writes it to the LED line register.
 * 
 * @param blue_lenght Length of the blue snake.
 * @param red_lenght Length of the red snake.
 */
void display_lenght(int blue_lenght, int red_lenght);

/**
 * @brief Combines two 16-bit values into a single 32-bit value.
 * 
 * This function combines two 16-bit values into a single 32-bit value, with `value1` in the higher 16 bits
 * and `value2` in the lower 16 bits.
 * 
 * @param value1 The first 16-bit value.
 * @param value2 The second 16-bit value.
 * @return uint32_t The combined 32-bit value.
 */
uint32_t combine_uint16(uint16_t value1, uint16_t value2);

/**
 * @brief Displays the length of the first snake (blue) using LED line.
 * 
 * This function calculates which LEDs should be lit to represent the length of the blue snake.
 * 
 * @param lenght The length of the blue snake.
 * @return uint16_t The bit pattern representing the length on the LED line.
 */
uint16_t display_snake_lenght1(int lenght);

/**
 * @brief Displays the length of the second snake (red) using LED line.
 * 
 * This function calculates which LEDs should be lit to represent the length of the red snake.
 * 
 * @param lenght The length of the red snake.
 * @return uint16_t The bit pattern representing the length on the LED line.
 */
uint16_t display_snake_lenght2(int lenght);

#endif // LED_LINE_H