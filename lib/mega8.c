/* 
* AVR MEGA BASIC FUNCTIONS LIBRARY
* File:     mega8.c
* Date:     1/2014
*
* Copyright (c)2014 Lukas Janik <lucaso.janik@gmail.com>
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
#include <util/delay.h>
#include <avr/io.h>
#include <util/twi.h>

//
// USART
//

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
    // in UCSRC and MSB in UCSRB
    // 0 = 5-bit
    // 1 = 6-bit
    // 2 = 7-bit
    // 3 = 8-bit
    // 7 = 9-bit

    // UCSRC.URSEL = 1 selects UCSRC register to write to (else writes to UBRRH, 
    // the space is shared)
    UCSRC =  (1 << URSEL) | (3 << UCSZ0);   

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

    // UBRR sets usart prescaler (UBRRL, UBRRH)
    UBRRL = UBRR_VALUE; 
}

void USART_WriteChar(char data)
{
    while(!(UCSRA & (1<<UDRE)))
     {}
   UDR=data;
}

void USART_PrintString(char * InputString)
{
    while(*InputString != '\0')
    {
        USART_WriteChar(*InputString);
        InputString++;
    }
    
}

//
// PWM
//

void PWM_Init()
{
    // DDRB3 must be set to enable PWM pin for T/C2
    DDRB |=  (1 << DDB3);       
    // TCCR2.CS22:0 selects PWM prescaler
    // 0 = no clock (PWM off)
    // 1 = 1 (directly system clock)
    // 2 = clk/8
    // 3 = clk/64
    // 4 = clk/256
    // 5 = clk/1024
    // 6 = external (T0 pin, falling edge)
    // 7 = external (T0 pin, rising edge)
    TCCR2 |=  (2 << CS20);      

    // TCCR2.WGM21:0 determines waveform generation mode
    // bits 0 and 1 are not neighbouring
    // 0 = normal timer
    // 1 = PWM phase correct
    // 2 = CTC (clear timer on compare match)
    // 3 = fast PWM
    TCCR2 |=  (1 << WGM20) | (1 << WGM21);  

    // TCCR2.COM21:0 determines pin OC2 behavior (although DDR register must 
    // be set accordingly)
    //
    // # Non PWM: #
    // 0 = normal pin function
    // 1 = toggle on compare match
    // 2 = clear on compare match
    // 3 = set on compare match
    //
    // # Fast PWM #
    // 0 = normal pin function
    // 1 = reserved
    // 2 = Clear OC2 on Compare Match, set OC2 at BOTTOM (non-inverting mode)
    // 3 = Set OC2 on Compare Match, clear OC2 at BOTTOM (inverting mode)
    //
    // # Phase correct PWM #
    // 0 = normal port operation
    // 1 = reserved
    // 2 = Clear OC2 on Compare Match when up-counting. 
    //     Set OC2 on Compare Match when downcounting.
    // 3 = Set OC2 on Compare Match when up-counting. 
    //     Clear OC2 on Compare Match when downcounting.
    TCCR2 |=  (2 << COM20);     

    // ASSR.AS2 = 1 sets T/C 2 clock source to external clock on pin TOSC1
    // ASSR |=  (1 << AS2); 

    // TIMSK.OCIE2 = 1 enables T/C 2 output compare match interrupt 
    // TIMSK |=  (1 << OCIE2);  

    // TIMSK.TOIE2 = 1 enables T/C 2 overflow interrupt
    // TIMSK |=  (1 << TOIE2);          
}

void PWM_SetValue(uint8_t duty)
{
    OCR2 = duty;
}

void PWM_SetPercent(uint8_t duty)
{
    OCR2 = (int)(255 * (duty/100.0));
}

//
// ADC
//

void ADC_Init()
{
    // ADMUX.REFS1:0 determines used voltage reference
    // 0 = AREF
    // 1 = AVCC with external cap at AREF pin
    // 3 = Internal 2.56V with external cap at AREF pin
    ADMUX |= (1 << REFS0);

    // ADMUX.ADLAR = 1 shifts 10-bit conversion result left so you can 
    // read 8b result from ADCH
    ADMUX |= (1 << ADLAR);

    // ADMUX.MUX3:0 determines connection between adc unit and MCU pins
    // 0 = ADC0
    // 1 = ADC1
    // 2 = ADC2
    // 3 = ADC3
    // 4 = ADC4
    // 5 = ADC5
    // 6 = ADC6
    // 7 = ADC7
    // 14= 1.30V (VBG)
    // 15= 0V (GND)
    ADMUX |= (5 << MUX0);

    // ADCSRA.ADEN = 1 enables ADC unit
    ADCSRA |= (1 << ADEN);

    // ADCSRA.ADSC starts single measure (in single conversion mode)
    // ADCSRA |= (1 << ADSC);   

    // ADCSRA.ADFR = 1 sets free runing mode
    // ADCSRA |= (1 << ADFR);

    // ADCSRA.ADIE = 1 enables ADC interrupt
    ADCSRA |= (1 << ADIE);          

    // ADCSRA.ADPS2:0 sets ADC prescaler
    // 0 = clk/2
    // 1 = clk/2
    // 2 = clk/4
    // 3 = clk/8
    // 4 = clk/16
    // 5 = clk/32
    // 6 = clk/64
    // 7 = clk/128
    ADCSRA |= (3 << ADPS0);     
}

uint8_t ADC_GetVal()
{
    return ADCH;
}

//
// I2C
//

void I2C_Init()
{
    // TWBR.TWBR7:0 selects TWI bitrate division factor for SCL clock
    TWBR = TWI_PRESCALER;

    // TWCR.TWEN = 1 enables TWI
    // TWCR |= (1 << TWEN);

    // TWCR.TWIE =1 enables TWI interrupts
    TWCR |= (1 << TWIE);     

    // TWSR.TWPS1:0 selects prescaler for TWI
    // 0 = 1
    // 1 = 4
    // 2 = 16
    // 3 = 64
    TWSR |= (1 << TWPS0);   

}

void I2C_Data(uint8_t SLA, uint8_t Data)
{
    // START condition
     TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
     while (!(TWCR & (1 << TWINT))); // cekani na nastaveni flagu
     
     if((TWSR & 0xF8) != TW_START)
        Error();
     
     // Writes destination address, adds write symbol
     TWDR=((SLA << 1) + 1);
     TWCR = (1 << TWINT) | (1 << TWEN);
     // Wait for the transmission
     while (!(TWCR & (1 << TWINT))); 
     
     if((TWSR & 0xF8) != TW_MT_SLA_ACK)
        Error();

     // Sending data
     TWDR = Data;
     TWCR = (1 << TWINT) | (1 << TWEN);
     // Wait for the transmission
     while (!(TWCR & (1<<TWINT))); 
     
     // STOP condition
     TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void Error()
{
    
}

//
// LCD Display
//

void DisplayInit()
{
    // sets R/W pin to zero (sets to write)
    PORTB &= ~(1 << PORTB3);

    // set 4b mode
    PORTC = 0b0010; DisplayClock();

    // st 4b operation 2 line display font 5x8
    PORTC = 0b0010; DisplayClock();
    PORTC = 0b1000; DisplayClock();

    // Turn on display and cursor
    PORTC = 0b0000; DisplayClock();
    PORTC = 0b1110; DisplayClock();

    // Set increment address and shift cursor right
    PORTC = 0b0000; DisplayClock();
    PORTC = 0b0110; DisplayClock();

    // Set cursor to 0 and clear
    PORTC = 0b0000; DisplayClock();
    PORTC = 0b0001; DisplayClock(); 
}

void DisplayClock()
{
    PORTB |= (1 << PORTB4);
    _delay_ms(2);
    PORTB &= ~(1 << PORTB4);
    _delay_ms(1);
}

void DisplayWriteChar(char Character)
{
    // set RS to "1"
    PORTB |= (1 << PORTB5);

    // breaks character to nibbles
    char temp = (Character >> 4);

    DISPLAY_PORT = temp; DisplayClock();
    DISPLAY_PORT = (Character & 0x0f); DisplayClock();

    // set RS back to "0"
    PORTB &= ~(1 << PORTB5);
}

void DisplayWriteInst(uint8_t Inst)
{
    char temp = (Inst >> 4);

    DISPLAY_PORT = temp; DisplayClock();
    DISPLAY_PORT = (Inst & 0x0f); DisplayClock();

}

void DisplayWriteString(char * InputString, const uint8_t address)
{
    // go to address
    DisplayWriteInst((128 | address));

    // write whole string by char
     while(*InputString != '\0')
    {
        DisplayWriteChar(*InputString);
        InputString++;
    }
  
}

//
// Misc
//

uint8_t GetKey(uint8_t ADC_Val)
{
    if(ADC_Val < 15)
        return btnRIGHT;
    if(ADC_Val < 55)
        return btnUP;
    if(ADC_Val < 100)
        return btnDOWN;
    if(ADC_Val < 150)
        return btnLEFT;
    if(ADC_Val < 215)
        return btnSELECT;

    return btnNONE;
}