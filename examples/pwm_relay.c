/* 
*
* File:		pwm_relay.c
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
#include <stdio.h>
#include <util/delay.h>
#include "../lib/mega8.h"




int main(void)
{	
	// initializes the USART
	USART_Init();
	
	// initializes PWM unit
	PWM_Init();

	// initializes ADC unit
	ADC_Init();

	DDRC |= (1 << DDC5) | (1 << DDC4);
	PORTC |= (1 << PORTC5) | (1 << PORTC4);
	
	// sets duty cycle to 100%
	OCR2=255;
	
	// sets PORTD.1 to output
	DDRD = (1 << DDD1);
	
	// enables innterupts			
	sei();

	// writes hello string to USART
	USART_PrintString("PWM Driver\r\n");
	
    while(1)
    {
		ADCSRA |= (1 << ADSC);
		_delay_ms(400);
    }
}

ISR(USART_RXC_vect)
{	
	char received;
	received=UDR;
	//UDR=received; // if uncommented, sent characters will be shown in console (=echo)
	
	switch(received)
	{
		// increases / decreases PWM duty (OCR register) by 1
		case '+':	OCR2 +=1; break;	
		case '-':	OCR2 -=1; break;
		// increases / decreases PWM duty (OCR register) by 10
		case '*':	OCR2 +=10; break;
		case '/':	OCR2 -=10; break;
		// toggles PC4 pin (relay1)
		case '1':	PORTC ^= (1 << PORTC4); break;
		// toggles PC5 pin (relay2)
		case '2':	PORTC ^= (1 << PORTC5); break;

	} 
}

ISR(ADC_vect)
{
	char * buffer = "00000000000000";
	uint8_t pomocna = ADCH * 500 / 255;
	uint8_t r1 = (PORTC & (1 << PORTC4) ) ? 0 : 1;
	uint8_t r2 = (PORTC & (1 << PORTC5) ) ? 0 : 1;
	sprintf(buffer,"Temp: %d\tPWM:%d\tR1:%d\tR2:%d \r",pomocna,OCR2,r1,r2);

	USART_PrintString(buffer);
}



