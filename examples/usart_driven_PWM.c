
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



