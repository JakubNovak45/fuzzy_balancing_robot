/************************************************
Includes
************************************************/
#include <stdio.h>
#include <unistd.h>
#include "fuzzy.h"
#include "mpu6050.h"
#include "serial.h"

int fd;
float angleY, gyroY, fuzzyOutput, gyroYOffset;

int main()
{
 serial_init(B115200, "/dev/ttyUSB0");
 gyroYOffset = mpu6050_init(&fd);

 while(1)
 {
  //test_spin();
  angleY = get_angle(&fd);
  gyroY = get_gyro_y(&fd) - gyroYOffset;
  //fuzzy
  if(angleY < 45 && angleY > -45)
  {
    g_fisInput[0] = angleY;
    g_fisInput[1] = gyroY;
    fis_evaluate();
    fuzzyOutput = g_fisOutput[0];

    serial_send(fuzzyOutput);
    printf("angleY: %f  gyroY: %f serial: %f\n", angleY, gyroY, fuzzyOutput);
  }
  else
  {
   serial_send(0);
   printf("angleY: %f  gyroY: %f serial: %f\n", angleY, gyroY, 0);
  }
  usleep(100000);
 }
 return 0;
}

