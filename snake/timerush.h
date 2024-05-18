/**
 * @file timerush.h
 * @author Marek Strympl
 * @author Son Ngoc Tran
 * @brief Header file for timerush mode to work
*/

#ifndef TIME_RUSH_H
#define TIME_RUSH_H

/**
 * @brief Decreases the time amount if ticks exceed 5.
 *
 * This function decreases the `time_amount` by 1 and resets `ticks` to 0
 * if `ticks` is greater than 5.
 *
 * @param time_amount Pointer to the time amount to be decreased.
 * @param ticks Pointer to the tick count.
 */
void decrease_time(int* time_amount, int* ticks);

/**
 * @brief Resets the time amount to 8.
 *
 * This function sets the `time_amount` to 8.
 *
 * @param time_amount Pointer to the time amount to be reset.
 */
void reset_time(int* time_amount);

/**
 * @brief Displays the time amount at a specified position on the screen.
 *
 * This function displays the `time_amount` at coordinates (450, 20)
 * with a specific text color and font size.
 *
 * @param time_amount The time amount to be displayed.
 */
void display_time1(int time_amount);

/**
 * @brief Displays the time amount at a specified position on the screen.
 *
 * This function displays the `time_amount` at coordinates (20, 20)
 * with a specific text color and font size.
 *
 * @param time_amount The time amount to be displayed.
 */
void display_time2(int time_amount);

#endif // TIME_RUSH_H