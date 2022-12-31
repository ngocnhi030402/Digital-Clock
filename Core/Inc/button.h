/*
 * button.h
 *
 *  Created on: Dec 22, 2022
 *      Author: admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NO_OF_BUTTONS 4

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2

void button_reading(void);
int isBtnPressed(int index);
void subKeyProcess(int index);


#endif /* INC_BUTTON_H_ */
