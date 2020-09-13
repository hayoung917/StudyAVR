/*
 * PrescalerTimer.c
 *
 * Created: 2020-06-16 오전 9:21:36
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char LED_Data = 0x00;		//volatile : 컴파일러에게 이 변수는 변화하니깐 최적화시키지 말고 이 변수 그대로 사용해달라고 말하는것
unsigned int timer0Cnt = 0;

SIGNAL(TIMER0_OVF_vect);

int main()
{
	DDRC = 0XFF;					//출력포트 설정
	TCCR0 = 0X06;					//프리스캐일러 256분주 사용
	
	TCNT0 = 184;					//8bit -> 256
									//7372800 / 256 = 28800 <- 1s에 클럭이 뛰는 수
									//0.025s->72번 뛰게 설정
									//256 - 72 = 184
	TIMSK = 0X01;					//오버플로우 인터럽트 0번 사용
	TIFR |= 1 << TOV0;				//tov0번으로 이동해서 1로 초기화 나머지는 0
	
	sei();							//전체 인터럽트 사용가능
	
	while(1)
	{
		PORTC = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();							//전체 인터럽트 사용금지
	
	TCNT0 = 184;
	timer0Cnt++;
	
	if(timer0Cnt == 400)			//0.025s설정 했기때문에 1초 만들려면 400
	{
		LED_Data++;
		if(LED_Data > 0xff)			//전체 불 다 켜졌으면 0으로 바꿔줌
			LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();							//전체 인터럽트 사용
}