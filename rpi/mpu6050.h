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
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <math.h>

/************************************************
Defines
************************************************/
#define MPU_ACCEL_XOUT	0x3B
#define MPU_ACCEL_YOUT	0x3D
#define MPU_ACCEL_ZOUT	0x3F

#define MPU_GYRO_XOUT	0x43
#define MPU_GYRO_YOUT	0x45
#define MPU_GYRO_ZOUT	0x47

#define MPU_TEMP	0x41
#define MPU_POWER1	0x6B
#define MPU_CONFIG	0x1A

/************************************************
Global var
************************************************/

/************************************************
Function prototypes
************************************************/
float mpu6050_init(int *fd);
int get_raw_xaccel(int *fd);
float get_gyro_y(int *fd);
float get_angle(int *fd);
#endif
