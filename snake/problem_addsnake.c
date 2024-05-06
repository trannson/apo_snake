#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

#include "collisions.h"
#include "menu.h"
#include "buttons.h"
#include "draw_px_or_char.h"
#include "food_maker.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
unsigned char *mem_base;

/*
Each snake will be make of array of these squares
int x is each square x coordinate
int y is each square y coordinate
x and y are coordinates of the top left corner of the square
*/
typedef struct Snake {
  int index;
  int x;
  int y;
  struct Snake* next;
  struct Snake* previous;
} Snake;

Snake create_snake(int index, int x, int y);
void add_snake(Snake* head, Snake* new_node);
void draw_snake(Snake* head);
void move_snake(Snake* tail);

int main(int argc, char *argv[]) {  

  int square_size = 15;

  int i,j;
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
 
  printf("Starting program\n");
 
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
    exit(1);
 
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  ptr=0;

  // remove background, initialize on 0
  for (i = 0; i < 320 ; i++) {
    for (j = 0; j < 480 ; j++) {
      c = 0;
      fb[ptr]=c;
      parlcd_write_data(parlcd_mem_base, fb[ptr++]);
    }
  }
 
  struct timespec loop_delay;
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 1000;
  
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  
  /*
  This will show a menu scene
  */
  int game_mode = show_menu();

/*
Choosing game mode
*/
  bool player2;
  bool timerush = false;

  switch(game_mode) {
    // Single classic
    case 1:
      player2 = false;
      break;
    // Single time rush
    case 2:
      player2 = true;
      timerush = true;
      break;
    // Multi classic
    case 3:
      player2 = false;
      break;
    // Multi time rush
    case 4:
      player2 = true;
      timerush = true;
      break;
  }

/*
GAME LOOP
*********************************************************************************************************************************
*/

// squares snake[snake_length];
//     // initialized snake coords
//     for (int k = 0; k < snake_length; k++) {
//       snake[k].x = 150 - square_size;
//       snake[k].y = 150;
//     }

int blue_snake_len = 2;
int blue_snake_dir = 1;
int blue_snake_curr_dir = ((r&0xff));
int blue_snake_prev_dir = ((r&0xff));

Snake blue_snake = create_snake(0, 150, 150);

Snake blue_tail = create_snake(1, 165, 150);

add_snake(&blue_snake, &blue_tail);

// if (player2) {
//   int red_snake_len = 3;
//   int red_snake_dir = 4;
//   int red_snake_curr_dir;
//   int red_snake_prev_dir;
// }

/*
  Snake's direction
  1 means LEFT, 2 means TOP, 3 means RIGHT, 4 means DOWN
*/
//int snake_direction = 1;

// int curr_snake_dir = ((r&0xff));
// int prev_snake_dir = ((r&0xff));

// FOOD
bool eaten = false;
int apple_x = 200;
int apple_y = 200;

  while (1) {
    //squares old_head = snake[0];
 
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // button pressed
    if ((r&0x7000000)!=0) {
      printf("k\n");
    }

    blue_snake_curr_dir = ((r&0xff)); // blue knob

    blue_snake_dir = modify_while_rotating(blue_snake_curr_dir, blue_snake_prev_dir, blue_snake_dir, 4);

    blue_snake_prev_dir = blue_snake_curr_dir;

    // moving head
    switch(blue_snake_dir) {
      case 1: 
        blue_snake.x -= square_size;
        break;
      case 2:
        blue_snake.y -= square_size;
        break;
      case 3:
        blue_snake.x += square_size;
        break;
      case 4:
        blue_snake.y += square_size;
        break;
    }
    
    // yy = (((r>>16)&0xff)*320)/256; // green knob

    // // moving tail
    //   for (int k = 1; k < snake_length; k++) {
    //     squares temp = snake[k]; // saving tail square into temp
    //     // setting tail squares to be old head square
    //     snake[k].x = old_head.x; 
    //     snake[k].y = old_head.y;

    //     // saved tail temp is a "new" old head for the tail square behind him
    //     old_head = temp; 
    // }

    move_snake(&blue_tail);
    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u; 
    }
    
    // draw square
    // for (int k = 0; k < snake_length; k++) {
    //   for (j=0; j<square_size; j++) {
    //     for (i=0; i<square_size; i++) {
    //         draw_pixel(i+snake[k].x,j+snake[k].y,0x7ff);
    //     }
    //   }
    // }
  draw_snake(&blue_snake);
    // for (int k = 0; k < blue_snake_len; k++) {
    //   for (j = 0; j < square_size; j++) {
    //     for (i = 0; i < square_size; i++) {
    //         draw_pixel(i+blue_snake.x,j+blue_snake.y,0x7ff);
    //     }
    //   }
    // }
    
eaten = apple_collision(blue_snake.x, blue_snake.y, apple_x, apple_y);
  // draw apple
    if (eaten) {
      make_food(&apple_x, &apple_y);
      
    } else {
      for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 11; ++j) {
          draw_pixel(i+apple_x, j + apple_y, 0xF000);
        }
      }
    }

    if (!check_collisions(blue_snake.x, blue_snake.y)) {
      printf("Snake out\n");
      break;
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }

/*
END OF GAME LOOP
*********************************************************************************************************************************
*/
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
 
  printf("Program ended\n");
 
  return 0;
}

Snake create_snake(int index, int x, int y) {
  Snake new_node;

  new_node.x = x;
  new_node.y = y;
  new_node.index = index;
  new_node.next = NULL;
  new_node.previous = NULL;

  return new_node;
}

void add_snake(Snake* head, Snake* new_node) {
  
  head->next = new_node;
  new_node->previous = head;
  
}

void draw_snake(Snake* head) {
  int square_size = 15;
  while(head != NULL) {

    for (int j = 0; j < square_size; j++) {
      for (int i = 0; i < square_size; i++) {
          draw_pixel(i+head->x,j+head->y,0x7ff);
      }
    }
    head = head->next;
  }
}

void move_snake(Snake* tail) {
  while (tail->index != 0) {
    tail->x = tail->previous->x;
    tail->y = tail->previous->y;

    move_snake(tail->previous);
  }
  return;
}

