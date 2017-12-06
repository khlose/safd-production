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
	vCell = read16(hi2c,MAX17043_VCELL);
	// vCell is a 12-bit register where each bit represents 1.25mV
	vCell = (vCell) >> 4;

	return ((float) vCell / 800.0);
}

float getSOC(I2C_HandleTypeDef *hi2c)
{
  uint16_t soc;
  float percent;
  soc = read16(hi2c,MAX17043_SOC);
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
  HAL_I2C_StateTypeDef stat = HAL_I2C_MEM_Write(hi2c, MAX17043_ADDRESS, address, I2C_MEMADD_SIZE_8BIT, &msb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  stat = HAL_I2C_MEM_Write(hi2c, MAX17043_ADDRESS, address+1, I2C_MEMADD_SIZE_8BIT, &lsb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  return (ret);
}

uint16_t read16(I2C_HandleTypeDef *hi2c, uint8_t address)
{
  uint8_t msb, lsb;
  int16_t timeout = 1000;
  max17043_status ret = max17043_ok;

  HAL_I2C_StateTypeDef stat = HAL_I2C_MEM_Write(hi2c, MAX17043_ADDRESS, address, I2C_MEMADD_SIZE_8BIT, &msb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;
  stat = HAL_I2C_MEM_Write(hi2c, MAX17043_ADDRESS, address+1, I2C_MEMADD_SIZE_8BIT, &lsb, 1, 100);
  if(stat != HAL_OK) ret = max17043_error;

  return ((uint16_t) msb << 8) | lsb;
}

uint16_t getVersion(I2C_HandleTypeDef *hi2c)
{
	return read16(hi2c,MAX17043_VERSION);
}
