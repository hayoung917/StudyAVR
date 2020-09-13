/*
 * PracTimerInterrup.c
 *
 * Created: 2020-06-15 오후 6:20:42
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char LED_Data = 0x00;
unsigned char timer0Cnt = 0;
SIGNAL(TIMER0_OVF_vect);

int main()
{
	DDRC = 0XFF;
	TCCR0 = 0X06;
	TCNT0 = 184;
	TIMSK = 0X01;
	TIFR |= 1 << TOV0;
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 184;
	timer0Cnt++;		//256-72
	
	if(timer0Cnt == 400)
	{
		LED_Data = 0X00;
		
		timer0Cnt = 0;
	}
	else
		LED_Data = 0xff;
	sei();
}