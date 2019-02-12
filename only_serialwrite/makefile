CC = gcc
CFLAGS = -O2
OBJFILES = serial.o
TARGET = output

all: $(TARGET)
$(TARGET) : $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) -lm
clean:
	rm -f *.o ./output
