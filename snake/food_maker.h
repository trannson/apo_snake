#ifndef FOODMAKER_H
#define FOODMAKER_H

/*
* Calls random_num_in_range, which will assign new coordinates to the food
*
*@param random_x: pointer to the current food's x coordinate, which will be changed (new value will be between 20 - 460)
*@param random_y: pointer to the current food's y coordinate, which will be changed (new value will be between 20 - 300)
*/
void make_food(int* random_x, int* random_y);

/*
* Generates new value to the x and y coordinate in the given range
*
*@param min: the lowest possible new value
*@param max: the highest possible new value
*return value: new value for the x or y coordinate
*/
int random_num_in_range(int min, int max);

/*
* Draws an apple due to it's coordinates
*
*@param apple_x: the x coordinate of the apple
*@param apple_y: the y coordinate of the apple
*/
void draw_apple(int apple_x, int apple_y);

#endif // FOODMAKER_H