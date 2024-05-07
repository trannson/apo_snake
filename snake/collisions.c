#include "collisions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "food_maker.h"
#include "snake_prop.h"
#include "end_state.h"

/*
Dimensions of the LCD panel
*/
#define WIDTH 480
#define HEIGHT 320

int check_collisions(SnakeBig* Bblue_snake, SnakeBig* Bred_snake, int* apple_x, int* apple_y) {
    int ret = 1;
    if (check_bounds_collisions(Bblue_snake->snake->x, Bblue_snake->snake->y)) {
        init_screen_state(Bblue_snake);
        ret = 2;
    } else if(check_bounds_collisions(Bred_snake->snake->x, Bred_snake->snake->y)) {
        init_screen_state(Bred_snake);
        ret = 3;
    } else if (apple_collision(Bblue_snake->snake->x, Bblue_snake->snake->y, apple_x, apple_y)) {
        make_food(apple_x, apple_y);

        Snake* tmp = create_snake_part(Bblue_snake->tail->index++, Bblue_snake->tail->x, Bblue_snake->tail->y);
        add_snake(Bblue_snake->tail, tmp);
        Bblue_snake->tail = tmp;
        Bblue_snake->lenght++;
        ret = 4;
    } else if (apple_collision(Bred_snake->snake->x, Bred_snake->snake->y, apple_x, apple_y)) {
        make_food(apple_x, apple_y);

        Snake* tmp = create_snake_part(Bred_snake->tail->index++, Bred_snake->tail->x, Bred_snake->tail->y);
        add_snake(Bred_snake->tail, tmp);
        Bred_snake->tail = tmp;
        Bred_snake->lenght++;
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
