AVR Mega8 lib
=============
This small library provides basic functions to work with MCU peripherals. It is designated to speed up development and make a base stone to projects with Mega. This library is meant to be some kind of template.

Based on <http://www.atmel.com/images/atmel-2486-8-bit-avr-microcontroller-atmega8_l_datasheet.pdf>

### USART ###

	void USART_Init();
	void USART_WriteChar(char data);

### I<sup>2</sup>C ###

	void I2C_Init());

### PWM ###

	void PWM_Init();