/*
 * fsm_led_clock.c
 *
 *  Created on: Dec 23, 2022
 *      Author: admin
 */


#include "main.h"
#include "gpio.h"
#include "button.h"
#include "global.h"
#include "software_timer.h"
#include "fsm_led_clock.h"


uint16_t ledPin[12] = {
		LED2_Pin,
		LED3_Pin,
		LED4_Pin,
		LED5_Pin,
		LED6_Pin,
		LED7_Pin,
		LED8_Pin,
		LED9_Pin,
		LED10_Pin,
		LED11_Pin,
		LED12_Pin,
		LED1_Pin
};

GPIO_TypeDef* ledPort[12] = {
		LED2_GPIO_Port,
		LED3_GPIO_Port,
		LED4_GPIO_Port,
		LED5_GPIO_Port,
		LED6_GPIO_Port,
		LED7_GPIO_Port,
		LED8_GPIO_Port,
		LED9_GPIO_Port,
		LED10_GPIO_Port,
		LED11_GPIO_Port,
		LED12_GPIO_Port,
		LED1_GPIO_Port

};

enum ledNum{
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED7,
	LED8,
	LED9,
	LED10,
	LED11,
	LED12
};

void turnOnAll(){
	for(int i = 0; i < 12; i++){
		HAL_GPIO_WritePin(ledPort[i], ledPin[i], GPIO_PIN_RESET);
	}
}

void turnOffAll(){
	for(int i = 0; i < 12; i++){
		HAL_GPIO_WritePin(ledPort[i], ledPin[i], GPIO_PIN_SET);
	}
}

void setNumberOnClock(int num){
	HAL_GPIO_WritePin(ledPort[num], ledPin[num], GPIO_PIN_RESET);
}

void clearNumberOnClock(int num){
	HAL_GPIO_WritePin(ledPort[num], ledPin[num], GPIO_PIN_SET);
}

void display_hour_led(){
	setNumberOnClock(LED1);
	setNumberOnClock(LED4);
	setNumberOnClock(LED7);
	setNumberOnClock(LED10);
}
void display_minute_led(){
	setNumberOnClock(LED12);
	setNumberOnClock(LED1);
	setNumberOnClock(LED2);
	setNumberOnClock(LED6);
	setNumberOnClock(LED7);
	setNumberOnClock(LED8);
}
void display_second_led(){
	setNumberOnClock(LED3);
	setNumberOnClock(LED4);
	setNumberOnClock(LED5);
	setNumberOnClock(LED9);
	setNumberOnClock(LED10);
	setNumberOnClock(LED11);
}

void increase_led_hour(){
	temp_hour++;
	if(temp_hour == 12) temp_hour = 0;
	UARTOutput(temp_hour);
}

void increase_led_minute(){
	temp_minute++;
	if(temp_minute == 60) {
		temp_minute = 0;
		temp_hour++;
	}
	UARTOutput(temp_minute);
}

void increase_led_second(){
	temp_second++;
	if(temp_second == 60) {
		temp_second = 0;
		temp_minute++;
	}
	UARTOutput(temp_second);
}
void decrease_led_hour(){
	if(temp_hour == 0) temp_hour = 11;
	else temp_hour--;
	UARTOutput(temp_hour);
}

void decrease_led_minute(){
	if(temp_minute == 0) temp_minute = 59;
	else temp_minute--;
	UARTOutput(temp_minute);

}

void decrease_led_second(){
	if(temp_second == 0) temp_second = 59;
	else temp_second--;
	UARTOutput(temp_second);
}

void update_led(){
	second = temp_second;
	minute = temp_minute;
	hour = temp_hour;
}
void display_led(){
	if(timer0_flag == 1){
		  if (second == 59){
			  second = 0;
			  minute++;
		  }
		  if (minute == 59){
			  minute = 0;
			  hour++;
		  }
		  if (hour == 12){
			  hour = 0;
		  }

		  turnOffAll();
		  setNumberOnClock(second/5);
		  setNumberOnClock(minute/5);
		  setNumberOnClock(hour);
		  setTimer0(100);

		  second++;
		  temp_second = second;
		  temp_minute = minute;
		  temp_hour = hour;
		  update_led();
	}
}


void fsm_led_clock(){
	switch(current_mode){
		case INIT:
			turnOffAll();
			current_mode = MODE_1;
			break;

		case MODE_1:
			display_led();

			// when pressing button 1, change to next mode
			if(isBtnPressed(BUTTON1)){
				current_mode = MODE_2;
				setTimer1(500);
				turnOffAll();
			}
			break;

		case MODE_2:
			display_second_led();

			// when pressing button 1, change to next mode
			if(isBtnPressed(BUTTON1)){
				current_mode = MODE_3;
				setTimer1(500);
				turnOffAll();
			}

			if(isBtnPressed(BUTTON2)) {
				increase_led_second();
			}
			if(isBtnPressed(BUTTON3)) decrease_led_second();

			update_led();
			break;

		case MODE_3:
			display_minute_led();

			// when pressing button 1, change to next mode
			if(isBtnPressed(BUTTON1)){
				current_mode = MODE_4;
				setTimer1(500);
				turnOffAll();
			}
			if(isBtnPressed(BUTTON2)) increase_led_minute();
			if(isBtnPressed(BUTTON3)) decrease_led_minute();

			update_led();
			break;

		case MODE_4:
			display_hour_led();

			// when pressing button 1, change to next mode
			if(isBtnPressed(BUTTON1)){
				current_mode = MODE_1;
				turnOffAll();
			}
			if(isBtnPressed(BUTTON2)) increase_led_hour();
			if(isBtnPressed(BUTTON3)) decrease_led_hour();
			update_led();
			break;

		default:
			break;

	}
}
