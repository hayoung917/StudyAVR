/*
 * TimerSwitchTime.c
 *
 * Created: 2020-06-17 오전 9:40:29
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

volatile unsigned char time_s = 0;
volatile unsigned char FND_flag = 0, edge_flag = 0;

int main()
{
	DDRA = 0XFF;
	DDRE = 0X00;
	
	TCCR3A = 0X00;
	TCCR3B = (1 << ICES3)|(1 << CS32)|(1 << CS30);			//1024분주, 1로 설정하면 상승에지에서 검출, 카운터 값은 ICR3에 저장되고,
															//입력 캡처 플래그(ICF3)가 설정된 경우 입력 캡쳐 인터럽트 발생
	
	ETIMSK = (1 << TICIE3);									//1로 설정되면 타이머3의 입력캡쳐 인터럽트를 개별적으로 Enable
	ETIFR |= (1 << ICF3);									//입력캡쳐신호 또는 아날로그 비교기로부터의 신호에 의해 캡쳐동작이 수행될때
															//1로 세트되고 입력 캡쳐 인터럽트 발생
															//ICR3레지스터가 TOP 값으로 사용되는 동작 모드에서 TCNT3의 값이 TOP과 같아질때
															//1로 세트되고 인터럽트 발생
															
	sei();
	
	PORTA = FND_DATA_TBL[0];								//포트A에 FND TBL의 값 출력
	
	while(1)
	{
		if(FND_flag)
		{
			if(time_s > 15)
				time_s = 15;
			
			PORTA = FND_DATA_TBL[time_s];
			FND_flag = 0;
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	
	//스위치가 눌릴 시간 측정을 위해 상승에지에서 하강에지까지의 시간을 계산
	
	if(edge_flag == 0)							//상승 에지(스위치 누르면)
	{
		//프리스케일러 1024, 하강에치 캡처 트리거 설정
		TCCR3B = (1 << CS32)|(1 << CS30);
		TCNT3 = 0;								//TCNT3레지스터 0으로 초기화
		ICR3 = 0;								//ICR3 레지스터 0으로 초기화
		edge_flag = 1;
	}
	else                                       // 하강에지(스위치 떼면)
	{
		//프리스케일러 1024, 상승 에지 캡쳐트리거 설정
		TCCR3B = (1 << ICES3)|(1 << CS32)|(1 << CS30);
		count_check = ICR3;
		
		//7372800/1024 = 7200, 1초동안 TCNT의 값
		time_s = count_check/720; //누를 시간 0.1초 단위로 변경
		
		//측정 시간 FND로 출력  0~1.5초까지 측정가능
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}