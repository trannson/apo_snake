/**
 * @file singleplayer.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for initialization and functions of the game loop for 1 player
*/

#ifndef SINGLE_H
#define SINGLE_H

/**
 * @brief Runs the singleplayer game mode.
 * 
 * This function initializes the game state for singleplayer mode, creates the snake,
 * and enters the game loop. The game loop handles updating the snake's position,
 * checking for collisions, and drawing the game state to the screen. If the timerush
 * mode is enabled, it also handles the timer.
 * 
 * @param timerush Boolean flag indicating whether timerush mode is enabled.
 */
void singleplayer(bool timerush);

#endif // SINGLE_H