PROJECT=mega8

CC=avr-gcc -mmcu=atmega8 
CFLAGS=-c -Wall -Os

BIN=../bin/
SRC=$(PROJECT).c
OBJ=$(PROJECT).o


all: $(PROJECT)	 

$(PROJECT).o: $(PROJECT).c
	$(CC) $(CFLAGS) $(PROJECT).c -o $(PROJECT).o
		
clean:
	rm -rf *.o
	

