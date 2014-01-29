PROJECT=pwm_relay

CC=avr-gcc -mmcu=atmega8 
CFLAGS=-c -Wall -Os

BIN=bin/
SRC=lib/mega8.c examples/adc_usart.c
OBJ=mega8.o adc_usart.o


all: $(PROJECT)	 
	
$(PROJECT): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)$(PROJECT).elf
	avr-size --format=avr --mcu=atmega8 $(BIN)$(PROJECT).elf

adc_usart.o: examples/pwm_relay.c
	$(CC) $(CFLAGS) examples/adc_usart.c -o adc_usart.o
	
mega8.o: lib/mega8.c
	$(CC) $(CFLAGS) lib/mega8.c -o mega8.o
	
prog: 
	avr-objcopy -O ihex -j .text -j .data $(BIN)$(PROJECT).elf $(BIN)$(PROJECT).hex
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:$(BIN)$(PROJECT).hex
	
clean:
	rm -rf *.o $(BIN)$(PROJECT).elf $(BIN)$(PROJECT).hex 
	

