/*
 * flash.h
 *
 *  Created on: Nov 3, 2017
 *      Author: schwin
 */

#ifndef FLASH_H_
#define FLASH_H_
#include "stm32l4xx_hal.h"


#define FLASH_BLOCK1_CS_PORT GPIOC
#define FLASH_BLOCK1_CS_PIN GPIO_PIN_8
#define FLASH_BLOCK2_CS_PORT GPIOC
#define FLASH_BLOCK2_CS_PIN GPIO_PIN_7

#define FLASH_BLOCK1_CHIP_ENABLE() HAL_GPIO_WritePin(FLASH_BLOCK1_CS_PORT,FLASH_BLOCK1_CS_PIN,GPIO_PIN_RESET)
#define FLASH_BLOCK1_CHIP_DISABLE() HAL_GPIO_WritePin(FLASH_BLOCK1_CS_PORT,FLASH_BLOCK1_CS_PIN,GPIO_PIN_SET)

#define FLASH_BLOCK2_CHIP_ENABLE() HAL_GPIO_WritePin(FLASH_BLOCK2_CS_PORT,FLASH_BLOCK2_CS_PIN,GPIO_PIN_RESET)
#define FLASH_BLOCK2_CHIP_DISABLE() HAL_GPIO_WritePin(FLASH_BLOCK2_CS_PORT,FLASH_BLOCK2_CS_PIN,GPIO_PIN_SET)

/*cypress specific parameter*/
#define PAGE_SIZE 0x200 //512 byte
#define SECTOR_SIZE 0x40000 //256kb
//READ command
#define RDID 0x9F /*Read ID command*/
#define REMS 0x90 /*Read electronic manufacturer Signature*/
#define RES 0xAB /*Read electronic signature*/
#define RSFDP 0x5A /*Read serial flash discoverable parmaeters*/
#define READ4 0x13 /*Read 4 byte address*/
//WRITE command
#define WRDI 0x04 /*Write disable*/
#define WREN 0x06 /*Write enable*/
#define PP4 0x12 /*WRITE PAGE*/
//ERASE command
#define ER4SE 0xDC /* Erase 256kb sector (4-byte address)*/

typedef enum
{
  FLASH_AVAILABLE = 0,
  FLASH_ERROR
}FLASH_State;

FLASH_State verify_flash_memory(SPI_HandleTypeDef* hspi);
FLASH_State master_EraseFlash(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint16_t sectors);
FLASH_State Master_WriteToFlash_Page(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint8_t *pData, uint16_t pages);
FLASH_State Master_ReadFromFlash(SPI_HandleTypeDef* hspi,uint32_t flash_addr, uint8_t *pData, uint16_t size);

#endif /* FLASH_H_ */
