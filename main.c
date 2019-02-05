/************************************************
Includes
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "fuzzy.h"
#include "mpu6050.h"
#include <signal.h>
#include <sys/time.h>
#include <string.h>

/************************************************
Global var
************************************************/
int fd;
float angleY;
int acc;
float e,de = 0;
float t1,t2 = 0;


/************************************************
Function prototypes
************************************************/
void timer_init(int period);


/************************************************
Main loop
************************************************/
int main()
{

  mpu6050_init(&fd);
  timer_init(10000);	//10ms period


  while(1){



    }


  return 0;
}











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

  /*
 static int count = 0;
 count += 1;
 //printf ("timer iteration: %d\n",count);
 if(count == 100){
   angleY = get_acc_angle(&fd);
   printf("angleY: %f\n", angleY);
  //printf ("tik tak\n");
	 count = 0;

 }

 */
 //do interrupt routine
}


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
