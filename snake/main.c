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
#include "singleplayer.h"
#include "multiplayer.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
unsigned char *mem_base;

int main(int argc, char *argv[]) {  
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
  ptr = 0;

  // remove background, initialize on 0
  for (int i = 0; i < 320 ; i++) {
    for (int j = 0; j < 480 ; j++) {
      c = 0;
      fb[ptr]=c;
      parlcd_write_data(parlcd_mem_base, fb[ptr++]);
    }
  }
  

  while (1) {
    /*
    This will show a menu scene
    */
    int game_mode = show_menu();

      /*
      Choosing a game mode
      */
      switch(game_mode) {
        // Single classic
        case 1:
          singleplayer(false);
          break;
        // Single time rush
        case 2:
          singleplayer(true);
          break;
        // Multi classic
        case 3:
          multiplayer(false);
          break;
        // Multi time rush
        case 4:
          multiplayer(true);
          break;
      }

      // If the EXIT button was pressed (in the menu)
      if (game_mode == 5) {
        break; // Ending the whole game
      }
  }

    // Setting the screen black
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, 0);
    }
 
  printf("Program ended\n");
 
  return 0;
  }
