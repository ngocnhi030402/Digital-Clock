/*
 * button.c
 *
 *  Created on: Dec 22, 2022
 *      Author: admin
 */
#include "button.h"
#include "gpio.h"
// DURATION FOR LONG PRESSED
#define LONG_PRESSED_DURATION 100

#define IS_PRESSED 0
#define IS_RELEASED 1

// store button state for debouncing
int KeyReg0[NO_OF_BUTTONS] = {IS_RELEASED, IS_RELEASED, IS_RELEASED,IS_RELEASED};
int KeyReg1[NO_OF_BUTTONS] = {IS_RELEASED, IS_RELEASED, IS_RELEASED,IS_RELEASED};
int KeyReg2[NO_OF_BUTTONS] = {IS_RELEASED, IS_RELEASED, IS_RELEASED,IS_RELEASED};
int KeyReg3[NO_OF_BUTTONS] = {IS_RELEASED, IS_RELEASED, IS_RELEASED,IS_RELEASED};

int TimeOutForKeyPress[NO_OF_BUTTONS] = {500, 500, 500, 500};
int flagBtn[NO_OF_BUTTONS];

void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];

		// checking for which button is being read
		switch(i){
			case BUTTON1:
				KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
				break;

			case BUTTON2:
				KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
				break;

			case BUTTON3:
				KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
				break;

			default:
				break;
		}

		if((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if(KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];

				if(KeyReg3[i] == IS_PRESSED){
					TimeOutForKeyPress[i] = 500;
					subKeyProcess(i);
				}
			}
			else{
				TimeOutForKeyPress[i] --;
				if (TimeOutForKeyPress[i] == 0){
					KeyReg3[i] = IS_RELEASED;
				}
			}
		}
	}
}

void subKeyProcess(int index){
	flagBtn[index] = 1;
}

int isBtnPressed(int index){
	if (flagBtn[index] == 1){
		flagBtn[index] = 0;
		return 1;
	}
	return 0;
}

