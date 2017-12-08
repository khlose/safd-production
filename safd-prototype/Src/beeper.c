/*
 * beeper.c
 *
 *  Created on: Dec 7, 2017
 *      Author: Station13
 */

#include "beeper.h"

void HAL_TIM_PeriodBeeper(TIM_HandleTypeDef* htim4,int duration){
	HAL_TIM_PWM_Start(htim4, TIM_CHANNEL_2);
		HAL_Delay(duration * 100);
		HAL_TIM_PWM_Stop(htim4, TIM_CHANNEL_2);
		HAL_Delay(duration * 100);
}

