/*
 * user_interface.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Schwin
 */

#include "user_interface.h"
extern frame frame_lookup[10];
void init_userinterface()
{
	frame_lookup[0] = {.previous = 0,0,0,1,1,11,&to_child,&stay};
	return;
}

