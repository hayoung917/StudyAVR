/*
 * InterruptFND.c
 *
 * Created: 2020-06-15 오후 3:22:28
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;

int main()
{
	unsigned char FND_DATA_TBL[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
	unsigned char cnt = 0;
	
	DDRA = 0XFF;
	DDRE = 0X00;
	
	EICRB = 0XC0;
	EIMSK = 0X80;
	EIFR = 0X80;
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		if(Time_STOP == 0)
		{
			cnt++;
			if(cnt>17)
				cnt = 0;
		}
		_delay_ms(200);
	}
	return 0;
}

SIGNAL(INT7_vect)
{
	
	cli();
	if(Time_STOP == 0)
	{
		Time_STOP = 1;
	}
	else
	{
		Time_STOP = 0;
	}
	sei();
}