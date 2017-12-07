/*
 * user_interface.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Schwin
 */

#include "user_interface.h"



void init_userinterface()
{
	current_frame_index = 0;

	frame_lookup[0].previous = 0;
	frame_lookup[0].next = 0;
	frame_lookup[0].parent = 0;
	frame_lookup[0].child = 1;
	frame_lookup[0].a_index = 1;
	frame_lookup[0].b_index = 0;
	frame_lookup[0].a_action = to_child;
	frame_lookup[0].b_action = stay;
	frame_lookup[0].a_string = "menu";
	frame_lookup[0].b_string = "home";
	frame_lookup[0].main_msg = "status:unarmed";

	frame_lookup[0].sub_msg = "";


	frame_lookup[1].previous = 6;
	frame_lookup[1].next = 3;
	frame_lookup[1].parent = 0;
	frame_lookup[1].child = 2;
	frame_lookup[1].a_index = 2;
	frame_lookup[1].b_index = 0;
	frame_lookup[1].a_action = to_child;
	frame_lookup[1].b_action = to_parent;
	frame_lookup[1].a_string = "confirm";
	frame_lookup[1].b_string = "back";
	frame_lookup[1].main_msg = "arm the system";
	frame_lookup[1].sub_msg = "";


	frame_lookup[2].previous = 11;
	frame_lookup[2].next = 11;
	frame_lookup[2].parent = 1;
	frame_lookup[2].child = 11;
	frame_lookup[2].a_index = 0;
	frame_lookup[2].b_index = 1;
	frame_lookup[2].a_action = to_root;
	frame_lookup[2].b_action = to_parent;
	frame_lookup[2].a_string = "confirm";
	frame_lookup[2].b_string = "back";
	frame_lookup[2].main_msg = "would you like to arm";
	frame_lookup[2].sub_msg = "the system?";

	frame_lookup[3].previous = 1;
	frame_lookup[3].next = 4;
	frame_lookup[3].parent = 0;
	frame_lookup[3].child = 11;
	frame_lookup[3].a_index = 0;
	frame_lookup[3].b_index = 0;
	frame_lookup[3].a_action = stay;
	frame_lookup[3].b_action = to_root;
	frame_lookup[3].a_string = "";
	frame_lookup[3].b_string = "back";
	frame_lookup[3].main_msg = "battery level:";
	frame_lookup[3].sub_msg = "";

	frame_lookup[4].previous = 3;
	frame_lookup[4].next = 7;
	frame_lookup[4].parent = 0;
	frame_lookup[4].child = 5;
	frame_lookup[4].a_index = 5;
	frame_lookup[4].b_index = 0;
	frame_lookup[4].a_action = to_child;
	frame_lookup[4].b_action = to_root;
	frame_lookup[4].a_string = "confirm";
	frame_lookup[4].b_string = "back";
	frame_lookup[4].main_msg = "record data";
	frame_lookup[4].sub_msg = "";

	frame_lookup[5].previous = 11;
	frame_lookup[5].next = 11;
	frame_lookup[5].parent = 4;
	frame_lookup[5].child = 11;
	frame_lookup[5].a_index = 0;
	frame_lookup[5].b_index = 0;
	frame_lookup[5].a_action = stay;
	frame_lookup[5].b_action = stay;
	frame_lookup[5].a_string = "";
	frame_lookup[5].b_string = "";
	frame_lookup[5].main_msg = "enabled";
	frame_lookup[5].sub_msg = "";

	frame_lookup[6].previous = 7;
	frame_lookup[6].next = 1;
	frame_lookup[6].parent = 0;
	frame_lookup[6].child = 11;
	frame_lookup[6].a_index = 11;
	frame_lookup[6].b_index = 0;
	frame_lookup[6].a_action = turn_off;
	frame_lookup[6].b_action = to_root;
	frame_lookup[6].a_string = "confirm";
	frame_lookup[6].b_string = "back";
	frame_lookup[6].main_msg = "power off";
	frame_lookup[6].sub_msg = "";

	frame_lookup[7].previous = 4;
	frame_lookup[7].next = 6;
	frame_lookup[7].parent = 0;
	frame_lookup[7].child = 8;
	frame_lookup[7].a_index = 8;
	frame_lookup[7].b_index = 0;
	frame_lookup[7].a_action = to_child;
	frame_lookup[7].b_action = to_root;
	frame_lookup[7].a_string = "menu";
	frame_lookup[7].b_string = "home";
	frame_lookup[7].main_msg = "transfer data";
	frame_lookup[7].sub_msg = "";

	frame_lookup[8].previous = 11;
	frame_lookup[8].next = 11;
	frame_lookup[8].parent = 7;
	frame_lookup[8].child = 9;
	frame_lookup[8].a_index = 11;
	frame_lookup[8].b_index = 7;
	frame_lookup[8].a_action = stay;
	frame_lookup[8].b_action = to_child;
	frame_lookup[8].a_string = "";
	frame_lookup[8].b_string = "cancel";
	frame_lookup[8].main_msg = "transfer data...";
	frame_lookup[8].sub_msg = "";

	frame_lookup[9].previous = 11;
	frame_lookup[9].next = 11;
	frame_lookup[9].parent = 8;
	frame_lookup[9].child = 11;
	frame_lookup[9].a_index = 0;
	frame_lookup[9].b_index = 0;
	frame_lookup[9].a_action = stay;
	frame_lookup[9].b_action = to_root;
	frame_lookup[9].a_string = "";
	frame_lookup[9].b_string = "";
	frame_lookup[9].main_msg = "transfer interrupted";
	frame_lookup[9].sub_msg = "";
	refresh_oled();

	return;
}


void to_child()
{
	current_frame_index = frame_lookup[current_frame_index].child;
	refresh_oled();
}
void stay()
{

}
void to_root()
{
	current_frame_index = 0;
	refresh_oled();
}
void to_parent()
{
	current_frame_index = frame_lookup[current_frame_index].parent;
	refresh_oled();
}
void to_next()
{
	  if(frame_lookup[current_frame_index].next <10)
	  {
		  current_frame_index = frame_lookup[current_frame_index].next;
		  refresh_oled();
	  }


}
void to_prev()
{
	  if(frame_lookup[current_frame_index].previous <10)
	  {
		  current_frame_index = frame_lookup[current_frame_index].previous;
		  refresh_oled();
	  }
}
void delayed_to_root(int sec)
{
	HAL_Delay(sec*1000);
	current_frame_index = 0;
	refresh_oled();

}
void turn_off()
{
	//assert the pin here
}

void refresh_oled()
{

	SSD1306_Flush();

	SSD1306_Orientation(LCD_ORIENT_180);

	SSD1306_Contrast(127);
	SSD1306_Fill(0x00);
	LCD_PutStr(0,23,frame_lookup[current_frame_index].main_msg,fnt7x10);
	LCD_PutStr(0,scr_height - 15,frame_lookup[current_frame_index].sub_msg,fnt7x10);
	SSD1306_Flush();

}
