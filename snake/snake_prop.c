#include "snake_prop.h"
#include "draw_px_or_char.h"

#include <stdlib.h>
#include <stdio.h>

#define SQUARE_SIZE 15

SnakeBig* build_snake(int lenght, int dir, int curr_dir, int prev_dir, unsigned short color, int x1, int x2, int y) {
    SnakeBig* big_snake = (SnakeBig*)malloc(sizeof(SnakeBig));
    if (big_snake == NULL) {
        exit(-2);
    }

    big_snake->lenght = lenght;
    big_snake->dir = dir;
    big_snake->curr_dir = curr_dir;
    big_snake->prev_dir = prev_dir;
    big_snake->color = color;
    Snake* snake = create_snake_part(0, x1, y);
    Snake* tail = create_snake_part(1, x2, y);
    add_snake(snake, tail);
    big_snake->snake = snake;
    big_snake->tail = tail;

    return big_snake;
}

Snake* create_snake_part(int index, int x, int y) {
  Snake* new_node = (Snake*)malloc(sizeof(Snake));
  if (new_node == NULL) {
    exit(-1);
  }

  new_node->x = x;
  new_node->y = y;
  new_node->index = index;
  new_node->next = NULL;
  new_node->previous = NULL;

  return new_node;
}

void add_snake(Snake* old_tail, Snake* new_tail) {
  
  old_tail->next = new_tail;
  new_tail->previous = old_tail;
  
}

void draw_snake(Snake* head, unsigned short color) {
  if (head == NULL) {
      return;
  }
    for (int j = 0; j < SQUARE_SIZE; j++) {
      for (int i = 0; i < SQUARE_SIZE; i++) {
          draw_pixel(i+head->x,j+head->y, color);
      }
    }
    draw_snake(head->next, color);
}

void move_snakes_body(Snake* tail) {
  if (tail->index == 0) {
    return;
  }
    tail->x = tail->previous->x;
    tail->y = tail->previous->y;
    
    move_snakes_body(tail->previous);
}

void move_snakes_head(int snake_dir, Snake* head) {
    switch(snake_dir) {
      case 1: 
        head->x -= SQUARE_SIZE;
        break;
      case 2:
        head->y -= SQUARE_SIZE;
        break;
      case 3:
        head->x += SQUARE_SIZE;
        break;
      case 4:
        head->y += SQUARE_SIZE;
        break;
    }
}
