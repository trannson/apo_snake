/**
 * @file end_state.h.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for showing the game over scene with score
*/

#ifndef END_STATE_H
#define END_STATE_H

#include "snake_prop.h"

/**
 * @brief Initializes the screen state after the game ends.
 * 
 * This function clears the screen and draws the end state screen, including the winner/loser message,
 * scores, and buttons for returning to the menu or submitting the score.
 * 
 * @param loser_snake Pointer to the SnakeBig struct representing the losing snake.
 * @param winner_snake Pointer to the SnakeBig struct representing the winning snake.
 * @param multiplayer Boolean indicating whether the game was multiplayer or not.
 */
void init_screen_state(SnakeBig* loser_snake, SnakeBig* winner_snake, bool multiplayer);

/**
 * @brief Draws the end state screen for singleplayer mode.
 * 
 * This function displays the end state screen for singleplayer mode, including the message indicating
 * the loser, the score, and buttons for returning to the menu or submitting the score.
 * 
 * @param big_snake Pointer to the SnakeBig struct representing the losing snake.
 */
void draw_died_screen_single(SnakeBig* big_snake);

/**
 * @brief Draws the end state screen for multiplayer mode.
 * 
 * This function displays the end state screen for multiplayer mode, including the message indicating
 * the winner, scores of both players, and buttons for returning to the menu or submitting the score.
 * 
 * @param loser_snake Pointer to the SnakeBig struct representing the losing snake.
 * @param winner_snake Pointer to the SnakeBig struct representing the winning snake.
 */
void draw_died_screen_multi(SnakeBig* loser_snake, SnakeBig* winner_snake);

#endif // END_STATE_H