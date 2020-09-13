/*
 * Interrupt.c
 *
 * Created: 2020-06-15 오후 2:12:45
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;

int main(void)
{
	unsigned char LED_Data = 0x01;
	DDRC = 0X0F;
	DDRE = 0X00;
	EICRB = 0X03;
	EIMSK = 0X10;
	EIFR = 0X10;
	sei();
    /* Replace with your application code */
    while (1) 
    {
		PORTC = LED_Data;
		if(Time_STOP == 0)
		{
			if(LED_Data == 0X08)
				LED_Data = 0x01;
			else
				LED_Data <<= 1;
		}
		_delay_ms(100);
    }
}

SIGNAL(INT4_vect)
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