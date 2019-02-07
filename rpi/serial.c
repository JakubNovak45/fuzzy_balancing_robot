/************************************************
Includes
************************************************/
#include "serial.h"

void serial_init(int baudrate, char* port)
{
  struct termios options;
  cfsetospeed(&options, baudrate);
  cfsetispeed(&options, baudrate);
  // Open the Port
  serialPort = open(port, O_RDWR | O_NOCTTY);
  if (serialPort == -1) {
    perror("open_port: Unable to open ");
  }
}

void serial_send(float varToSend)
{
 snprintf(sendBuffer, sizeof(sendBuffer), "%.6f", varToSend);
 int n = write(serialPort,(void*) sendBuffer, strlen(sendBuffer));
 if (n < 0) {
   perror("Write failed - ");
 }
}


