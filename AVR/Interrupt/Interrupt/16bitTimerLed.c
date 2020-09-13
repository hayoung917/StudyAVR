/*
 * _16bitTimerLed.c
 *
 * Created: 2020-06-16 오전 11:32:24
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

int main()
{
	DDRC = 0XFF;
	
	TCCR1A = 0X00;
	TCCR1B = (1 << CS10);		//클럭소스 존재 (프리스케일링 없음)
	
	TCNT1 = 0;
	TIMSK = (1 << TOIE1);		//1로 설정되면 타이머1의 오버플로우 인터럽트를 개별적으로 Enable
	TIFR |= 1 << TOV1;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
	timer1Cnt++;
	
	if(timer1Cnt == 112)
	{
		LED_Data++;
		if(LED_Data > 0xff)
			LED_Data = 0;
		
		timer1Cnt = 0;
	}
	sei();
}