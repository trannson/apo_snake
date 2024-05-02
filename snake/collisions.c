#include "collisions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
Dimensions of the LCD panel
*/
#define WIDTH 480
#define HEIGHT 320

/*
@param snake_x: current x coordinate of the snake's head
@param snake_y: current y coordinate of the snake's head

It represents the top left corner of the head

@return ret: true if snake is still inside the boarders, false if out of bounds
*/
bool check_collisions(int snake_x, int snake_y) {
    bool ret = true;
    if ((snake_x > WIDTH) || (snake_y > HEIGHT) || (snake_x < 0) || (snake_y < 0) ) {
        printf("Snake out of range\n");
        ret = false;
    }
    return ret;
}

bool apple_collision(int snake_x, int snake_y, int apple_x, int apple_y) {
    if (abs(snake_x - apple_x) < 20 && abs(snake_y - apple_y) < 20) {
        return true;
    } else {
        return false;
    }
}
