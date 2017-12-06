/*
 * user_interface.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Schwin
 */

#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "ssd1306.h"
#include "stm32l4xx_hal.h"

extern oled_message central_message;

typedef struct frame
{
	uint8_t previous;
	uint8_t next;
	uint8_t parent;
	uint8_t child;
	uint8_t a_index;
	void (* a_function)(void);
	uint8_t b_index;
	void (* b_function)(void);
}frame;

typedef struct oled_message
{
	char string button_a[];
	char string_button_b[];
	char string_battery[];
	char center_message[];
}oled_message;

void init_userinterface();




#endif /* USER_INTERFACE_H_ */
