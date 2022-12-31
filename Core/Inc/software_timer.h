/*
 * software_timer.h
 *
 *  Created on: Dec 23, 2022
 *      Author: admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

//#define TIMER

extern int state; //0: Led 0 ON - 1: Led 1 ON

extern int timer0_counter;
extern int timer1_counter;
extern int timer0_flag;
extern int timer1_flag;
extern int TIME_CYCLE;

void setTimer0(int duration);
void setTimer1(int duration);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
