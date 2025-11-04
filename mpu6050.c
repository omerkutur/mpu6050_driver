/*
 * mpu6050.c
 *
 *  Created on: Nov 3, 2025
 *      Author: omer
 */

#include "mpu6050.h"
#include "stm32f4xx.h"
#include "math.h"



///////////////////////////////////////////////
////////////// EXTERN /////////////////////////
extern I2C_HandleTypeDef hi2c1;
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////// RAW ////////////////////////////
int16_t rawAccel[3] = {0};
int16_t rawGyro[3] = {0};
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////// DIVIDED ////////////////////////
float calAccel[3] = {0.0f};
float calGyro[3] = {0.0f};
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////// PARAMS /////////////////////////
float accelSens = 2048.0f; // for example in case of error with accel init
float gyroSens = 65.5f; // for example in case of error with gyro init
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////// ANGLE VARS//////////////////////
float anglePitch = 0.0f;
float angleRoll  = 0.0f;
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////// TEMPERATUR /////////////////////
int16_t rawTemp = 0;
float   calTemp = 0.0f;
///////////////////////////////////////////////


void MPU6050_IsReady( void ){
	if(HAL_OK == HAL_I2C_IsDeviceReady(&hi2c1, MPU6050_ADDRESS, 100, HAL_MAX_DELAY)){
		HAL_Delay(0);
	}
}

void MPU6050_WhoAmI( void ){
	uint8_t ret = 0x00;
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, MPU6050_WHOAMI, 1, &ret, 1, HAL_MAX_DELAY);
}

void MPU6050_GyroInit( MPU6050_GyroFS_SEL fs_sel, MPU6050_Gyro_Sens sens){
	gyroSens = ( MPU6050_GYRO_Default_sens / sens);
	uint8_t val = fs_sel << 3;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_GYRO_CONFIG, 1, &val, 1, HAL_MAX_DELAY);
}

void MPU6050_AccelInit( MPU6050_AccelFS_SEL fs_sel, MPU6050_Accel_Sens sens ){
	accelSens = sens;
	uint8_t val = fs_sel << 3;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_ACCEL_CONFIG, 1, &val, 1, HAL_MAX_DELAY);
}

void MPU6050_PowerInit( MPU6050_PowerRef val){
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, 1, &val, 1, HAL_MAX_DELAY);
}

void MPU6050_ReadAccel( void ){}

void MPU6050_ReadGyro( void ){}

void MPU6050_ReadAll( void ){
	uint8_t readAll[14] = {0};

	////////////////////////////////// GETTING FIRST VALUES ///////////////////////////////////////
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, 1, readAll, 14, HAL_MAX_DELAY);

	////////////////////////////////// SHIFTING AND DIVIDING //////////////////////////////////////
	//////// ACCEL /////////////
	for(uint8_t i=0; i<3; i++){
		rawAccel[i] = (int16_t)( readAll[i*2] << 8  | readAll[(i*2)+1] );
		calAccel[i] = (float) rawAccel[i] / accelSens;
	}

	//////// TEMP /////////////
	rawTemp = (int16_t)( readAll[6] << 8 | readAll[7] );
	calTemp = (float)((int16_t)rawTemp / 340.0f + 36.53f);

	//////// GYRO /////////////
	for(uint8_t i=4; i<7; i++){
		rawGyro[i-4] = (int16_t)( readAll[i*2] << 8  | readAll[(i*2)+1] );
		calGyro[i-4] = (float) rawGyro[i-4] / gyroSens;
	}
}

void MPU6050_GetPitchRoll( void ){
	float accel_pitch = atan2f(calAccel[1], sqrtf(calAccel[0]*calAccel[0] + calAccel[2]*calAccel[2])) * 180.0f / M_PI;
	float accel_roll = atan2f(-calAccel[0], sqrtf(calAccel[1]*calAccel[1] + calAccel[2]*calAccel[2])) * 180.0f / M_PI;

	anglePitch += calGyro[1] * DT;
	angleRoll  += calGyro[0] * DT;

	///////////////////// COMPL FILTER
	anglePitch = ALPHA * anglePitch + ( 1.0f - ALPHA ) * accel_pitch;
	angleRoll  = ALPHA * angleRoll  + ( 1.0f - ALPHA ) * accel_roll;
}















