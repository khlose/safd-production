/*
 * lsm6ds3.c
 *
 *  Created on: Oct 2, 2017
 *      Author: Schwin Pinkoh
 */

#include "lsm6ds3.h"


LSM6DS3_StatusTypedef init_accelerometer(I2C_HandleTypeDef *hi2c, uint8_t sensor_no, LSM6DS3_SensitivityTypedef sensitivity,LSM6DS3_DataRateTypedef data_rate)
{
	HAL_StatusTypeDef wStat;

	/*Acc X, Y, Z axes enabled*/
	uint8_t wData = ACC_XYZ_EN;
	wStat = HAL_I2C_Mem_Write(hi2c,sensor_no, CTRL9_XL, I2C_MEMADD_SIZE_8BIT, &wData,1,1000);

	if(wStat != HAL_OK)
		return LSM6DS3_ERROR;

	/*Acc performance select*/
	wData = sensitivity | data_rate;

	/*Selecting Anti Aliasing filter based on data rate*/
	switch(data_rate)
	{
		case rate12hz:
		case rate26hz:
		case rate52hz:
		case rate104hz:
			wData |= 0x03;
		break;

		case rate208hz:
			wData |= 0x02;
		break;

		case rate416hz:
			wData |= 0x01;
		break;

		case rate833hz:
		case rate1_66khz:
			wData |= 0x00;
		break;

		/*Filter not used for 3.33-6.66kHzs*/
		default:
			wData |= 0x00;
	}
	wStat = HAL_I2C_Mem_Write(hi2c,sensor_no,CTRL1_XL,I2C_MEMADD_SIZE_8BIT,&wData,1,1000);
	if(wStat != HAL_OK)
			return LSM6DS3_ERROR;
	/* Acc Data Ready interrupt on INT1*/
	wData = 0x03;
	wStat = HAL_I2C_Mem_Write(hi2c,sensor_no,INT1_CTRL,I2C_MEMADD_SIZE_8BIT,&wData,1,1000); // Do we need this???
	if(wStat != HAL_OK)
			return LSM6DS3_ERROR;

	/*Store the selected sensitivity for future use*/
	selected_sensitivity = sensitivity;
	return LSM6DS3_OK;
}

LSM6DS3_StatusTypedef init_gyroscope(I2C_HandleTypeDef *HI2C, uint8_t sensor_no, LSM6DS3_DpsTypedef dps, LSM6DS3_DataRateTypedef data_rate){
	HAL_StatusTypeDef GStatus;
	uint8_t GData = ACC_GYRO_EN;

	GStatus = HAL_I2C_Mem_Write(HI2C , sensor_no, ACC_GYRO_CTRL10_C, I2C_MEMADD_SIZE_8BIT, &GData, 1, 1000);
	if(GStatus != HAL_OK){
		return LSM6DS3_ERROR;
	}

	//data_rate = ODR[3:0]
	GData = dps | data_rate;

	GStatus = HAL_I2C_Mem_Write(HI2C,sensor_no,ACC_GYRO_CTRL2_G,I2C_MEMADD_SIZE_8BIT,&GData,1,1000);
		if(GStatus != HAL_OK)
				return LSM6DS3_ERROR;

	/* Gyro Data Ready interrupt on INT1*/
	GData = 0x03;
	GStatus = HAL_I2C_Mem_Write(HI2C,sensor_no,INT1_CTRL,I2C_MEMADD_SIZE_8BIT,&GData,1,1000); // Do we need this???
	if(GStatus != HAL_OK)
		return LSM6DS3_ERROR;

	/*Store the selected dps for future use*/
	selected_dps = dps;
	return LSM6DS3_OK;
}

LSM6DS3_StatusTypedef acc_read_xyz(I2C_HandleTypeDef* hi2c1, int sensor_no,triplet* acc_data)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t r_buffer[1] = {0};
	uint8_t acc_buffer[6] = {0};
	uint16_t x_raw,y_raw,z_raw;
	int16_t temp[3] = {0};
	int scaling = 1;

	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,STATUS_REG,I2C_MEMADD_SIZE_8BIT,r_buffer,1,100);

	/*Busy HAL bus, go do something else*/
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*XLDA bit = 0, no new data*/
	if((r_buffer[0] & XLDA_BIT) == 0x00) return LSM6DS3_OUT_OF_DATA;

	/*Read X_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_XL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[0],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read X_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_XH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[1],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Y_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_YL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[2],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Y_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_YH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[3],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;
	/*Read Z_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_ZL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[4],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Z_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_ZH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[5],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	x_raw = acc_buffer[1] << 8 | acc_buffer[0];
	y_raw = acc_buffer[3] << 8 | acc_buffer[2];
	z_raw = acc_buffer[5] << 8 | acc_buffer[4];

	temp[0] = x_raw;
	temp[1] = y_raw;
	temp[2] = z_raw;

	switch(selected_sensitivity)
	{
		case sensitivity_2g: scaling = scaling_2g;
		break;

		case sensitivity_4g: scaling = scaling_4g;
		break;

		case sensitivity_8g: scaling = scaling_8g;
		break;

		case sensitivity_16g: scaling = scaling_16g;
		break;
	}

	acc_data->x = (float)(temp[0]) / scaling;
	acc_data->y = (float)(temp[1]) / scaling;
	acc_data->z = (float)(temp[2]) / scaling;

	return LSM6DS3_OK;
}


LSM6DS3_StatusTypedef gyro_read_xyz(I2C_HandleTypeDef* hi2c1,int sensor_no,triplet* gyro_data)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t r_buffer[1] = {0};
	uint8_t acc_buffer[6] = {0};
	uint16_t x_raw,y_raw,z_raw;
	int16_t temp[3] = {0};
	int scaling = 1;

	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,STATUS_REG,I2C_MEMADD_SIZE_8BIT,r_buffer,1,100);

	/*Busy HAL bus, go do something else*/
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*XLDA bit = 0, no new data*/
	if((r_buffer[0] & GDA_BIT) == 0x00) return LSM6DS3_OUT_OF_DATA;

	/*Read X_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_XL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[0],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read X_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_XH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[1],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Y_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_YL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[2],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Y_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_YH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[3],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;
	/*Read Z_Lower*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_ZL,I2C_MEMADD_SIZE_8BIT,&acc_buffer[4],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	/*Read Z_Higher*/
	status = HAL_I2C_Mem_Read(hi2c1,sensor_no,ACC_GYRO_ZH,I2C_MEMADD_SIZE_8BIT,&acc_buffer[5],1,100);
	if(status != HAL_OK) return LSM6DS3_BUSY;

	x_raw = acc_buffer[1] << 8 | acc_buffer[0];
	y_raw = acc_buffer[3] << 8 | acc_buffer[2];
	z_raw = acc_buffer[5] << 8 | acc_buffer[4];

	temp[0] = x_raw;
	temp[1] = y_raw;
	temp[2] = z_raw;

	/*Have to divide this by 1000 because our scaling factor must be a float but*/
	/*enum elements cant be float*/
	switch(selected_dps)
	{
		case dps_250: scaling = scaling_250/1000;
		break;

		case dps_500: scaling = scaling_500/1000;
		break;

		case dps_1000: scaling = scaling_1000/1000;
		break;

		case dps_2000: scaling = scaling_2000/1000;
		break;
	}

	/*Unit now in mdps, has to convert to dps*/
	gyro_data->x = (float)(temp[0]) * scaling / 1000;
	gyro_data->y = (float)(temp[1]) * scaling / 1000;
	gyro_data->z = (float)(temp[2]) * scaling / 1000;

	/*Convert to rad/s*/
	gyro_data->x = gyro_data->x * (22/7) / 180;
	gyro_data->y = gyro_data->y * (22/7) / 180;
	gyro_data->z = gyro_data->z * (22/7) / 180;

	return LSM6DS3_OK;
}
