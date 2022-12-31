/*
 * fsm_led_clock.h
 *
 *  Created on: Dec 23, 2022
 *      Author: admin
 */

#ifndef INC_FSM_LED_CLOCK_H_
#define INC_FSM_LED_CLOCK_H_

#define INIT 10
#define MODE_1 11
#define MODE_2 12
#define MODE_3 13
#define MODE_4 14

extern uint16_t ledPin[12];
extern GPIO_TypeDef* ledPort[12];


void turnOnAll();
void turnOffAll();
void setNumberOnClock(int num);
void clearNumberOnClock(int num);
void modify_traffic_buffer(int mode, int hour, int minute, int second);
void display_hour_led();
void display_minute_led();
void display_second_led();
void change_mode_buffer(int mode);
void increase_led_hour();
void increase_led_minute();
void increase_led_second();
void decrease_led_hour();
void decrease_led_minute();
void decrease_led_second();
void update_led();
void display_led();
void fsm_led_clock();

#endif /* INC_FSM_LED_CLOCK_H_ */
