CC = gcc
OBJFILES = main.o mpu6050.o fuzzy.o
TARGET = output

all: $(TARGET)
$(TARGET) : $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) -lm
