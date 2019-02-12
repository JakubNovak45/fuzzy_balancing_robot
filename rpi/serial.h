#ifndef SERIAL_H
#define SERIAL_H

/************************************************
Includes
************************************************/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>

/************************************************
Global var
************************************************/
char sendBuffer[32];
int serialPort;
/************************************************
Function prototypes
************************************************/
void serial_init(int baudrate, char* port);
void serial_send(float varToSend);
#endif
