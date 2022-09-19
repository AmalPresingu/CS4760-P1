CC = gcc
OBJECTS = main.o
CFLAGS = -Wall -g
TARGET = chain

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

main.o: main.c
	$(CC) -c main.c

clean:
	/bin/rm -f *.o output.dat $(TARGET)
	/bin/rm -f *.out
