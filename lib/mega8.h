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

/*
* USART 
*
* UBRR values for U2X=0:
* ----------------------
* clock -->	1MHz  2MHz  4MHz 
* baud v|  UBRR  UBRR  UBRR
* 2400  |  25  	  51    103
* 4800  |  12  	  25     51
* 9600  |  6  	  12
*/

#define UBRR_VALUE 25

void USART_Init();
void USART_WriteChar(char data);
void USART_PrintString(const char * InputString);

// PWM

void PWM_Init();
void PWM_SetValue(uint8_t duty);
void PWM_SetPercent(uint8_t duty);

// ADC

void ADC_Init();
uint8_t ADC_GetVal();


