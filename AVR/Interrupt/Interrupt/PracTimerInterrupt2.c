/*
 * PracTimerInterrupt2.c
 *
 * Created: 2020-06-15 오후 7:21:17
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Shift_flag = 0;
unsigned char LED_DATA = 0X00; 
unsigned int timer0Cnt = 0;

SIGNAL(TIMER0_OVF_vect);

int main()
{
	DDRC = 0XFF;
	TCCR0 = 0X06;
	TCNT0 = 184;
	TIMSK = 0X01;
	TIFR |=1 << TOV0;
	
	sei();
	
	while(1)
	{
		if(Shift_flag == 0)
		{
			LED_DATA = 0Xff;
		}
		else if(Shift_flag == 1)
		{
			LED_DATA = 0x00;
		}
		PORTC = LED_DATA;	
	}
	return 0;	
}



SIGNAL(TIMER0_OVF_vect) //여기서는 간략하게 플래그 변환만 쓰기
{
	cli();
	TCNT0 = 184;
	timer0Cnt++;
	if(timer0Cnt == 400)
	{
		if(Shift_flag == 0)
		{
			Shift_flag = 1;
		}
		else
		{
			Shift_flag = 0;
		}
		timer0Cnt = 0;
	}
	sei();
}