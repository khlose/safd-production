/*
 * max17043.c
 *
 *  Created on: Dec 6, 2017
 *      Author: Station13
 */

#include "max17043.h"

uint8_t quickStart(I2C_HandleTypeDef *hi2c){
	return write16(hi2c,MAX17043_MODE_QUICKSTART, MAX17043_MODE);
}

float getVoltage(I2C_HandleTypeDef *hi2c){
	uint16_t vCell;
	max17043_status stat = read16(hi2c,MAX17043_VCELL,&vCell);

	//vCell = read16(hi2c,MAX17043_VCELL,);
	// vCell is a 12-bit register where each bit represents 1.25mV
	vCell = (vCell) >> 4;

	return ((float) vCell / 800.0);
}

float getSOC(I2C_HandleTypeDef *hi2c)
{
  uint16_t soc;
  float percent;
  max17043_status stat = read16(hi2c,MAX17043_SOC,&soc);
  percent = (soc & 0xFF00) >> 8;
  percent += (float) (((uint8_t) soc) / 256.0);

  return percent;
}

uint8_t write16(I2C_HandleTypeDef *hi2c, uint16_t data, uint8_t address)
{
  uint8_t msb, lsb;
  msb = (data & 0xFF00) >> 8;
  lsb = (data & 0x00FF);
  max17043_status ret = max17043_ok;
  HAL_StatusTypeDef stat = HAL_I2C_Mem_Write(hi2c, write_addr, address, I2C_MEMADD_SIZE_8BIT, &msb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  stat = HAL_I2C_Mem_Write(hi2c, write_addr, address+1, I2C_MEMADD_SIZE_8BIT, &lsb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  return (ret);
}

max17043_status read16(I2C_HandleTypeDef *hi2c, uint8_t address,uint16_t* val)
{
  uint8_t msb= 0xFF;
  uint8_t lsb = 0xFF;
  int16_t timeout = 1000;
  max17043_status ret = max17043_ok;

  HAL_StatusTypeDef stat = HAL_I2C_Mem_Read(hi2c, read_addr, address, I2C_MEMADD_SIZE_8BIT, &msb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  stat = HAL_I2C_Mem_Read(hi2c, read_addr, address+1, I2C_MEMADD_SIZE_8BIT, &lsb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;

  *val =  ((uint16_t) msb << 8) | lsb;
  return ret;
}

uint16_t getVersion(I2C_HandleTypeDef *hi2c)
{
	uint16_t version;
	max17043_status stat = read16(hi2c,MAX17043_VERSION,&version);
	if(stat != max17043_ok) version = 0xFFFF;
	return version;
}
