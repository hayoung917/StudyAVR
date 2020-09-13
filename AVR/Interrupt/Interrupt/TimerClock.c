/*
 * TimerClock.c
 *
 * Created: 2020-06-16 오전 9:42:50
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

volatile unsigned char time_s = 0;
unsigned char timer0Cnt = 0;

int main()
{
	DDRA = 0XFF;
	
	TCCR0 = 0X07;						//프리스캐일러 1024분주 => (1<<cs02)|(1<<cs01)|(1<<cs00)
	OCR0 = 71;							//출력 비교 레지스터 0.01초마다 인터럽트 발생
	TIMSK = 0X02;						//출력비교 인터럽트 활성화(비트 1,7번 출력비교 인터럽트)
	TIFR |= 1 << OCF0;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 71;
	timer0Cnt++;
	
	if(timer0Cnt == 100)
	{
		if(time_s >= 16)
			time_s = 0;
		else
			time_s++;
		timer0Cnt=0;
	}
	sei();
}