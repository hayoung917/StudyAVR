/*
 * LedTest1.c
 *
 * Created: 2020-06-12 오후 3:39:32
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	
	while(1)
	{
		PORTA = 0x00;
		_delay_ms(1000);
		PORTA = 0xFF;
		_delay_ms(1000);
	}
	return 0;
}
