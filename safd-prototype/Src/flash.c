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
	FLASH_BLOCK1_CHIP_ENABLE();

	//transmit
	if(HAL_SPI_TransmitReceive(hspi, commands,rec_temp, 8, 1000) != HAL_OK)
	{
		//error here
		_Error_Handler(__FILE__, __LINE__);
	}
	FLASH_BLOCK1_CHIP_DISABLE();

	//now our rec_temp is populated, we can check the return value from it

	if(rec_temp[1] != 1 || rec_temp[2] != 2 || rec_temp[3] != 32 || rec_temp[4] != 77 || rec_temp[6] != 128)
	{
		flash_status = FLASH_ERROR;
	}

	return flash_status;
}

FLASH_State master_EraseFlash(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint16_t sectors)
{
	uint8_t commands[10];
	FLASH_State flash_status = FLASH_AVAILABLE;
	commands[0] = WREN;
	uint8_t rec_temp[7];
	FLASH_BLOCK1_CHIP_ENABLE();

	//Enable write to erase
	if(HAL_SPI_TransmitReceive(hspi, commands,rec_temp, 1, 1000) != HAL_OK)
	{
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
	}
	FLASH_BLOCK1_CHIP_DISABLE(); //must disable first to enable chip writing.

	//Start erasing sectors
	for(uint16_t i=0; i < sectors;i++)
	{
		commands[0] = ER4SE;
		//4-byte address
		commands[1] = (flash_addr>>24) & 0xff;
		commands[2] = (flash_addr>>16) & 0xff;
		commands[3] = (flash_addr>>8) & 0xff;
		commands[4] = (flash_addr) & 0xff;

		FLASH_BLOCK1_CHIP_ENABLE();
		if(HAL_SPI_TransmitReceive(hspi, commands,rec_temp, 1, 1000) != HAL_OK)
		{
			flash_status = FLASH_ERROR;
			_Error_Handler(__FILE__, __LINE__);
		}

		FLASH_BLOCK1_CHIP_DISABLE();
		//wait until the write is done
		/*
		if(CheckIsWritingReadingComplete(30000)!=0)//in testing it needs 21370=2.1s for 1 sector. Erase of one sector may take 130ms
		{
			flash_status = FLASH_ERROR;
			_Error_Handler(__FILE__, __LINE__);
		}
		 */
		HAL_Delay(4000);
		flash_addr+=0x40000; //4*64*1024; 256kB, move to the next sector (each sector's size = 256 kb)

	}
	return flash_status;
}


//write to flash. must be pages. Each page is 512 byte
FLASH_State Master_WriteToFlash_Page(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint8_t *pData, uint16_t pages)
{
	//enable writing first
	//send command to chip
	uint8_t commands[10+PAGE_SIZE];
	uint8_t RxDummy[2048];//max 2kB at a time
	FLASH_State flash_status = FLASH_AVAILABLE;
	uint8_t ReceiveTemp[7];

	commands[0]=WREN;
	FLASH_BLOCK1_CHIP_ENABLE(); //enable the chip, CS=0
	if(HAL_SPI_TransmitReceive(hspi, commands,ReceiveTemp, 1, 1000) != HAL_OK)
	{
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
	}
	FLASH_BLOCK1_CHIP_DISABLE(); //must disable first to enable chip writing.
	//start to write data to flash
	for(uint16_t i=0;i<pages;i++)
	{
	//write addr , then send data
	commands[0]=PP4;//page write
	commands[1]=(flash_addr>>24)&0xff; //highest byte first
	commands[2]=(flash_addr>>16)&0xff; //2nd byte
	commands[3]=(flash_addr>>8)&0xff; //3rd byte
	commands[4]=(flash_addr)&0xff; //last byte
	//copy the data to array to send
	for(uint16_t p0=0;p0<PAGE_SIZE;p0++)
	{
		commands[5+p0]=pData[p0];//copy to command array
	}
	FLASH_BLOCK1_CHIP_ENABLE(); //enable the chip, CS=0
	if(HAL_SPI_TransmitReceive(hspi, commands,RxDummy,PAGE_SIZE+5,1000) != HAL_OK)
	{
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
	}
	FLASH_BLOCK1_CHIP_DISABLE(); //must disable first to enable chip writing.

	//check status
	/*
	if(CheckIsWritingReadingComplete(100)!=0)//10ms. we use poling mode to write data, should be done after calling the code
	{
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
	}
	 */
	flash_addr+=PAGE_SIZE;
	pData+=PAGE_SIZE;//move to next page
	}
	return flash_status;

}


FLASH_State Master_ReadFromFlash(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint8_t *pData, uint16_t size)
{
 //enable writing first
//send command to chip
 uint8_t commands[10+PAGE_SIZE*4];
 uint8_t RxDummy[10+PAGE_SIZE*4];//max 1kB at a time
	FLASH_State flash_status = FLASH_AVAILABLE;
 commands[0]=READ4;//page read
 commands[1]=(flash_addr>>24)&0xff; //highest byte first
 commands[2]=(flash_addr>>16)&0xff; //2nd byte
 commands[3]=(flash_addr>>8)&0xff; //3rd byte
 commands[4]=(flash_addr)&0xff; //last byte
 FLASH_BLOCK1_CHIP_ENABLE(); //enable the chip, CS=0
 if(HAL_SPI_TransmitReceive(&hspi, commands,RxDummy, size+5,1000) != HAL_OK)
 {
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
 }
 FLASH_BLOCK1_CHIP_DISABLE(); //must disable first to enable chip writing.

 //check status
 /*
 if(CheckIsWritingReadingComplete(100)!=0)//10ms. we use poling mode to write data, should be done after calling the code
 {
		flash_status = FLASH_ERROR;
		_Error_Handler(__FILE__, __LINE__);
 }
 */

 //transfer to destination buffer
 for(uint16_t p0=0;p0<size;p0++)
 {
 pData[p0]=RxDummy[5+p0];//there are 5 dummy data in the Rx buffer
 }
//done
 return flash_status;
}

