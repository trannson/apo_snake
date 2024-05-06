#include "collisions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "food_maker.h"

/*
Dimensions of the LCD panel
*/
#define WIDTH 480
#define HEIGHT 320

int check_collisions(int snake01_x, int snake01_y, int snake02_x, int snake02_y, int* apple_x, int* apple_y) {
    int ret = 1;
    if (check_bounds_collisions(snake01_x, snake01_y)) {
        ret = 2;
    } else if(check_bounds_collisions(snake02_x, snake02_y)) {
        ret = 3;
    } else if (apple_collision(snake01_x, snake01_y, apple_x, apple_y)) {
        make_food(apple_x, apple_y);
        ret = 4;
    } else if (apple_collision(snake02_x, snake02_y, apple_x, apple_y)) {
        make_food(apple_x, apple_y);
        ret = 5;
    }
    return ret;
}

bool check_bounds_collisions(int snake_x, int snake_y) {
    bool ret = false;
    if ((snake_x > WIDTH) || (snake_y > HEIGHT) || (snake_x < 0) || (snake_y < 0) ) {
        printf("Snake out of range\n");
        ret = true;
    }
    return ret;
}

bool apple_collision(int snake_x, int snake_y, int* apple_x, int* apple_y) {
    bool ret = false;
    if (abs(snake_x - *apple_x) < 20 && abs(snake_y - *apple_y) < 20) {
        return true;
    }
    return ret;
}
