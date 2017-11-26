/*
 * util.c
 *
 *  Created on: Oct 19, 2017
 *      Author: Schwin Pinkoh
 */

#include "util.h"

float determine_runtime(int avgOver,triple_ring_buffer* buffer)
{
	uint32_t tick_i = HAL_GetTick();
	int i;
	int result=0;
	int fetch_status = 0;
	triplet fetched_ang_v;

	for(i = 0; i < avgOver; ++i)
	{
		int fetch_status = fetch(buffer,&fetched_ang_v);
		//function to average over goes here
		result = detection_angular_velocity();

	}
	/*Current time = 0.75 ms*/
	uint32_t tick_t = HAL_GetTick();
	float time_per_calc = (float)(tick_t - tick_i)/avgOver;

	return time_per_calc;
}


