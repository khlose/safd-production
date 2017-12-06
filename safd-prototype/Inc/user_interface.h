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


typedef struct frame
{
	uint8_t previous;
	uint8_t next;
	uint8_t parent;
	uint8_t child;
	uint8_t a_index;
	uint8_t b_index;
	void (* a_action)(void);
	void (* b_action)(void);
}frame;





void init_userinterface();
void to_child();
void stay();



#endif /* USER_INTERFACE_H_ */
