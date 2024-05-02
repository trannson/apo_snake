#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "food_maker.h"

void make_food(int* random_x, int* random_y) {
    
    srand(time(NULL));

    *random_x = random_num_in_range(20, 460);
    *random_y = random_num_in_range(20, 300);

}

int random_num_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}
