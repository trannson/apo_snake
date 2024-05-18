/**
 * @file snake_prop.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for making and changing each snake's properties
*/

#ifndef SNAKE_PROP_H
#define SNAKE_PROP_H

/**
 * @struct Snake
 * @brief Represents a single part of the snake's body
 */
typedef struct Snake {
    int index;              /**< Index of the snake part */
    int x;                  /**< X-coordinate of the snake part */
    int y;                  /**< Y-coordinate of the snake part */
    struct Snake* next;     /**< Pointer to the next part of the snake */
    struct Snake* previous; /**< Pointer to the previous part of the snake */
} Snake;

/**
 * @struct SnakeBig
 * @brief Represents the entire snake with its properties
 */
typedef struct SnakeBig {
    int lenght;             /**< Length of the snake */
    int dir;                /**< Direction of the snake */
    int curr_dir;           /**< Current direction of the snake */
    int prev_dir;           /**< Previous direction of the snake */
    unsigned short color;   /**< Color of the snake */
    Snake* snake;           /**< Pointer to the head of the snake */
    Snake* tail;            /**< Pointer to the tail of the snake */
} SnakeBig;

/**
 * @brief Constructs a snake with specified properties.
 * 
 * This function allocates memory for a SnakeBig structure and initializes
 * it with the given parameters. It creates two snake parts (head and tail),
 * links them, and assigns them to the SnakeBig structure.
 * 
 * @param lenght Length of the snake.
 * @param dir Direction of the snake.
 * @param curr_dir Current direction of the snake.
 * @param prev_dir Previous direction of the snake.
 * @param color Color of the snake.
 * @param x1 X-coordinate of the head.
 * @param x2 X-coordinate of the tail.
 * @param y Y-coordinate of the snake (common for head and tail).
 * 
 * @return Pointer to the constructed SnakeBig structure.
 */
SnakeBig* build_snake(int lenght, int dir, int curr_dir, int prev_dir, unsigned short color, int x1, int x2, int y);

/**
 * @brief Creates a single part of the snake.
 * 
 * This function allocates memory for a Snake structure and initializes it
 * with the given parameters.
 * 
 * @param index Index of the snake part.
 * @param x X-coordinate of the snake part.
 * @param y Y-coordinate of the snake part.
 * 
 * @return Pointer to the created Snake structure.
 */
Snake* create_snake_part(int index, int x, int y);

/**
 * @brief Adds a new part to the snake.
 * 
 * This function links a new snake part to the existing tail of the snake.
 * 
 * @param old_tail Pointer to the current tail of the snake.
 * @param new_tail Pointer to the new tail to be added.
 */
void add_snake(Snake* old_tail, Snake* new_tail);

/**
 * @brief Draws the entire snake on the screen.
 * 
 * This function recursively draws each part of the snake by filling a square
 * of SQUARE_SIZE at the snake part's coordinates.
 * 
 * @param head Pointer to the head of the snake.
 * @param color Color to draw the snake.
 */
void draw_snake(Snake* head, unsigned short color);

/**
 * @brief Moves the body of the snake.
 * 
 * This function recursively updates the coordinates of each part of the snake
 * to follow the previous part.
 * 
 * @param tail Pointer to the tail of the snake.
 */
void move_snakes_body(Snake* tail);

/**
 * @brief Moves the head of the snake.
 * 
 * This function updates the coordinates of the snake's head based on the
 * given direction.
 * 
 * @param snake_dir Direction to move the head (1: left, 2: up, 3: right, 4: down).
 * @param head Pointer to the head of the snake.
 */
void move_snakes_head(int snake_dir, Snake* head);

#endif // SNAKE_PROP_H
