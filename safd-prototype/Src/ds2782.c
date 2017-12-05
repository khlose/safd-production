/*
 * ds2782.c
 *
 *  Created on: Nov 26, 2017
 *      Author: spinkoh
 */

#include "ds2782.h"




DS2782Status ds2782_init(I2C_HandleTypeDef *hi2c)
{
	DS2782Status return_status = DS2782_OK;
	HAL_StatusTypeDef status;

	/*
	uint8_t full40Reg_msb = 0x32;
	uint8_t full40Reg_lsb = 0;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, FULL_40_MSB, I2C_MEMADD_SIZE_8BIT, &full40Reg_msb,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, FULL_40_MSB, I2C_MEMADD_SIZE_8BIT, &full40Reg_lsb,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//charge voltage threshold used to detect a fully charged state
	//has a unit of 19.52mV (0x01 = 19.52mV 0x02 = 39.04mV etc.)
	uint8_t vchg = 0xD5;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, VCHG, I2C_MEMADD_SIZE_8BIT, &vchg,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//stores the charge current threshold used to detect a fully charged state
	//has a unit of 50 uV assuming RSNS = 20mOhm
	uint8_t imin = 0x14;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, IMIN, I2C_MEMADD_SIZE_8BIT, &imin,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//Stores the voltage threshold used to detect the active empty point
	//has a unit of 19.52mV
	uint8_t vae = 0xB3;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, VAE, I2C_MEMADD_SIZE_8BIT, &vae,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//stores the discharge current threshold used to detect the Active Empty point
	//has a unit of 200uV assuming RSNS = 20mOhm
	uint8_t iae = 0x0a;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, IAE, I2C_MEMADD_SIZE_8BIT, &iae,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//what exactly is Active empty 40?
	uint8_t ae40 = 0x06;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, ACTIVE_EMPTY_40, I2C_MEMADD_SIZE_8BIT, &ae40,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//fillBuf(full40Reg, buf);
	//setEepromBlockRegister(RSGAIN_MSB,buf,2);

	//sensinbg resistor temperature coefficient, we have none
	//buf[0]=0;
	uint8_t rstc = 0;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, RSTC, I2C_MEMADD_SIZE_8BIT, &rstc,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//stores the value of the sense resistor for use in computing the absolute capacity result
	//has a units of mhos
	uint8_t rsnsp = 0x32;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, RSNSP, I2C_MEMADD_SIZE_8BIT, &rsnsp,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	//accumulation bias register set to 00h
	uint8_t ab = 0;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, AB, I2C_MEMADD_SIZE_8BIT, &ab,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;
*/
	return return_status;
}


DS2782Status ds2782_initv2(I2C_HandleTypeDef *hi2c)
{
	DS2782Status return_status = DS2782_OK;
	HAL_StatusTypeDef status;

	uint8_t bias = 0x04;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, AB, I2C_MEMADD_SIZE_8BIT, &bias,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	uint8_t acr1 = 0x0C;
	uint8_t acr2 = 0x84;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, AC_MSB, I2C_MEMADD_SIZE_8BIT, &acr1,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, AC_LSB, I2C_MEMADD_SIZE_8BIT, &acr2,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	uint8_t cv = 0xD5;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, VCHG, I2C_MEMADD_SIZE_8BIT, &cv,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	uint8_t imin_store = 0x20;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, IMIN, I2C_MEMADD_SIZE_8BIT, &imin,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	uint8_t vae_store = 0x20;
	status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, VAE, I2C_MEMADD_SIZE_8BIT, &vae_store,1,1000);
	if(status != HAL_OK) return DS2782_ERROR;

	return return_status;
}


DS2782Status readRarcReg(I2C_HandleTypeDef *hi2c, uint8_t* rarc_val){
    uint8_t rarcRegVal;  //unit [%]
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,RARC_REG,I2C_MEMADD_SIZE_8BIT,&rarcRegVal,1,100);
    if(status != HAL_OK) return DS2782_ERROR;
    *rarc_val = rarcRegVal;

    return DS2782_OK;
}


DS2782Status readStatusReg(I2C_HandleTypeDef *hi2c, uint8_t* status_val){
    uint8_t statusRegVal;
    HAL_StatusTypeDef status;
    status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,STATUS,I2C_MEMADD_SIZE_8BIT,&statusRegVal,1,100);
    if(status != HAL_OK) return DS2782_ERROR;
    *status_val = statusRegVal;
    return DS2782_OK;

}

DS2782Status readAcrReg(I2C_HandleTypeDef *hi2c, float* acr_val){

   uint8_t rawData[2];
   uint16_t rawRes=0;
   HAL_StatusTypeDef status;
   status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,ACR_MSB_REG,I2C_MEMADD_SIZE_8BIT,rawData,2,100);
   if(status != HAL_OK) return DS2782_ERROR;

   rawRes= (rawData[0] << 8) | rawData[1];

    if(rawRes &0x8000) *acr_val = ((float)(rawRes-65536)*1.5625);
    else *acr_val = ((float)(rawRes)*1.5625);

    return DS2782_OK;
}

DS2782Status setACRRegister(I2C_HandleTypeDef *hi2c, uint16_t reg)
{
	HAL_StatusTypeDef status;

    uint8_t buf[2];
    buf[0]= ((reg>>8)&0xFF);
    buf[1]= ((reg)&0xFF);
    status = HAL_I2C_Mem_Write(hi2c,DS2782_ADDRESS, ACR_MSB_REG, I2C_MEMADD_SIZE_8BIT, buf,2,1000);

	if(status != HAL_OK) return DS2782_ERROR;
	return DS2782_OK;
}

DS2782Status readVoltage(I2C_HandleTypeDef *hi2c, float *voltage){

   uint8_t rawData[2];
   uint16_t rawVolt=0;
   HAL_StatusTypeDef status;
   status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,VOLT_MSB_REG,I2C_MEMADD_SIZE_8BIT,rawData,2,100);
   if(status != HAL_OK) return DS2782_ERROR;

   rawVolt= (((rawData[0]&~(1<<7))<<3)|((rawData[1]>>5)&0xF));

   *voltage= (float)(rawVolt*4.88);
   return DS2782_OK;
}


DS2782Status readCurrent(I2C_HandleTypeDef *hi2c, float *current){

   uint8_t rawData[2];
   uint16_t rawRes=0;

   HAL_StatusTypeDef status;
   status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,CURRENT_MSB_REG,I2C_MEMADD_SIZE_8BIT,rawData,2,100);
   if(status != HAL_OK) return DS2782_ERROR;


   rawRes= (rawData[0]<<8) |rawData[1];
    if(rawRes &0x8000){
    	*current = (float)(rawRes-65536)*0.07813;
    }
    else
    	*current = (float)(rawRes)*0.07813;
   return DS2782_OK;
}


DS2782Status readUniqueID(I2C_HandleTypeDef *hi2c, uint8_t *id){
	uint8_t uniqueid[8] = {0};
	uint8_t first_byte = 0;

	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(hi2c,DS2782_ADDRESS,UNIQUE_ID_REG,I2C_MEMADD_SIZE_8BIT,uniqueid,8,100);

	if(status != HAL_OK) return DS2782_ERROR;
	return DS2782_OK;
}
