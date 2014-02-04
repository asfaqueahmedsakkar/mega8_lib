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
	void I2C_DataSend(uint8_t SLA, uint8_t Data);

#### LCD Display (HD44780U - like) ####
	
	void DisplayInit();
	void DisplayWriteChar(char Character);
	void DisplayWriteInst(uint8_t Inst);
	void DisplayWriteString(char * InputString, uint8_t address);

#### Analog keyboard recognition (Arduino Display shield - like) ####

	uint8_t GetKey(uint8_t ADC_Val);

#### Stepper driver 4988 ####

	void SetStep(uint8_t stepSize);
	void Step(uint8_t direction);
	void Rotate(uint8_t steps, uint8_t direction);	

### Examples ###

Directory examples contains few code examples ready to be directly loaded into device, pin connections are commented out in mega8.h or right into the example code.

#### Compilation ####

You should modify makefile for your needs (now set for programming with AVR Dragon), change variable PROJECT to file name (exclude extension)

	make
	make prog

