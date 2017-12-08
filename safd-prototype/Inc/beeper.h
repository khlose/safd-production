/*
 * beeper.h
 *
 *  Created on: Dec 7, 2017
 *      Author: Station13
 */

#ifndef BEEPER_H_
#define BEEPER_H_

#include "stm32l4xx_hal.h"

void HAL_TIM_PeriodBeeper(TIM_HandleTypeDef* htim4,int duration);

#endif /* BEEPER_H_ */
