/**
 * @file RGB_led.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for changing the colors of two RGB led
*/

#ifndef RGB_LED_H
#define RGB_LED_H

/**
 * @brief Sets the color of the first RGB LED.
 * 
 * This function sets the color of the first RGB LED by writing the RGB values to the appropriate register.
 * 
 * @param red The red component of the color (0-255).
 * @param green The green component of the color (0-255).
 * @param blue The blue component of the color (0-255).
 */
void display_color_led1(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Sets the color of the second RGB LED.
 * 
 * This function sets the color of the second RGB LED by writing the RGB values to the appropriate register.
 * 
 * @param red The red component of the color (0-255).
 * @param green The green component of the color (0-255).
 * @param blue The blue component of the color (0-255).
 */
void display_color_led2(uint8_t red, uint8_t green, uint8_t blue);

#endif // RGB_LED_H
