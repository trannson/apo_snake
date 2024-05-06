#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "draw_px_or_char.h"

#include "food_maker.h"

void make_food(int* random_x, int* random_y) {
    
    srand(time(NULL));

    *random_x = random_num_in_range(20, 460);
    *random_y = random_num_in_range(20, 300);
}

int random_num_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

void draw_apple(int apple_x, int apple_y) {
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
          draw_pixel(i+apple_x, j + apple_y, 0xF000);
        }
    }
}
