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
#define MPU_ACCEL_XOUT1 0x3b
#define MPU_ACCEL_XOUT2 0x3c
#define MPU_ACCEL_YOUT1 0x3d
#define MPU_ACCEL_YOUT2 0x3e
#define MPU_ACCEL_ZOUT1 0x3f
#define MPU_ACCEL_ZOUT2 0x40

#define MPU_GYRO_XOUT1 0x43
#define MPU_GYRO_XOUT2 0x44
#define MPU_GYRO_YOUT1 0x45
#define MPU_GYRO_YOUT2 0x46
#define MPU_GYRO_ZOUT1 0x47
#define MPU_GYRO_ZOUT2 0x48

#define MPU_TEMP1 0x41
#define MPU_TEMP2 0x42

#define MPU_POWER1 0x6b
#define MPU_POWER2 0x6c

/************************************************
Global var
************************************************/



/************************************************
Function prototypes
************************************************/
void mpu6050_init(int *fd);
int get_raw_xaccel(int *fd);
float get_acc_angle(int *fd);

#endif
