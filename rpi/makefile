CC = gcc
CFLAGS = -O2
OBJFILES = main.o mpu6050.o fuzzy.o serial.o
TARGET = output

all: $(TARGET)
$(TARGET) : $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) -lm
clean:
	rm -f *.o ./output
