/*
 * StepMortor.c
 *
 * Created: 2020-06-18 오전 9:32:43
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0X20;
	DDRD = 0XF0;
	PORTB &= ~0X20;
	
    while (1) 
    {
		PORTD = 0X10;
		_delay_ms(10);
		PORTD = 0X20;
		_delay_ms(10);
		PORTD = 0X40;
		_delay_ms(10);
		PORTD = 0X80;
		_delay_ms(10);
    }
}

