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
typedef struct {
  int x;
  int y;
} squares;

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
int snake_length = 3;

squares snake[snake_length];
    // initialized snake coords
    for (int k = 0; k < snake_length; k++) {
      snake[k].x = 150 - square_size;
      snake[k].y = 150;
    }

int blue_snake_len = 3;
int blue_snake_dir = 1;
int blue_snake_curr_dir = ((r&0xff));
int blue_snake_prev_dir = ((r&0xff));

if (player2) {
  int red_snake_len = 3;
  int red_snake_dir = 4;
  int red_snake_curr_dir;
  int red_snake_prev_dir;
}

/*
  Snake's direction
  1 means LEFT, 2 means TOP, 3 means RIGHT, 4 means DOWN
*/
int snake_direction = 1;

int curr_snake_dir = ((r&0xff));
int prev_snake_dir = ((r&0xff));

// FOOD
bool eaten = false;
int apple_x = 200;
int apple_y = 200;

  while (1) {
    squares old_head = snake[0];
 
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // button pressed
    if ((r&0x7000000)!=0) {
      printf("k\n");
    }

    // moving head
    switch(snake_direction) {
      case 1: 
        snake[0].x -= square_size;
        break;
      case 2:
        snake[0].y -= square_size;
        break;
      case 3:
        snake[0].x += square_size;
        break;
      case 4:
        snake[0].y += square_size;
        break;
    }
    
    curr_snake_dir = ((r&0xff)); // blue knob

    snake_direction = modify_while_rotating(curr_snake_dir, prev_snake_dir, snake_direction, 4);

    prev_snake_dir = curr_snake_dir;
    
    // yy = (((r>>16)&0xff)*320)/256; // green knob

    // moving tail
      for (int k = 1; k < snake_length; k++) {
        squares temp = snake[k]; // saving tail square into temp
        // setting tail squares to be old head square
        snake[k].x = old_head.x; 
        snake[k].y = old_head.y;

        // saved tail temp is a "new" old head for the tail square behind him
        old_head = temp; 
    }

    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u; 
    }
    
    // draw square
    for (int k = 0; k < snake_length; k++) {
      for (j=0; j<square_size; j++) {
        for (i=0; i<square_size; i++) {
            draw_pixel(i+snake[k].x,j+snake[k].y,0x7ff);
        }
      }
    }
eaten = apple_collision(snake[0].x, snake[1].y, apple_x, apple_y);
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

    if (!check_collisions(snake[0].x, snake[0].y)) {
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
