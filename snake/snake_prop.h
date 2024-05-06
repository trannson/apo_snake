#ifndef SNAKE_PROP_H
#define SNAKE_PROP_H

typedef struct Snake {
  int index;
  int x;
  int y;
  struct Snake* next;
  struct Snake* previous;
} Snake;

typedef struct SnakeBig {
    int lenght;
    int dir;
    int curr_dir;
    int prev_dir;
    unsigned short color;
    Snake* snake;
    Snake* tail;
} SnakeBig;

SnakeBig* build_snake(int lenght, int dir, int curr_dir, int prev_dir, unsigned short color, int x1, int x2, int y);

Snake* create_snake_part(int index, int x, int y);

void add_snake(Snake* head, Snake* new_node);

void draw_snake(Snake* head, unsigned short);

void move_snakes_body(Snake* tail);

void move_snakes_head(int snake_dir, Snake* snake);

#endif // SNAKE_PROP_H
