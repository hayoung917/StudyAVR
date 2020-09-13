/*
 * _16bitPrescaleTimerLed.c
 *
 * Created: 2020-06-16 오후 12:16:56
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

int main()
{
	DDRC = 0XFF;
	
	TCCR3A = 0X00;								//NOMAL포트 사용
	TCCR3B = (1 << CS32)|(1<<CS30);				//1024분주 사용
	
	TCNT3 = 58336;								//7372800 / 1024 = 7200
												//65536-7200 = 58336
												//16bit 범위 안에 있으므로 분할 안해도 됨
												
	ETIMSK = (1 << TOIE3);						//1로 설정되면 타이머3의 오버플로우 인터럽트를 개별적으로 Enable
	ETIFR |= 1 << TOV3;
	
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER3_OVF_vect)
{
	cli();
	TCNT3 = 58336;
	LED_Data++;
	
	if(LED_Data > 0xff)
		LED_Data = 0;
	sei();
}