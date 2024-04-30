#include "buttons.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Each button (red, green and blue) can be rotated by 360 degrees
Each button's current position is represented by 8 bits (0 - 256)
and one piece of movement (when button clicks) will change the 
number by 4
SENSITIVITY is just to handle smaller changes, when rotating the button
this is caused by game loop refreshes
*/
#define SENSITIVITY 3

/*
@param cur_value: current value of some periphery (button in our case)
@param prev_value: the value of the same periphery, as in cur_value, but the
  value is form the previous refresh of the (while) loop
@param action_num: number of the current action, this value can be from
  1 to @param upper_range, each number represents different action that takes place
@param upper_range: indicates the highest value @param action_num can have

@return action_num: is new action number, which will take place
*/
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range) {

  // Button moved to the LEFT
  if (cur_value < prev_value && (abs(cur_value - prev_value) > SENSITIVITY)) {
    if (action_num == 1) {
      action_num = upper_range;
    } else {
      action_num -= 1;
    }
  // Button moved to the RIGHT
  } else if ((cur_value > prev_value) && (abs(cur_value - prev_value) > SENSITIVITY)) {
    if (action_num == upper_range) {
      action_num = 1;
    } else {
      action_num += 1;
    }
  }
  
  return action_num;
}