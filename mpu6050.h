/*
 * mpu6050.h
 *
 *  Created on: Nov 2, 2025
 *      Author: omer
 */

#ifndef MPU6050_DRIVER_INC_MPU6050_H_
#define MPU6050_DRIVER_INC_MPU6050_H_

#include "stdint.h"

#define MPU6050_WHOAMI					( 0x75 )
#define MPU6050_ADDRESS					( 0x68 << 1 )

#define MPU6050_PWR_MGMT_1 				( 0x6B )
#define MPU6050_SMPRT_DIV				( 0x19 )

#define MPU6050_CONFIG					( 0x1A )
#define MPU6050_GYRO_CONFIG				( 0x1B )
#define MPU6050_ACCEL_CONFIG			( 0x1C )

#define MPU6050_ACCEL_XOUT_H			( 0x3B )
#define MPU6050_ACCEL_XOUT_L			( 0x3C )
#define MPU6050_ACCEL_YOUT_H			( 0x3D )
#define MPU6050_ACCEL_YOUT_L			( 0x3E )
#define MPU6050_ACCEL_ZOUT_H			( 0x3F )
#define MPU6050_ACCEL_ZOUT_L			( 0x40 )

#define MPU6050_GYRO_XOUT_H				( 0x43 )
#define MPU6050_GYRO_XOUT_L				( 0x44 )
#define MPU6050_GYRO_YOUT_H				( 0x45 )
#define MPU6050_GYRO_YOUT_L				( 0x46 )
#define MPU6050_GYRO_ZOUT_H				( 0x47 )
#define MPU6050_GYRO_ZOUT_L				( 0x48 )
#define MPU6050_GYRO_Default_sens		( 131.0 )

#define MPU6050_GYRO_250_SENS			( 131.0 )
#define MPU6050_GYRO_500_SENS			( 65.5  )
#define MPU6050_GYRO_1000_SENS			( 32.8  )
#define MPU6050_GYRO_2000_SENS			( 16.4  )
#define MPU6050_GYRO_Default_sens		( 131.0 )

#define GYRO_TEST_CAL_VALUE				( 500 )

#define MPU6050_TEMP_OUT_H				( 0x41 )
#define MPU6050_TEMP_OUT_L				( 0x42 )

#define ALPHA 							( 0.98f )
#define DT 								( 0.01f )

typedef enum {
	INTERNAL_OSC = 0,
	PLL_X_GYRO_REF,
	PLL_Y_GYRO_REF,
	PLL_Z_GYRO_REF
}MPU6050_PowerRef;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////// GYRO ////////////////////////////////////
typedef enum {
	FS_SEL_250 = 0,
	FS_SEL_500,
	FS_SEL_1000,
	FS_SEL_2000,
}MPU6050_GyroFS_SEL;

typedef enum {
	GYRO_250_SENS = 1,
	GYRO_500_SENS = 2,
	GYRO_1000_SENS = 4,
	GYRO_2000_SENS = 8,
}MPU6050_Gyro_Sens;

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////// ACCEL //////////////////////////////////////
typedef enum {
	AFS_SEL_2G = 0,
	AFS_SEL_4G,
	AFS_SEL_8G,
	AFS_SEL_16G,
}MPU6050_AccelFS_SEL;

typedef enum {
	ACCEL_2G_SENS  = 16384,
	ACCEL_4G_SENS  = 8192,
	ACCEL_8G_SENS  = 4096,
	ACCEL_16G_SENS = 2048,
}MPU6050_Accel_Sens;

//////////////////////////////////////////////////////////////////////

void MPU6050_IsReady( void );
void MPU6050_WhoAmI( void );

void MPU6050_GyroInit( MPU6050_GyroFS_SEL fs_sel, MPU6050_Gyro_Sens sens);
void MPU6050_AccelInit( MPU6050_AccelFS_SEL fs_sel, MPU6050_Accel_Sens sens);
void MPU6050_PowerInit( MPU6050_PowerRef val);

void MPU6050_ReadAccel( void );
void MPU6050_ReadGyro ( void );
void MPU6050_ReadAll( void );

void MPU6050_GetPitchRoll( void );






#endif /* MPU6050_DRIVER_INC_MPU6050_H_ */
