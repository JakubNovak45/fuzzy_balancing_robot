/************************************************
Includes
************************************************/
#include "serial.h"

void serial_init(int baudrate, char* port)
{
  // Open the Port
  serialPort = open(port, O_RDWR | O_NOCTTY);
  if (serialPort == -1) {
    perror("open_port: Unable to open ");
    exit(1);
  }

  struct termios options;
  if (tcgetattr(serialPort, &options) != 0) {
	perror("tcgetattr");
    exit(1);
  }
  cfmakeraw(&options); // vynulovat strukturu na RAW (zadne prevody newlines atd)
  cfsetspeed(&options, baudrate); // input a output speed je stejny
  if(tcsetattr(serialPort, TCSAFLUSH, &options) != 0) {
	perror("tcsetattr");
	exit(1);
  }
}

void serial_send(float varToSend)
{
 char sendBuffer[32];
 snprintf(sendBuffer, sizeof(sendBuffer), "%.6f ", varToSend);
 int n = write(serialPort,(void*) sendBuffer, strlen(sendBuffer));
 if (n < 0) {
   perror("Write failed - ");
 }
}

