/************************************************
Includes
************************************************/
#include "mpu6050.h"

void mpu6050_init(int *fd)
{

  char *fileName = "/dev/i2c-1";
  int  address = 0x68;

  if ((*fd = open(fileName, O_RDWR)) < 0) {
      printf("Failed to open i2c port\n");
      exit(1);
  }

  if (ioctl(*fd, I2C_SLAVE, address) < 0) {
      printf("Unable to get bus access to talk to slave\n");
      exit(1);
  }


  i2c_smbus_write_byte_data(*fd, MPU_CONFIG, 0x06);		//filter 5Hz
  int8_t power = i2c_smbus_read_byte_data(*fd, MPU_POWER1);
  i2c_smbus_write_byte_data(*fd, MPU_POWER1, ~(1 << 6) & power);
  printf("MPU6050 init done!\n");
}

int get_raw_xaccel(int *fd){
  int16_t xaccel = i2c_smbus_read_byte_data(*fd, MPU_ACCEL_XOUT) << 8 |
                   i2c_smbus_read_byte_data(*fd, MPU_ACCEL_XOUT + 1);
                   printf("accel x in function: %d\n", xaccel);
  return (int)xaccel;
}

float get_acc_angle(int *fd)
{
  float accX;
  float accY;
  float accZ;
  float angleAccY;

  int16_t xaccel = i2c_smbus_read_byte_data(*fd, MPU_ACCEL_XOUT) << 8 |
                   i2c_smbus_read_byte_data(*fd, MPU_ACCEL_XOUT + 1);
  int16_t yaccel = i2c_smbus_read_byte_data(*fd, MPU_ACCEL_YOUT) << 8 |
                   i2c_smbus_read_byte_data(*fd, MPU_ACCEL_YOUT + 1);
  int16_t zaccel = i2c_smbus_read_byte_data(*fd, MPU_ACCEL_ZOUT ) << 8 |
                   i2c_smbus_read_byte_data(*fd, MPU_ACCEL_ZOUT + 1);

  accX = ((float)xaccel) / 16384.0;
  accY = ((float)yaccel) / 16384.0;
  accZ = ((float)zaccel) / 16384.0;

  angleAccY = atan2(accX, accZ + abs(accY)) * 360 / -2.0 / 3.14;
  return angleAccY;
}

/*
float get_gyro_x(int *fd)
{
int16_t xgyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_XOUT1) << 8 |
                i2c_smbus_read_byte_data(fd, MPU_GYRO_XOUT2);
  	gyroX = ((float)rawGyroX) / 65.5;
    return gyroX;
}
*/
