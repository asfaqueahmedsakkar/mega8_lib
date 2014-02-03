/* 
* AVR MEGA BASIC FUNCTIONS LIBRARY
* File:		mega8.h
* Date:		1/2014
*
* Copyright (c)2014	Lukas Janik <lucaso.janik@gmail.com>
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include <stdint.h>

#define F_CPU 1000000UL 

#define UBRR_VALUE 25
#define TWI_PRESCALER 6

#define DISPLAY_PORT PORTC

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define DIR_LEFT  0
#define DIR_RIGHT 1

#define FULLSTEP	0
#define HALFSTEP	1
#define QUARSTEP	2
#define EIGHSTEP	3
#define SIXTSTEP	4

// determines if steppers are held at position while
// not moving
#define HOLD

// SPEED is between 0 and 10
#define SPEED 8

 // ------------------------------
 // USART 
 // 
 // UBRR values for U2X=0:
 // ----------------------
 // clock -->	1MHz  2MHz  4MHz 
 // baud v|  UBRR  UBRR  UBRR
 // 2400  |  25  	  51    103
 // 4800  |  12  	  25     51
 // 9600  |  6  	  12


void USART_Init();
void USART_WriteChar(char data);
void USART_PrintString(char * InputString);

// PWM

void PWM_Init();
void PWM_SetValue(uint8_t duty);
void PWM_SetPercent(uint8_t duty);

// ADC

void ADC_Init();
uint8_t ADC_GetVal();

// I2C

void I2C_Init();
void I2C_DataSend(uint8_t SLA, uint8_t Data);


// LCD Display
//
// Display		MCU
// ----------------
// RW			PB3
// E			PB4
// RS			PB5
// -
// D4			PC0
// D5			PC1
// D6			PC2
// D7			PC3

// Common instructions
//  0x01 : clear display
//	0x02 : go to first
//	0x04 : go to previous symbol
//	0xC0 : go to second line


void DisplayClock();
void DisplayInit();
void DisplayWriteChar(char Character);
void DisplayWriteInst(uint8_t Inst);
void DisplayWriteString(char * InputString, uint8_t address);


// stepper driver A4988
//
// Driver	MCU
// -----------
// !ENA		PB0
// MS1		PB1
// MS2		PB2
// MS3		GND
// DIR		PB3
// STEP		PB4

void SetStep(uint8_t stepSize);
void Step(uint8_t direction);
void Rotate(uint8_t steps, uint8_t direction);


// misc

void Error();
uint8_t GetKey(uint8_t ADC_Val);
