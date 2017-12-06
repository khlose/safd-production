/*
 * user_interface.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Schwin
 */

#include "user_interface.h"
frame frame_lookup[10];

void init_userinterface()
{
	frame_lookup[0].previous = 0;
	frame_lookup[0].next = 0;
	frame_lookup[0].parent = 0;
	frame_lookup[0].child = 0;
	frame_lookup[0].a_index = 1;
	frame_lookup[0].b_index = 0;
	frame_lookup[0].a_action = to_child;
	frame_lookup[0].b_action = stay;

	frame_lookup[1].previous = 6;
	frame_lookup[1].next = 3;
	frame_lookup[1].parent = 0;
	frame_lookup[1].child = 2;
	frame_lookup[1].a_index = 2;
	frame_lookup[1].b_index = 0;
	frame_lookup[1].a_action = to_child;
	frame_lookup[1].b_action = stay;

	frame_lookup[2].previous = 11;
	frame_lookup[2].next = 11;
	frame_lookup[2].parent = 1;
	frame_lookup[2].child = 11;
	frame_lookup[2].a_index = 0;
	frame_lookup[2].b_index = 1;
	frame_lookup[2].a_action = to_child;
	frame_lookup[2].b_action = stay;

	frame_lookup[3].previous = 1;
	frame_lookup[3].next = 4;
	frame_lookup[3].parent = 0;
	frame_lookup[3].child = 11;
	frame_lookup[3].a_index = 0;
	frame_lookup[3].b_index = 0;
	frame_lookup[3].a_action = to_child;
	frame_lookup[3].b_action = stay;

	frame_lookup[4].previous = 3;
	frame_lookup[4].next = 7;
	frame_lookup[4].parent = 0;
	frame_lookup[4].child = 5;
	frame_lookup[4].a_index = 5;
	frame_lookup[4].b_index = 0;
	frame_lookup[4].a_action = to_child;
	frame_lookup[4].b_action = stay;

	frame_lookup[5].previous = 11;
	frame_lookup[5].next = 11;
	frame_lookup[5].parent = 4;
	frame_lookup[5].child = 11;
	frame_lookup[5].a_index = 0;
	frame_lookup[5].b_index = 0;
	frame_lookup[5].a_action = to_child;
	frame_lookup[5].b_action = stay;

	frame_lookup[6].previous = 7;
	frame_lookup[6].next = 1;
	frame_lookup[6].parent = 0;
	frame_lookup[6].child = 11;
	frame_lookup[6].a_index = 11;
	frame_lookup[6].b_index = 0;
	frame_lookup[6].a_action = to_child;
	frame_lookup[6].b_action = stay;

	frame_lookup[7].previous = 4;
	frame_lookup[7].next = 6;
	frame_lookup[7].parent = 0;
	frame_lookup[7].child = 8;
	frame_lookup[7].a_index = 8;
	frame_lookup[7].b_index = 0;
	frame_lookup[7].a_action = to_child;
	frame_lookup[7].b_action = stay;

	frame_lookup[8].previous = 11;
	frame_lookup[8].next = 11;
	frame_lookup[8].parent = 7;
	frame_lookup[8].child = 9;
	frame_lookup[8].a_index = 11;
	frame_lookup[8].b_index = 7;
	frame_lookup[8].a_action = to_child;
	frame_lookup[8].b_action = stay;

	frame_lookup[9].previous = 11;
	frame_lookup[9].next = 11;
	frame_lookup[9].parent = 8;
	frame_lookup[9].child = 11;
	frame_lookup[9].a_index = 0;
	frame_lookup[9].b_index = 0;
	frame_lookup[9].a_action = to_child;
	frame_lookup[9].b_action = stay;

	return;
}


void to_child()
{

}
void stay()
{

}

