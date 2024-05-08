#ifndef END_STATE_H
#define END_STATE_H

#include "snake_prop.h"

/*
* Called when some snake hits boundaries, itself or the other snake
* Then a screen will apear stating that the snake has died, plus it will show a score
* When the button is pressed, then the menu will appear again
*
*@param Bigsnake: the snake which died
*/
void init_screen_state(SnakeBig* loser_snake, SnakeBig* winner_snake, bool multiplayer);

/*
* Function is called by init_screen_state
* It draws a text and waits for the green button to be pressed (return to the menu)
*
*@param big_snake: the snake which died
*/
void draw_died_screen_single(SnakeBig* big_snake);

void draw_died_screen_multi(SnakeBig* loser_snake, SnakeBig* winner_snake);

#endif // END_STATE_H