PROJECT=stepper

CC=avr-gcc -mmcu=atmega8
CFLAGS=-c -Wall -Os

BIN=../bin/
SRC=../lib/mega8.c $(PROJECT).c
OBJ=mega8.o $(PROJECT).o


all: $(PROJECT)        
        
$(PROJECT): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)$(PROJECT).elf
	avr-size --format=avr --mcu=atmega8 $(BIN)$(PROJECT).elf
	avr-objcopy -O ihex -j .text -j .data $(BIN)$(PROJECT).elf $(BIN)$(PROJECT).hex

$(PROJECT).o: $(PROJECT).c
	$(CC) $(CFLAGS) $(PROJECT).c -o $(PROJECT).o
        
mega8.o: ../lib/mega8.c
	$(CC) $(CFLAGS) ../lib/mega8.c -o mega8.o
        
prog:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:$(BIN)$(PROJECT).hex
        
clean:
	rm -rf *.o $(BIN)$(PROJECT).elf $(BIN)$(PROJECT).hex 
