/*
 * TimerLed2.c
 *
 * Created: 2020-06-15 오후 5:10:22
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0;
unsigned char Shift_Flag= 0;

SIGNAL(TIMER2_OVF_vect);

int main()
{
	DDRC = 0XFF;
	TCCR2 = 0X05;			//1024 분주율로 사용
	
	TCNT2 = 183;
	TIMSK = 0X40;			//오버플로우 타이머2번 사용 (비트6번)
	TIFR |= 1 << TOV2;		//TOV2로 옮겨서 초기화(자신과 다른건 0으로 바꿈)
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	
	return 0;
}

SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 183;
	timer2Cnt++;
	
	if(timer2Cnt == 50)
	{
		if(Shift_Flag == 0)
		{
			LED_Data <<= 1;
			if(LED_Data == 0x80)
				Shift_Flag = 1;
		}
		else
		{
			LED_Data >>= 1;
			if(LED_Data == 0x01)
				Shift_Flag = 0;
		}
		timer2Cnt = 0;
	}
	sei();
}