/**
 * @file collisions.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for checking snake's collisions
*/

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <stdbool.h>
#include "snake_prop.h"

/**
 * @brief Checks for collisions between snakes, boundaries, and apples.
 * 
 * @param Bblue_snake Pointer to the blue snake.
 * @param Bred_snake Pointer to the red snake.
 * @param apple_x Pointer to the x-coordinate of the apple.
 * @param apple_y Pointer to the y-coordinate of the apple.
 * @param multiplayer Indicates if the game is multiplayer.
 * @param timerush Indicates if the game is in time rush mode.
 * @param blue_time Pointer to the blue snake's time in time rush mode.
 * @param red_time Pointer to the red snake's time in time rush mode.
 * @return true if there is a collision, false otherwise.
 */
bool check_collisions(SnakeBig* Bblue_snake, SnakeBig* Bred_snake, int* apple_x, int* apple_y, bool multiplayer, bool timerush, int* blue_time, int* red_time);

/**
 * @brief Checks for collisions with the game boundaries.
 * 
 * @param snake_x The x-coordinate of the snake.
 * @param snake_y The y-coordinate of the snake.
 * @return true if there is a boundary collision, false otherwise.
 */
bool check_bounds_collisions(int snake_x, int snake_y);

/**
 * @brief Checks for collisions between a snake and itself.
 * 
 * @param BigSnake Pointer to the snake.
 * @return true if there is a self-collision, false otherwise.
 */
bool check_snake_collision(SnakeBig* BigSnake);

/**
 * @brief Checks for collisions between a snake and an apple.
 * 
 * @param snake_x The x-coordinate of the snake.
 * @param snake_y The y-coordinate of the snake.
 * @param apple_x Pointer to the x-coordinate of the apple.
 * @param apple_y Pointer to the y-coordinate of the apple.
 * @return true if there is a collision between the snake and the apple, false otherwise.
 */
bool apple_collision(int snake_x, int snake_y, int* apple_x, int* apple_y);

/**
 * @brief Checks for collisions between two snakes.
 * 
 * This function checks whether the head of one snake collides with any part of the other snake.
 * 
 * @param snk1 Pointer to the first SnakeBig structure representing the first snake.
 * @param snk2 Pointer to the second SnakeBig structure representing the second snake.
 * @return true if there is a collision between the snakes, false otherwise.
 */
bool snakes_collisions(SnakeBig* snk1, SnakeBig* snk2);

#endif // COLLISIONS_H
