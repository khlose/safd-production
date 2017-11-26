/*
 * lsm6ds3.h
 *
 *  Created on: Oct 2, 2017
 *      Author: Schwin Pinkoh
 */
#include "stm32l4xx.h"
#include "buffer.h"

#ifndef LSM6DS3_H_
#define LSM6DS3_H_

/*register addresses*/
#define CTRL9_XL                 ((uint8_t)0x18)            /*!< CTRL9_XL register address */
#define CTRL1_XL                 ((uint8_t)0x10)            /*!< CTRL1_XL register address */
#define INT1_CTRL                ((uint8_t)0x0D)            /*!< INT1_CTRL register address */
#define WHO_AM_I				 ((uint8_t)0x0F)			/*!< Who am I register*/
#define STATUS_REG				 ((uint8_t)0x1E)			/*!< Status register*/

#define ACC_XL					 ((uint8_t)0x28)			/*!< Register storing the lower 8bits of x*/
#define ACC_XH					 ((uint8_t)0x29)			/*!< Register storing the higher 8bits of x*/
#define ACC_YL					 ((uint8_t)0x2A)			/*!< Register storing the lower 8bits of y*/
#define ACC_YH					 ((uint8_t)0x2B)			/*!< Register storing the higher 8bits of y*/
#define ACC_ZL					 ((uint8_t)0x2C)			/*!< Register storing the lower 8bits of z*/
#define ACC_ZH					 ((uint8_t)0x2D)			/*!< Register storing the higher 8bits of z*/

#define ACC_GYRO_CTRL2_G        ((uint8_t)0x11)
#define ACC_GYRO_CTRL10_C        ((uint8_t)0x18)
#define ACC_GYRO_INT1_CTRL       ((uint8_t)0x0D)

#define ACC_GYRO_XL              ((uint8_t)0x22)
#define ACC_GYRO_XH              ((uint8_t)0x23)
#define ACC_GYRO_YL              ((uint8_t)0x24)
#define ACC_GYRO_YH              ((uint8_t)0x25)
#define ACC_GYRO_ZL              ((uint8_t)0x26)
#define ACC_GYRO_ZH              ((uint8_t)0x27)

/*Data Transmitted*/
#define ACC_XYZ_EN				 ((uint8_t)0x38)			/*!< Enable xyz acc data - bit3,4,5*/
#define ACC_GYRO_EN				 ((uint8_t)0x39)
#define INTERRUPT_INT1			 ((uint8_t)0x01)			/*!< Acc Data ready interrupt on INT1*/

/*Slave sensor addresses*/
#define SENSOR_1				 ((uint8_t)0x6B<<1)			/*!< Sensor No.1 (SDO/SA0 - Supply Voltage)*/
#define SENSOR_2				 ((uint8_t)0x6A<<1)			/*!< Sensor No.2 (SDO/SA0 - GND)*/

/*Masking pattern*/
#define XLDA_BIT				 ((uint8_t)0x01)			/*!< Mask checking availability of new data set*/
#define GDA_BIT					 ((uint8_t)0x02)			/*!< Mask checking gyro status register*/

#define SAMPLIING_PERIOD 0.0024f

typedef enum
{
	sensitivity_2g = 0x00,
	sensitivity_4g = 0x08,
	sensitivity_8g = 0x0C,
	sensitivity_16g = 0x04
}LSM6DS3_SensitivityTypedef;

typedef enum
{
	dps_250 = 0x00,
	dps_500 = 0x04,
	dps_1000 = 0x08,
	dps_2000 = 0x0C
}LSM6DS3_DpsTypedef;

typedef enum
{
	scaling_2g = 16384,
	scaling_4g = 8192,
	scaling_8g =  4096,
	scaling_16g = 2048
}LSM6DS3_ScalingTypedef;

typedef enum
{
	scaling_250 = 8750,
	scaling_500 = 17500,
	scaling_1000 = 35000,
	scaling_2000 = 70000
}LSM6DS3_DpsScalingTypedef;

typedef enum
{
	power_down = 0x00,
	rate12hz = 0x10,
	rate26hz = 0x20,
	rate52hz = 0x30,
	rate104hz = 0x40,
	rate208hz = 0x50,
	rate416hz = 0x60,
	rate833hz = 0x70, // 5000/6 hz
	rate1_66khz = 0x80, // 10/6 khz once every 0.6ms
	rate3_33khz = 0x90,
	rate6_66khz = 0xA0
}LSM6DS3_DataRateTypedef;

typedef enum
{
	LSM6DS3_OK = 0x00,
	LSM6DS3_ERROR = 0x01,
	LSM6DS3_BUSY = 0x02,
	LSM6DS3_OUT_OF_DATA = 0x03
}LSM6DS3_StatusTypedef;

/*
typedef enum {

}
 */
static LSM6DS3_SensitivityTypedef selected_sensitivity;
static LSM6DS3_DpsTypedef selected_dps;
LSM6DS3_StatusTypedef init_accelerometer(I2C_HandleTypeDef *hi2c, uint8_t sensor_no,LSM6DS3_SensitivityTypedef sensitivity, LSM6DS3_DataRateTypedef data_rate);
LSM6DS3_StatusTypedef acc_read_xyz(I2C_HandleTypeDef* hi2c1,int sensor_no,triplet* acc_data);
LSM6DS3_StatusTypedef init_gyroscope(I2C_HandleTypeDef *HI2C, uint8_t sensor_no, LSM6DS3_DpsTypedef dps, LSM6DS3_DataRateTypedef data_rate);
LSM6DS3_StatusTypedef gyro_read_xyz(I2C_HandleTypeDef* hi2c1,int sensor_no,triplet* gyro_data);
#endif /* LSM6DS3_H_ */
