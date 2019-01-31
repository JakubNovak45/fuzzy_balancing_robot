#ifndef MPU6050_H
#define MPU6050_H
/*
Conections:
MPU6050     Raspberry Pi
Vcc ----->  5V (PIN 2)
SDA ----->  GPIO2 (PIN 3)
SCL ----->  GPIO3 (PIN 5)
GND ----->  GND (PIN 6)
*/

/************************************************
Includes
************************************************/
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************************
Defines
************************************************/
#define MPU_ACCEL_XHIGH	 	0x3B
#define MPU_ACCEL_YHIGH	 	0x3D
#define MPU_ACCEL_ZHIGH	 	0x3F
#define MPU_GYRO_XHIGH 		0x43
#define MPU_GYRO_YHIGH 		0x45
#define MPU_GYRO_ZHIGH 		0x47
#define MPU_POWER1 			0x6b
#define MPU_GYRO_CONFIG		0x1B
#define MPU_ACCEL_CONFIG 	0x1C
#define MPU_CONFIG			0x1A

#define SLAVE_ADRESS 0x68
/************************************************
Global var
************************************************/

int fd;

/************************************************
Function prototypes
************************************************/
void mpu6050_init();
float get_angle_x();
float get_angle_y();
float get_angle_z();
int16_t get_gyro_x();
int16_t get_gyro_y();
int16_t get_gyro_z();

#endif
