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
	
	// initializes ADC unit
	// ADC_Init();
	DDRD = 1;
	DDRC = (15 << DDC0);
	DDRB = (7 << DDB3);
	
	_delay_ms(1000);
	PORTD = 1;
	// initializes display
	DisplayInit();

	// enables innterupts			
	sei();

	// writes hello string to USART
	USART_PrintString("4-bit display program\r\n");

	DisplayWriteChar('H');
	DisplayWriteChar('e');
	DisplayWriteChar('l');
	DisplayWriteChar('l');
	DisplayWriteChar('o');
	DisplayWriteChar(' ');
	DisplayWriteChar('v');
	DisplayWriteChar('o');
	DisplayWriteChar('l');
	DisplayWriteChar('e');




	
    while(1)
    {
    }
}

ISR(USART_RXC_vect)
{	
	char buffer = UDR;

	switch(UDR)
	{
		case 13: DisplayWriteInst(GoToFirst); break;	// enter
		case 10: DisplayWriteInst(GoToFirst); break;	// enter
		case 8: DisplayWriteInst(Backspace); break; 	// backspace
		default: DisplayWriteChar(buffer);break;
	}
	
	UDR=buffer;
}


