#ifndef DRAW_H
#define DRAW_H

/*
* Gives pixel with coordinates color
*
* @param x: pixel's x coordinate
* @param y: pixel's y coordinate
* @param color: new color for the pixel 
*/
void draw_pixel(int x, int y, unsigned short color);

/*
* Renders the neighborhood of a pixel depending on the scale
* Calls draw_pixel for all those pixels
*
* @param x: pixel's x coordinate
* @param y: pixel's y coordinate
* @param color: new color for the pixel(s)
* @param scale: a measure of how many surrounding pixels are colored
*/
void draw_pixel_big(int x, int y, unsigned short color, int scale);

/*
* Gets char's width
*
* @param ch: given char
* @return width: width of the character
*/
int char_width(int ch);

/*
* Draws character made of pixels
*
* @param x: starting x coordinate of the character
* @param y: starting y coordinate of the character
* @param ch: given character
* @param color: color of the character
* @param scale: a measure of how many surrounding pixels are colored
*/
void draw_char(int x, int y, char ch, unsigned short color, int scale);

#endif // DRAW_H
