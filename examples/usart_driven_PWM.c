/* 
*
* File:		usart_driven_PWM.c
* Date:		
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
#include <string.h>
#include "mega8.h"




int main(void)
{	
	// initializes the USART
	USART_Init();
	
	// initializes PWM unit
	PWM_Init();
	
	// sets duty cycle to 100%
	OCR2=255;
	
	// sets PORTD.1 to output
	DDRD = (1 << DDRD1);
	
	// enables innterupts			
	sei();

	// writes hello string to USART
	USART_PrintString("PWM Driver\r\n");
	
    while(1)
    {
		
    }
}

ISR(USART_RXC_vect)
{	
	char buffer[13];
	char received;
	received=UDR;
	//UDR=received; // if uncommented, sent characters will be shown in console (=echo)
	
	switch(received)
	{
		// increases / decreases PWM duty (OCR register) by 1
		case '+':	OCR2 +=1;sprintf(buff,"OCR2: %d\r\n",OCR2); UART_PrintString(&buff); break;	
		case '-':	OCR2 -=1;sprintf(buff,"OCR2: %d\r\n",OCR2); UART_PrintString(&buff); break;
		// increases / decreases PWM duty (OCR register) by 10
		case '*':	OCR2 +=10;sprintf(buff,"OCR2: %d\r\n",OCR2); UART_PrintString(&buff); break;
		case '/':	OCR2 -=10;sprintf(buff,"OCR2: %d\r\n",OCR2); UART_PrintString(&buff); break;
	} 
}



