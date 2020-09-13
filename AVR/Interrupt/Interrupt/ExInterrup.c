/*
 * ExInterrup.c
 *
 * Created: 2020-06-15 오후 7:02:07
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;

int main()
{
	char LED_DATA = 0XFF;
	DDRC = 0XFF;
	DDRE = 0X00;
	EICRB = 0XC0;
	EIMSK = 0X80;
	EIFR = 0X80;
	
	sei();
	
	while(1)
	{
		PORTC = LED_DATA;
		if(Shift_flag == 1)
		{
			LED_DATA = 0XFF;
		}
		else if(Shift_flag == 0)
		{
			LED_DATA = 0;
		}
	}
	return 0;
}

SIGNAL(INT7_vect) //여기서는 간략하게 플래그 변환만 쓰기
{
	cli();
	if(Shift_flag == 1)
	{
		Shift_flag = 0;
	}
	else
	{
		Shift_flag = 1;
	}
	
	sei();
}