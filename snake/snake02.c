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
#include "snake_prop.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
unsigned char *mem_base;

/*
Each snake will be make of array of these squares
int x is each square x coordinate
int y is each square y coordinate
x and y are coordinates of the top left corner of the square
*/

int main(int argc, char *argv[]) {  

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

/*
  Snake's direction
  1 means LEFT, 2 means TOP, 3 means RIGHT, 4 means DOWN
*/
  int blue_snake_len = 2;
  int blue_snake_dir = 1;
  int blue_snake_curr_dir = ((r&0xff));
  int blue_snake_prev_dir = ((r&0xff));
  unsigned short blue_snake_clr = 0x7ff;

  Snake* blue_snake = create_snake_part(0, 150, 150);
  Snake* blue_tail = create_snake_part(1, 165, 150);
  add_snake(blue_snake, blue_tail);

  int red_snake_len = 2;
  int red_snake_dir = 4;
  int red_snake_curr_dir = (((r>>16)&0xff));
  int red_snake_prev_dir = (((r>>16)&0xff));
  unsigned short red_snake_clr = 0xF000;
  
  Snake* red_snake = create_snake_part(0, 50, 50);
  Snake* red_tail = create_snake_part(1, 35, 50);
  add_snake(red_snake, red_tail);
  
  // FOOD
  bool eaten = false;
  int apple_x = 200;
  int apple_y = 200;

  while (1) {
 
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // button pressed
    if ((r&0x7000000)!=0) {
      printf("k\n");
    }

    blue_snake_curr_dir = ((r&0xff)); // blue knob
    red_snake_curr_dir = (((r>>16)&0xff));

    blue_snake_dir = modify_while_rotating(blue_snake_curr_dir, blue_snake_prev_dir, blue_snake_dir, 4);
    red_snake_dir = modify_while_rotating(red_snake_curr_dir, red_snake_prev_dir, red_snake_dir, 4);

    blue_snake_prev_dir = blue_snake_curr_dir;
    red_snake_prev_dir = red_snake_curr_dir;

    move_snakes_body(blue_tail);
    move_snakes_body(red_tail);

    move_snakes_head(blue_snake_dir, blue_snake);
    move_snakes_head(red_snake_dir, red_snake);
    
    // Black screen
    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u; 
    }
    
    draw_snake(blue_snake, blue_snake_clr);
    draw_snake(red_snake, red_snake_clr);
    draw_apple(apple_x, apple_y);

    int gloo = check_collisions(blue_snake->x, blue_snake->y, red_snake->x, red_snake->y, &apple_x, &apple_y);

    if (gloo == 2 || gloo == 3) {
      break;
    }

    if (gloo == 4) {
      Snake* tmp = create_snake_part(blue_tail->index++, blue_tail->x, blue_tail->y);
      add_snake(blue_tail, tmp);
      blue_tail = tmp;
      blue_snake_len++;
    }
    
    // // draw apple
    //   if (eaten) {
    //     make_food(&apple_x, &apple_y);
    //     add_snake(blue_tail, create_snake_part((blue_tail->index)++, blue_tail->x, blue_tail->y));
    //     blue_tail = blue_tail->next;
      
    

    // if (!check_collisions(blue_snake->x, blue_snake->y)) {
    //   printf("Snake out\n");
    //   break;
    // }
    // if (!check_collisions(red_snake->x, red_snake->y)) {
    //   printf("Snake out\n");
    //   break;
    // }

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
