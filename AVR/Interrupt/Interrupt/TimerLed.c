/*
 * Timer.c
 *
 * Created: 2020-06-15 오후 4:47:11
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;
SIGNAL(TIMER0_0VF_vect);

int main()
{
	DDRC = 0XFF;
	TCCR0 = 0X07;
	TCNT0 = 0XFF-72;
	TIMSK = 0X01;
	TIFR |=1 << TOV0;
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
}
SIGNAL(TIMER0_OVF_vect)
{
	
	cli();
	TCNT0 = 0XFF-72;
	timer0Cnt++;
	if(timer0Cnt == 100)
	{
		LED_Data++;
		if(LED_Data>0XFF)
			LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();
}
