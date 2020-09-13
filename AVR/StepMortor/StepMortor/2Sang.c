/*
 * _2Sang.c
 *
 * Created: 2020-06-18 오전 9:42:15
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char i;
	
	DDRB = 0X20;
	DDRD = 0XF0;
	PORTB &= ~0X20;
	
	while(1)
	{
		for(i = 0; i <12; i++)
		{
			PORTD = 0x30;
			_delay_ms(10);
			PORTD = 0x90;
			_delay_ms(10);
			PORTD = 0xC0;
			_delay_ms(10);
			PORTD = 0X60;
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}
