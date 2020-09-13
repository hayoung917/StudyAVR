/*
 * input.c
 *
 * Created: 2020-06-15 오전 10:07:58
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff;
	DDRE = 0x00;
	while(1)
	{
		//PORTA = PINE;
		if(PINE == 0x01)
		{
			PORTA = 0X01;
		}
		else if(PINE == 0x02)
		{
			PORTA = 0x02;
		}
		else if(PINE == 0x04)
		{
			PORTA = 0x04;
		}
	}
	return 0;
}