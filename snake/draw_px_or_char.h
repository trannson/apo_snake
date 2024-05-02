#ifndef DRAW_H
#define DRAW_H

void draw_pixel(int x, int y, unsigned short color);

void draw_pixel_big(int x, int y, unsigned short color, int scale);

int char_width(int ch);

void draw_char(int x, int y, char ch, unsigned short color, int scale);

#endif // DRAW_H