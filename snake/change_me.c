#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
 
unsigned short *fb;
 
typedef struct {
  int x;
  int y;

} squares;

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 
 
int main(int argc, char *argv[]) {  
  int snake_length = 3;
  int square_size = 15;
  

  squares snake[snake_length];
  // initialized snake coords
  for (int k = 0; k < snake_length; k++) {
    snake[k].x = 150 - square_size;
    snake[k].y = 150;
  }


  unsigned char *parlcd_mem_base, *mem_base;
  int i,j;
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
 
  printf("Hello world\n");
 
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
  int xx=0, yy=0;
  int p = 0, q = 0;
  int dave = 1;
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  int previousdir = ((r&0xff));
  while (1) {
    squares old_head = snake[0];
 
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // button pressed
    if ((r&0x7000000)!=0) {
      break;
    }

    // moving head
    switch(dave) {
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




    
    int snakedir = ((r&0xff)); // blue knob, divide by 256 so that we would get out of
    // printf("%d\n", snakedir);

    // check direction and change perhaps
    if (snakedir < previousdir && (abs(snakedir - previousdir) > 3)) {
      if (dave == 1) {
        dave = 4;
      } else {
        dave -= 1;
      }
    } else if ((snakedir > previousdir) && (abs(snakedir - previousdir) > 3)) {
      if (dave == 4) {
        dave = 1;
      } else {
        dave += 1;
      }
    }

    previousdir = snakedir;

    // printf("xx: %d\n", xx); 
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

    // printf("SNAKE %d X: %d ", 0, snake[0].x);
    // printf("SNAKE %d Y: %d\n", 0, snake[0].y);
    // for (int k = 1; k < snake_length; k++) {
    //   snake[k].x = snake[k-1].x - square_size;
    //   snake[k].y = snake[k-1].y;
    //   printf("SNAKE %d X: %d ", k, snake[k].x);
    //   printf("SNAKE %d Y: %d\n",k,  snake[k].y);
    // }

 
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


 
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
 
  printf("Goodbye world\n");
 
  return 0;
}
