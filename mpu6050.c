/************************************************
Includes
************************************************/
#include "mpu6050.h"

//pokud chodi warningy ze nezna i2c_smbus_read_byte
//sudo apt-get install libi2c-dev

void mpu6050_init()
{
  int fd;
  char *fileName = "/dev/i2c-1";

  if ((fd = open(fileName, O_RDWR)) < 0) {
    printf("Failed to open i2c port\n");
    exit(1);
  }

  if (ioctl(fd, I2C_SLAVE, SLAVE_ADRESS) < 0) {
    printf("Unable to get bus access to talk to slave\n");
    exit(1);
  }

  //================= setup + power up =============================
  i2c_smbus_write_byte_data(fd, MPU_GYRO_CONFIG, 0x00);	//gyro range 250dps
  i2c_smbus_write_byte_data(fd, MPU_ACCEL_CONFIG, 0x00);	//acce range 2g
  i2c_smbus_write_byte_data(fd, MPU_CONFIG, 0x06);		//filter 5Hz
  int8_t power = i2c_smbus_read_byte_data(fd, MPU_POWER1);
  i2c_smbus_write_byte_data(fd, MPU_POWER1, ~(1 << 6) & power);
}

float get_angle_x(){
  int16_t xaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH + 1);
  int16_t yaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);
  int16_t zaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);

  xaccel = (xaccel / 16384.0);
  yaccel = (yaccel / 16384.0);
  zaccel = (zaccel / 16384.0);
  //calculate angle
  return (180 / 3.141592) * atan (xaccel / sqrt(pow(yaccel, 2) + pow(zaccel, 2)));
}
float get_angle_y(){
  int16_t xaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH + 1);
  int16_t yaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);
  int16_t zaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);

  xaccel = (xaccel / 16384.0);
  yaccel = (yaccel / 16384.0);
  zaccel = (zaccel / 16384.0);
  //calculate angle
  return (180 / 3.141592) * atan (yaccel / sqrt(pow(xaccel, 2) + pow(zaccel, 2)));

}

float get_angle_z(){
  int16_t xaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_XHIGH + 1);
  int16_t yaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);
  int16_t zaccel = i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_ACCEL_YHIGH + 1);

  xaccel = (xaccel / 16384.0);
  yaccel = (yaccel / 16384.0);
  zaccel = (zaccel / 16384.0);
  //calculate angle
  return (180 / 3.141592) * atan (sqrt(pow(yaccel, 2) + pow(xaccel, 2)) / zaccel);
}

int16_t get_gyro_x(){
  int16_t xgyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_XHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_GYRO_XHIGH + 1);
  return (xgyro / 131.0);
}

int16_t get_gyro_y(){
  int16_t ygyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_YHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_GYRO_YHIGH + 1);
  return (ygyro / 131.0);
}

int16_t get_gyro_z(){
  int16_t zgyro = i2c_smbus_read_byte_data(fd, MPU_GYRO_ZHIGH) << 8 |
  i2c_smbus_read_byte_data(fd, MPU_GYRO_ZHIGH + 1);
  return (zgyro / 131.0);
}
