/*
 * ds2782.h
 *
 *  Created on: Nov 26, 2017
 *      Author: spinkoh
 */

#ifndef DS2782_H_
#define DS2782_H_
#include "stm32l4xx_hal.h"

#define DS2782_ADDRESS 0x68
//#define DS2782_ADDRESS ((uint8_t)0x34<<1)
//#define DS2782_ADDRESS ((uint8_t)0x34>>1)


typedef enum
{
	STATUS=0x01,     /*STATUS - Status Register*/
	RAAC_MSB_REG,        /*RAAC - Remaining Active Absolute Capacity MSB*/
	RAAC_LSB_REG,
	RSAC_MSB_REG,        /*RSAC - Remaining Standby Absolute Capacity MSB*/
	RSAC_LSB_REG,
	RARC_REG,            /*RARC - Remaining Active Relative Capacity*/
	RSRC_REG,            /*RSRC - Remaining Standby Relative Capacity*/
	IAVG_MSB_REG,        /*IAVG - Average Current Register MSB*/
	IAVG_LSB_REG,
	TEMP_MSB_REG,        /*TEMP - Temperature Register MSB*/
	TEMP_LSB_REG,
	VOLT_MSB_REG,        /*VOLT - Voltage Register MSB*/
	VOLT_LSB_REG,
	CURRENT_MSB_REG,     /*CURRENT - Current Register MSB*/
	CURRENT_LSB_REG,
	ACR_MSB_REG,         /*ACR - Accumulated Current Register MSB*/
	ACR_LSB_REG,
	ACRL_MSB_REG,        /*Low Accumulated Current Register MSB*/
	ACRL_LSB_REG,
	AS_REG,              /*AS - Age Scalar*/
	SFR_REG,             /*SFR - Special Feature Register*/
	FULL_MSB_REG,        /*FULL - Full Capacity MSB*/
	FULL_LSB_REG,
	AE_MSB_REG,          /*AE - Active Empty MSB*/
	AE_LSB_REG,
	SE_MSB_REG,          /*SE - Standby Empty MSB*/
	SE_LSB_REG,
	EEPROM_REG= 0x1F,         /*EEPROM - EEPROM Register */
	USR_EEPROM_REG= 0x20,     /*User EEPROM, Lockable, Block 0 [20 to 2F]*/
	ADD_USR_EEPROM_REG=0x30,  /*Additional User EEPROM, Lockable, Block 0 [30 to 37]*/
	PARAM_EEPROM_REG=0x60,    /*Parameter EEPROM, Lockable, Block 1 [60 to 7F]*/
	UNIQUE_ID_REG =0xF0,      /*Unique ID [F0 to F7]*/
	FUNC_COMMAND_REG= 0xFE    /*Function Command Register */
}RegisterAddress;

typedef enum {

   CONTROL = 0x60,   //Control Register
   AB =0x61,         //Accumulation Bias
   AC_MSB = 0x62,    //Aging Capacity MSB
   AC_LSB = 0x63,    //Aging Capacity LSB
   VCHG = 0x64,      //Charge Voltage
   IMIN =0x65,       //Minimum Charge Current
   VAE = 0x66,       //Active Empty Voltage
   IAE = 0x67,       //Active Empty Current
   ACTIVE_EMPTY_40 = 0x68,
   RSNSP = 0x69,     //Sense Resistor Prime
   FULL_40_MSB = 0x6A,
   FULL_40_LSB = 0x6B,
   FULL_3040_SLOPE = 0x6C,
   FULL_2030_SLOPE = 0x6D,
   FULL_1020_SLOPE = 0x6E,
   FULL_0010_SLOPE  = 0x6F,
   AE_3040_SLOPE  = 0x70,
   AE_2030_SLOPE = 0x71,
   AE_1020_SLOPE = 0x72,
   AE_0010_SLOPE = 0x73,
   SE_3040_SLOPE = 0x74,
   SE_2030_SLOPE = 0x75,
   SE_1020_SLOPE = 0x76,
   SE_0010_SLOPE = 0x77,
   RSGAIN_MSB = 0x78,          //Sense Resistor Gain MSB
   RSGAIN_LSB = 0x79,          //Sense Resistor Gain LSB
   RSTC = 0x7A,                //Sense Resistor Temp. Coeff.
   FRSGAIN_MSB = 0x7B,         //Factory Gain MSB
   FRSGAIN_LSB = 0x7C,         //Factory Gain LSB
   I2C_SLAVE_ADDR= 0x7E //2-Wire Slave Address
}ParamEepromReg;

typedef enum {
	DS2782_OK=0x00,
	DS2782_ERROR
}DS2782Status;


DS2782Status ds2782_init(I2C_HandleTypeDef *hi2c);
DS2782Status ds2782_initv2(I2C_HandleTypeDef *hi2c);
DS2782Status readRarcReg(I2C_HandleTypeDef *hi2c, uint8_t* rarc_val);
DS2782Status readStatusReg(I2C_HandleTypeDef *hi2c, uint8_t* status_val);
DS2782Status readAcrReg(I2C_HandleTypeDef *hi2c, float* acr_val);
DS2782Status setACRRegister(I2C_HandleTypeDef *hi2c, uint16_t reg);
DS2782Status readVoltage(I2C_HandleTypeDef *hi2c, float *voltage);
DS2782Status readCurrent(I2C_HandleTypeDef *hi2c, float *current);
DS2782Status readUniqueID(I2C_HandleTypeDef *hi2c, uint8_t *id);

#endif /* DS2782_H_ */
