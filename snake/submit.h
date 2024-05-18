/**
 * @file submit.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for showing a scene for saving players score and saving it
*/

#ifndef SUBMIT_H
#define SUBMIT_H

#include "snake_prop.h"

/**
 * @brief Submits the player's name and score.
 * 
 * This function handles the input for the player's name using a knob to select
 * letters and buttons to delete or submit the name. It updates the display and
 * saves the name and score to a file.
 *
 * @param snake Pointer to the SnakeBig structure containing the snake's properties.
 */
void submit(SnakeBig* snake);

/**
 * @brief Draws all the buttons for name input.
 * 
 * This function draws the buttons on the screen and labels them with letters
 * from A to Z, a DELETE button, and a DONE button.
 */
void make_buttons();

/**
 * @brief Saves the player's name and score to a file.
 * 
 * This function appends the player's name and score to the "scores.txt" file.
 *
 * @param name The player's name.
 * @param score The player's score.
 */
void save_score(char name[], int score);

#endif // SUBMIT_H
