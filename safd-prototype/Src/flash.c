/*
 * flash.c
 *
 *  Created on: Nov 3, 2017
 *      Author: schwin
 */

#include "flash.h"


FLASH_State verify_flash_memory(SPI_HandleTypeDef* hspi)
{
	FLASH_State flash_status = FLASH_AVAILABLE;

	uint8_t commands[10];
	uint8_t rec_temp[7];

	commands[0] = RDID;
	FLASH_BLOCK1_CHIP_ENABLE;

	//transmit
	if(HAL_SPI_TransmitReceive(hspi, commands,rec_temp, 8, 1000) != HAL_OK)
	{
		//error here
		_Error_Handler(__FILE__, __LINE__);
	}

	//now our rec_temp is populated, we can check the return value from it

	if(rec_temp[1] != 1 || rec_temp[2] != 2)
	{
		return FLASH_ERROR;
	}

	return flash_status;
}


