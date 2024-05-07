#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdbool.h>
#include "snake_prop.h"

/*
* Takes one or two snakes (depending on a game mode) and for each snake checks their collisions
*
*@param Bblue_snake: the struct of the blue snake, the strcut is defined in snake_prop.h
*@param Bred_snake: the struct of the blue snake, the strcut is defined in snake_prop.h
* NOTE: in singleplayer, Bblue_snake and Bred_snake are the same snake, but it works the same 
*@param apple_x: pointer to an apple x coordinate 
*@param apple_y: pointer to an apple y coordinate
*@return ret: should be there TODO
*/
int check_collisions(SnakeBig* Bblue_snake, SnakeBig* Bred_snake, int* apple_x, int* apple_y);

/*
* Checks if the snake's head has reached the screen boundaries
*
* @param snake_x: current x coordinate of the snake's head
* @param snake_y: current y coordinate of the snake's head
* @return ret: true if the snake is still inside the boarders, false if out of bounds
*/
bool check_bounds_collisions(int snake_x, int snake_y);

/*
* Checks if the snake collided with itself
*
*@param BigSnake: snake to be checked
*@return ret: false if the snake hasn't bumped into itself, otherwise true
*/
bool check_snake_collision(SnakeBig* BigSnake);

/*
* Checks if the snake's head had collided with an apple
*
* @param snake_x: x coordinate of the snake's head
* @param snake_y: y coordinate of the snake's head
* @param apple_x: x coordinate of the apple
* @param apple_y: y coordinate of the apple
* @return ret: true if the snake reached the apple, otherwise false
*/
bool apple_collision(int snake_x, int snake_y, int* apple_x, int* apple_y);

#endif // COLLISIONS_H
