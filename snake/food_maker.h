/**
 * @file food_maker.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for generating new apple coordinates and drawing the apple
*/

#ifndef FOODMAKER_H
#define FOODMAKER_H

/**
 * @brief Generates random coordinates for food (apple) within specified ranges.
 * 
 * This function sets random x and y coordinates for food within the ranges [20, 460] and [20, 300] respectively.
 * 
 * @param[out] random_x Pointer to the x-coordinate of the food.
 * @param[out] random_y Pointer to the y-coordinate of the food.
 */
void make_food(int* random_x, int* random_y);

/**
 * @brief Generates a random number within a specified range.
 * 
 * This function returns a random integer within the range [min, max].
 * 
 * @param[in] min The minimum value of the range.
 * @param[in] max The maximum value of the range.
 * @return int A random number within the specified range.
 */
int random_num_in_range(int min, int max);

/**
 * @brief Draws an apple on the screen.
 * 
 * This function draws a red square representing an apple at the specified coordinates.
 * 
 * @param[in] apple_x The x-coordinate of the apple's position.
 * @param[in] apple_y The y-coordinate of the apple's position.
 */
void draw_apple(int apple_x, int apple_y);

#endif // FOODMAKER_H
