/*
 * Interrupt2.c
 *
 * Created: 2020-06-15 오후 2:46:47
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;

int main()
{
	unsigned char LED_Data = 0x01;
	
	DDRC = 0XFF;
	DDRE = 0X00;
	DDRD = 0X00;
	
	EICRA = 0X02;
	EICRB = 0X03;
	
	EIMSK = 0X11;
	EIFR = 0X11;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
		if(Shift_flag == 1)
		{
			if(LED_Data == 0x80)
				LED_Data = 0x01;
			else
				LED_Data <<= 1;
		}
		else if(Shift_flag == 2)
		{
			if(LED_Data == 0X01)
				LED_Data = 0x80;
			else
				LED_Data >>=1;
		}
		_delay_ms(100);
	}
	return 0;
}

SIGNAL(INT0_vect)
{
	cli();
	Shift_flag = 1;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	Shift_flag = 2;
	sei();
}