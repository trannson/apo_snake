/**
 * @file draw_px_or_char.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for drawing pixels and writing text on a display
 *        these functions were taken from courseware from 
 *        https://cw.fel.cvut.cz/wiki/courses/b35apo/tutorials/11/start
*/

#ifndef DRAW_H
#define DRAW_H

/**
 * @brief Draws a single pixel on the framebuffer.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void draw_pixel(int x, int y, unsigned short color);

/**
 * @brief Draws a scaled pixel on the framebuffer.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @param scale The scale factor.
 */
void draw_pixel_big(int x, int y, unsigned short color, int scale);

/**
 * @brief Returns the width of a character.
 * 
 * @param ch The character.
 * @return The width of the character.
 */
int char_width(int ch);

/**
 * @brief Draws a character on the framebuffer.
 * 
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param ch The character to draw.
 * @param color The color of the character.
 * @param scale The scale factor.
 */
void draw_char(int x, int y, char ch, unsigned short color, int scale);

#endif // DRAW_H
