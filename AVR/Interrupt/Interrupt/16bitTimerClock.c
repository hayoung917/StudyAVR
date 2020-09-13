/*
 * _16bitTimerClock.c
 *
 * Created: 2020-06-17 오전 9:17:15
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

volatile unsigned char time_s = 0;

int main()
{
	DDRC = 0XFF;
	
	TCCR1A = 0X00;
	TCCR1B = (1 << CS12) | (1 << CS10);		//1024분주 설정
	
	OCR1A = 7200;							//7372800 / 1024
											//1초에 한번 인터럽트 발생
											
	TIMSK = (1 << OCIE1A);					//1로 설정되면 타이머1의 출력비교 인터럽트 A,B를 개별적으로 Enable
	TIFR |= 1 << OCF1A;						//OCF1A, OCF1B : TCNT1레지스터와 출력비교 레지스터 비교하여 같으면 1로 세트되고 출력비교 인터럽트발생
	
	sei();
	
	while(1)
	{
		PORTC = FND_DATA_TBL[time_s];
	}
	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;
	if(time_s >= 17)
		time_s = 0;
	else
		time_s++;
	sei();
}