#include "collisions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "food_maker.h"
#include "snake_prop.h"
#include "end_state.h"
#include "RGB_led.h"
#include "timerush.h"

/*
Dimensions of the LCD panel
*/
#define WIDTH 480
#define HEIGHT 320


bool check_collisions(SnakeBig* Bblue_snake, SnakeBig* Bred_snake, int* apple_x, int* apple_y, bool multiplayer, bool timerush, int* blue_time, int* red_time) {
    bool ret = false;
    if (check_snake_collision(Bblue_snake) || check_bounds_collisions(Bblue_snake->snake->x, Bblue_snake->snake->y)) 
    {
        display_color_led2(255, 0, 0);
        if (!multiplayer) {
            display_color_led1(255, 0, 0);
        }
        init_screen_state(Bblue_snake, Bred_snake, multiplayer);
        ret = true;
    } else if (check_snake_collision(Bred_snake) || check_bounds_collisions(Bred_snake->snake->x, Bred_snake->snake->y)) 
    {
        display_color_led1(255, 0, 0);
        if (!multiplayer) {
            display_color_led2(255, 0, 0);
        }
        init_screen_state(Bred_snake, Bblue_snake, multiplayer);
        ret = true;
    } else if (apple_collision(Bblue_snake->snake->x, Bblue_snake->snake->y, apple_x, apple_y)) {
        display_color_led2(0, 0, 255);
        if (!multiplayer) {
            display_color_led1(0, 0,255);
        }
        if (timerush) {
            reset_time(blue_time);
        }
        make_food(apple_x, apple_y);
        Snake* tmp = create_snake_part(Bblue_snake->tail->index++, Bblue_snake->tail->x, Bblue_snake->tail->y);
        add_snake(Bblue_snake->tail, tmp);
        Bblue_snake->tail = tmp;
        Bblue_snake->lenght++;
    } else if (apple_collision(Bred_snake->snake->x, Bred_snake->snake->y, apple_x, apple_y)) {
        display_color_led1(0, 0, 255);
        if (!multiplayer) {
            display_color_led2(0, 0,255);
        }
        if (timerush) {
            reset_time(red_time);
        }
        make_food(apple_x, apple_y);

        Snake* tmp = create_snake_part(Bred_snake->tail->index++, Bred_snake->tail->x, Bred_snake->tail->y);
        add_snake(Bred_snake->tail, tmp);
        Bred_snake->tail = tmp;
        Bred_snake->lenght++;
    }
    if (multiplayer) {
        if (snakes_collisions(Bblue_snake, Bred_snake)) {
            init_screen_state(Bred_snake, Bblue_snake, multiplayer);
            ret = true;
        } else if (snakes_collisions(Bred_snake, Bblue_snake)) {
            init_screen_state(Bblue_snake, Bred_snake, multiplayer);
            ret = true;
        }
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

bool check_snake_collision(SnakeBig* BigSnake) {
    bool ret = false;

    // iterate over body
    Snake* current = BigSnake->snake;
    while (current->next != NULL) {
        if (BigSnake->snake->x == current->next->x && BigSnake->snake->y == current->next->y) {
            ret = true;
            break;  
        }

        current = current->next;
    }
    return ret;
}

bool apple_collision(int snake_x, int snake_y, int* apple_x, int* apple_y) {
    bool ret = false;
    if (abs(snake_x - *apple_x) < 20 && abs(snake_y - *apple_y) < 20) {
        
        ret = true;
    }
    return ret;
}

bool snakes_collisions(SnakeBig* snk1, SnakeBig* snk2) {
    bool ret = false;
    
    Snake* current = snk1->snake;
    while (current != NULL) {
        if (snk2->snake->x == current->x && snk2->snake->y == current->y) {
            ret = true;
            break;
        }

        current = current->next;
    }
    return ret;
}

