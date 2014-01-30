/* 
* 
* File:		display_4b.c
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
#define F_CPU 1000000UL 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "../lib/mega8.h"

int main(void)
{	
	// initializes the USART
	USART_Init();

	// enables output for display pins
	DDRC = (15 << DDC0);
	DDRB = (7 << DDB3);
	
	_delay_ms(1000);

	// initializes display
	DisplayInit();

	// enables innterupts			
	sei();

	// writes hello string to USART
	USART_PrintString("4-bit display program\r\n");
	
	// writes hello string to Display
	DisplayWriteString("First line",0);
	DisplayWriteString("Second line",40); 	// display address 40 is first char on second line

    while(1)
    {

    }
}

ISR(USART_RXC_vect)
{	
	char buffer = UDR;

	switch(buffer)
	{
		// on receiving some special char do:
		case 13: DisplayWriteInst(0xC0); break;	// enter 
		case 10: DisplayWriteInst(0xC0); break;	// enter  > goes to second line
		case 8: DisplayWriteInst(16); DisplayWriteChar(' '); DisplayWriteInst(16); break; 	// backspace = go back, draw space, go back
		case 27: DisplayWriteInst(2); break;				// escape goes to first line, first char
		// if normal char, write it to display directly
		default: DisplayWriteChar(buffer); break;
	}
	
	UDR=buffer;
}

ISR(ADC_vect)
{

}
