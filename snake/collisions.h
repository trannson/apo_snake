#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdbool.h>

/*
This function takes current snake's head coordinates and checks, if
the snake reached the borders, or not
*/
bool check_collisions(int snake_x, int snake_y);

#endif // COLLISIONS_H