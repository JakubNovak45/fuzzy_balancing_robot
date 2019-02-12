/************************************************
Includes
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "fuzzy.h"
#include "mpu6050.h"
#include "serial.h"
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
//#include "rs232.h"

#define BUF_SIZE 128
/************************************************
Global var
************************************************/
int fd, serialPort;
float angleY;
int acc;
float e,de = 0;
float t1,t2 = 0;

/************************************************
Function prototypes
************************************************/
//void timer_init(int period);

/************************************************
Main loop
************************************************/
int main()
{

  //mpu6050_init(&fd);
  serial_init(B115200, "/dev/ttyACM0");
  //serial_init(115200, "/dev/ttyUSB0");
  //timer_init(10000);	//10ms period

  struct timespec start, finish;
  uint32_t startUsec, finishUsec;
  uint32_t lastStart = 0;
  int w,e = 0;
  static const int intervalMs = 10;
  while(1)
  {
      clock_gettime(CLOCK_MONOTONIC, &start);
      startUsec = start.tv_nsec / 1000;

      //kontrolni hlaska
      if(lastStart != 0){
        //printf("cyklus opakovan za: %lu mikrosekund\n", (startUsec - lastStart));
      }
      lastStart = startUsec;

      //
        //tvuj kod
        volatile int v = 0;
        for (int i = 0; i < 10000; i++) {
         v++;
        }

      //
      if(w == 100){
           serial_send(e);
           printf("%d\n", e);
         w =0;

         if(e == 30){
           e = 0;
         }
         e++;
      }
      w++;
      clock_gettime(CLOCK_MONOTONIC , &finish);
      finishUsec = finish.tv_nsec / 1000;

      usleep(intervalMs * 1000 - (finishUsec - startUsec) - 100);

      do{
          clock_gettime(CLOCK_MONOTONIC , &finish) != 0;
          finishUsec = finish.tv_nsec / 1000;
      }while((finishUsec - startUsec) < intervalMs * 1000);
  }
  return 0;
}

/*
void timer_handler (int signum)
{
  t2 = t1;
  t1 = e;
  de = (t1 - t2)/0.01;
  e = get_acc_angle(&fd);
    g_fisInput[0] = e;
     // Read Input: de
     g_fisInput[1] = de;

     g_fisOutput[0] = 0;

     fis_evaluate();
       float y = g_fisOutput[0];
  printf("fuzzy in e: %f\n", e);
  printf("fuzzy in de: %f\n", de);
  printf("fuzzy out y: %f\n", y);
  //send to serial
  serial_send(y);
}

// timer initialization
void timer_init(int period)
{
 struct sigaction sa;
 struct itimerval timer;

 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &timer_handler;
 sigaction (SIGVTALRM, &sa, NULL);

 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = period;
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = period;
 setitimer (ITIMER_VIRTUAL, &timer, NULL);
 printf("timer init done!\n");
}
*/
