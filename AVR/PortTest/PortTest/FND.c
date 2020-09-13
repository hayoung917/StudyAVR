/*
 * FND.c
 *
 * Created: 2020-06-15 오전 11:03:45
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0XFF;
	while(1)
	{
		PORTA = 0B00111111;	//0X3F;
		_delay_ms(1000);
		PORTA = 0B00000110;	//0X06;
		_delay_ms(1000);
	}
	return 0;
}