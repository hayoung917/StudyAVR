/*
 * TimerInterruptFND.c
 *
 * Created: 2020-06-16 오전 10:18:56
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
	
volatile unsigned char time_s = 0;
volatile unsigned char Time_STOP = 0;

unsigned char timer0Cnt = 0;
SIGNAL(TIMER2_COMP_vect);
SIGNAL(INT4_vect);

int main()
{
	DDRA = 0XFF;						//출력포드 설정
	DDRE = 0X00;						//입력포트 설정(인터럽트4번은 e포트 사용)
	
	TCCR2 = (1 << CS22)|(1 << CS20);	//1024분주 사용
	
	OCR2 = 71;							//0.01초에 한번 인터럽트 발생
										//7372800/1024 = 7200
										//1/7200 = 1.388888888888889e-4‬
										//1.388888888888889e-4‬ * (OCR2 + 1) = 0.01s 
										//(1.388888888888889e-4‬ * (OCR2 + 1))*timeCnt = 1s
										//OCR2 = 71
										
										
	TIMSK = (1 << OCIE2);				//타이머 2번사용
	TIFR |= (1 << OCF2);				//타이머 2번 이동 후 나머지 초기화
	
	EICRB = (1 << ISC41)|(1 << ISC40);	//인터럽트 4번을 상승엣지에서 사용
	EIMSK = (1 << INT4);				//인터럽트 4번 허용
	EIFR = (1 << INTF4);				//인터럽트 4번 플래그 클리어
	
	sei();								//모든 인터럽트 사용가능
	
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}

SIGNAL(TIMER2_COMP_vect)
{
	cli();
	OCR2 += 71;						//0.01초 인터럽트 발생
	timer0Cnt++;
	
	if(timer0Cnt == 50)				//0.5초 반복
	{
		if(Time_STOP == 0)
		{
			if(time_s >= 16)
				time_s = 0;
			else
				time_s++;
		}
		timer0Cnt=0;
	}
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	if(Time_STOP == 0)
		Time_STOP = 1;
	else
		Time_STOP = 0;
		
	sei();
}