#ifndef END_STATE_H
#define END_STATE_H

#include "snake_prop.h"

/*
* Called when some snake hits boundaries, itself or the other snake
* Then a screen will appear stating that the snake has died, plus it will show a score
* Does have a button, which takes player back to the menu
*
*@param loser_snake: a snake, that loses
*@param winner_snake: a snake, that won
* Note: in single player, loser and winner are the same snake
*@param multiplayer: true if the game was multiplayer, otherwise false
*/
void init_screen_state(SnakeBig* loser_snake, SnakeBig* winner_snake, bool multiplayer);

/*
* Function is called by init_screen_state, if the game was singleplayer
* Text with score will appear
* Shows two button, one leads back to the menu, the second one enables submiting score with custom name
*
*@param big_snake: the snake which died
*/
void draw_died_screen_single(SnakeBig* big_snake);

/*
* Draws ending screen for multiplayer game, shows both snake's score
* Has button, which leads back to the menu
*
*@param loser_snake: snake, that lost the game
*@param winner_snake: snake, that won the game
*/
void draw_died_screen_multi(SnakeBig* loser_snake, SnakeBig* winner_snake);

#endif // END_STATE_H