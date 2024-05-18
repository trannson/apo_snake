/**
 * @file multiplayer.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for initialization and functions of the game loop for 2 players
*/

#ifndef MULTI_H
#define MULTI_H

/**
 * @brief Runs the multiplayer game mode.
 * 
 * This function handles the main loop of the multiplayer game mode, including updating snake positions,
 * handling collisions, updating the display, and managing the timer.
 * 
 * @param timerush Boolean flag indicating if the timerush mode is active.
 */
void multiplayer(bool timerush);

#endif // MULTI_H
