#gcc -o output $(mysql_config --cflags) main.c sm_mysql.c $(mysql_config --libs)
CC = gcc
OBJFILES = main.o mpu6050.o fuzzy.o
TARGET = output

all: $(TARGET)
$(TARGET) : $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) -lm
