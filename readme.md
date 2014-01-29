AVR Mega8 lib
=============
This small library provides basic functions to work with MCU peripherals. It is designated to speed up development and make a base stone to projects with Mega. This library is meant to be some kind of template, guide for beginners.

Based on <http://www.atmel.com/images/atmel-2486-8-bit-avr-microcontroller-atmega8_l_datasheet.pdf>

### Provided functions ###
#### USART ####

	void USART_Init();
	void USART_WriteChar(char data);
	void USART_PrintString(char * InputString);

#### PWM ####

	void PWM_Init();
	void PWM_SetValue(uint8_t duty);
	void PWM_SetPercent(uint8_t duty);

#### ADC ####
	
	void ADC_Init();
	uint8_t ADC_GetVal();

#### I<sup>2</sup>C ####
	
	void I2C_Init();
	void I2C_Data(uint8_t SLA, uint8_t Data);

#### LCD Display (4 bit communication) ####
	
	void DisplayInit();
	void DisplayWriteChar(char Character);
	void DisplayWriteInst(DisplayInstruction Inst);

### Compiling examples ###
You should modify makefile for your needs (actualy set for direct programming with AVR Dragon), change variable PROJECT
to file name (exclude extension)

	make
	make program

