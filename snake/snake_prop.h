#ifndef SNAKE_PROP_H
#define SNAKE_PROP_H

// The struct of the snake's body parts
typedef struct Snake {
  int index;
  int x;
  int y;
  struct Snake* next;
  struct Snake* previous;
} Snake;

// the struct of the whole snake and it's information
typedef struct SnakeBig {
    int lenght;
    int dir;
    int curr_dir;
    int prev_dir;
    unsigned short color;
    Snake* snake;
    Snake* tail;
} SnakeBig;

/*
* Creates a whole new snake, the new snake starts with only a head and a tail
*
*@param lenght: the starting lenght of the snake
*@param dir: the starting dirrection (1 is LEFT, 2 is UP, 3 is RIGHT, 4 is Down)
*@param curr_dir: the current value of the button responsible for the movement of the snake
*@param prev_dir: the previous value of the button responsible for the movement of the snake
*@param color: the color of the snake
*@param x1: initial x coordinate for the head
*@param x2: initial x coordinate for the tail
*@param y: initial y coordinate for the head and the tail
*@return big_snake: new snake with all the necessary information
*/
SnakeBig* build_snake(int lenght, int dir, int curr_dir, int prev_dir, unsigned short color, int x1, int x2, int y);

/*
* Creates a new snake's body part, called when the snake eats something
*
*@param index: the new body part's index
*@param x: the new body part's x coordinate
*@param y: the new body part's y coordinate
*@return new_node: the new body part of the snake
*/
Snake* create_snake_part(int index, int x, int y);

/*
* Takes a new body part and attaches it to the snake's tail
*
*@param old_tail: old snake's tail
*@param new_tail: new snake's tail, this part is attached to the old tail
*/
void add_snake(Snake* old_tail, Snake* new_tail);

/*
* Draws the whole snake
*
*@param head: the head of the snake
*@param color: snake's color
*/
void draw_snake(Snake* head, unsigned short color);

/*
* Updates each body part it's new coordinates
*
* @param tail: tail of the snake (coordinates are passed from part to part recursively)
*/
void move_snakes_body(Snake* tail);

/*
* Updates a new snake's head coordinates depending on the dirrection of the snake
*
*@param snake_dir: dirrection of the snake (1 is LEFT, 2 is UP, 3 is RIGHT, 4 is Down)
*@param head: the head of the snake
*/
void move_snakes_head(int snake_dir, Snake* head);

#endif // SNAKE_PROP_H
