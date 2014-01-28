/* 
* AVR MEGA BASIC FUNCTIONS LIBRARY
* File:		mega8.c
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


#include "mega8.h"
#include <avr/io.h>

void USART_Init()
{
	// UCSRA.U2X = 1 doubles the USART transmission speed
	// UCSRA |=  (1<<U2X);	

	// UCSRA.MPCM = 1 enables multi-processor communication mode (addressing) 
	// UCSRA |=  (1<<MPCM);	

	// UCSRB.RXCIE = 1 enables USART Receive complete interrupt
	UCSRB |=  (1 << RXCIE);	

	// UCSRB.TXCIE = 1 enables USART Transmit complete interrupt
	// UCSRB |=  (1 << TXCIE);	

	// UCSRB.UDRIE = 1 enables USART data register empty interrupt enable
	// UCSRB |=  (1 << UDRIE);	

	// UCSRB.RXEN = 1 enables USART Receiver
	UCSRB |=  (1 << RXEN);	

	// UCSRB.TXEN = 1 enables USART Transmitter
	UCSRB |=  (1 << TXEN);

	// UCSRB.UCSZ2 determines number of data bits, !!! UCSZ has two lower bits 
	// in UCSRC and MSB in UCSRC
	// 0 = 5-bit
	// 1 = 6-bit
	// 2 = 7-bit
	// 3 = 8-bit
	// 7 = 9-bit

	// UCSRC.URSEL = 1 selects UCSRC register to write to (else writes to UBRRH, 
	// the space is shared)
	UCSRC |= (1 << URSEL);
	UCSRC |=  (3 << UCSZ0);	

	// UCSRC.UMSEL = 1 sets synchronous transfer mode (else asynchronous)	
	// UCSRC |= (1 << UMSEL);

	// UCSRC.UPM1:0 selects parity mode
	// 0 = disabled
	// 2 = even
	// 3 = odd
	// UCSRC |= (2 << UPM0);

	// UCSRC.USBS = 1 sets 2 stopbits (else 1)
	// UCSRC |= (1 << USBS);	

	// UCSRC.UCPOL selects clock polarity on synchronous mode
	// UCSRC |= (1 << UCPOL);	

	// UBRR sets usart prescaler
	UBRR = UBRR_VALUE;	
}

void USART_WriteChar(char data)
{
	while(!(UCSRA & (1<<UDRE)))
	 {}
   UDR=data;
}