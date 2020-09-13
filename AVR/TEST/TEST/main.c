/*
 * TEST.c
 *
 * Created: 2020-06-18 오전 10:18:17
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define MAX_STR 16

void LED(void);		//LED함수
void CDS(void);		//ADC함수
void PIANO(void);	//PIANO함수
void STEPMOTER(void);	//stepmotor함수

volatile unsigned int ADC_result = 0;	//ADC 변수
volatile unsigned char Time_STOP = 0;


void putch(unsigned char data)
{
	while((UCSR0A & 0X20) == 0);	//전송 준비 될 때까지 대기
	UDR0 = data;					//데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0X20;	
}

unsigned char getch()
{
	unsigned char data;				//데이터를 받을 때까지 대기
	while((UCSR0A & 0X80)==0);		//수신된 데이터는 UDR0에 저장
	data = UDR0;
	UCSR0A |= 0X80;
	return data;					//읽어온 문자를 반환
}

void putch_Str(char *str)
{
	unsigned char i=0;
	while(str[i]!='\0')
	putch(str[i++]);
}

int main(void)
{
	//메뉴 안내창
    unsigned char text[] =			
		"\r\n ++++ Menu ++++ \r\nL : LED\r\nC : CDS\r\nP : PIANO(0~7)\r\nS : Step Motor\r\npush button : stop\r\n";
		
	unsigned char M_input[] = "INPUT >> ";
	unsigned char i = 0;
	
	//입력 값 저장 변수
	unsigned char RX_data = 0;
	
	DDRE = 0XFE;			//시리얼 입력 출력 포트
	
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
   	//메모장 메뉴 읽고 포트 올리기
    
	while(text[i]!='\0')
	{
		putch(text[i++]);
	}
	
	while(1)
	{
		i = 0;
		Time_STOP = 0;
		while(M_input[i]!='\0')
		{
			putch(M_input[i++]);
		}
		
		RX_data = getch();
		putch(RX_data);
		
		switch(RX_data)
		{
			case 'L':
			{
				LED();
				break;
			}
			case 'C':
			{
				CDS();
				break;
			}
			case 'P':
			{
				PIANO();
				break;
			}
			case 'S':
			{
				STEPMOTER();
				break;
			}
			return 0;
		}
	}
	return 0;
}

void LED(void)	//LED 이동 함수
{
	SIGNAL(INT7_vect);
	unsigned char LED_Data = 0x01,i;
	
	DDRC = 0xFF;
	DDRE = 0X00;
	EICRB = 0XC0;
	EIMSK = 0X80;
	EIFR = 0X80;
	

	sei();
	
	while(1)
	{
		LED_Data = 0x01;		//초기값 지정
		for(i=0; i<7; i++)
		{
			if(Time_STOP == 0)
			{
				PORTC = LED_Data;
				LED_Data <<= 1;
				_delay_ms(500);
			}
		}
		for(i=0; i<7; i++)
		{
			if(Time_STOP == 0)
			{
				PORTC = LED_Data;
				LED_Data >>=1;
				_delay_ms(500);
			}
		}
		if(Time_STOP == 1)
		{
			PORTC = 0X00;
			break;
		}		
	}
}

void CDS(void)
{
	unsigned int AdData = 0;
	char cds[MAX_STR];
	DDRA = 0XFF;
	DDRF = (1 << DDRF1);	//DDRF1번 출력 나머지 입력 바꿔줌
	ADMUX = 0X00;
	ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1);		//64분주비
	
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
	DDRE = 0X00;		//7번 인터럽트
	EICRB = 0XC0;
	EIMSK = 0X80;
	EIFR = 0X80;
	
	sei();
	
	while(1)
	{
		if(Time_STOP == 0)
		{
			PORTF = (1 << PORTF1);						//VCC값 줌
			ADCSRA |= (1 << ADSC);						//읽은 아날로그를 디지털로 변환 시작해줘
					
			while((ADCSRA & 0x10)==0x00);				//끝날때 까지 기다림
			AdData = ADC;								//변환된 데이터 읽어옴
					
			sprintf(cds, "Data : %d", AdData);
			putch_Str(cds);
			_delay_ms(1000);
		}
		else
			return;
	}
}
void PIANO(void)
{
	unsigned char RX_data_P = 0;
	unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};	//피아노 음계
	unsigned char piano[] = "PIANO(number) >> ";
	unsigned char i = 0;
		
	DDRE = 0XFE;
		
	TCCR3A |= 0X0A;
	TCCR3B |= 0X19;
	TCCR3C = 0X00;
	TCNT3 = 0X0000;

	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	UBRR0H = 0X00;
	UBRR0L = 0X03;
		
	while(1)
	{
		i=0;
		while(piano[i]!='\0')
		{
			putch(piano[i++]);
		}

		RX_data_P = getch();
		putch(RX_data_P);
			
		if(RX_data_P >= '0' && RX_data_P <= '8')
		{
			ICR3 = 7372800/DoReMi[RX_data_P-'0']/7;
			TCCR3A = 0X40;
			_delay_ms(500);
			TCCR3A = 0X00;
		}
		else
			break;
	}
}

void STEPMOTER(void)
{
	unsigned char RX_data_S = 0;
	unsigned char step[] = "step(f:nomal,r:reverse) >> ";
	
	unsigned char i = 0;
	
	DDRB = 0X20;
	DDRD = 0XF0;
	PORTB &= ~0X20;
	
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
	DDRE = 0X00;		//7번 인터럽트
	EICRB = 0XC0;
	EIMSK = 0X80;
	EIFR = 0X80;
	sei();
	
	while(step[i]!='\0')
	{
		putch(step[i++]);
	}
	  
	while (1)
	{
		RX_data_S = getch();
		putch(RX_data_S);
		
		if(RX_data_S == 'f')
		{
			while(1)
			{
				if(Time_STOP == 1)
				{
					return;
				}
				PORTD = 0X80;
				_delay_ms(10);
				PORTD = 0X40;
				_delay_ms(10);
				PORTD = 0X20;
				_delay_ms(10);
				PORTD = 0X10;
				_delay_ms(10);
			}
		}
		else if(RX_data_S == 'r')
		{
			while(1)
			{
				if(Time_STOP == 1)
				{
					return;
				}
				PORTD = 0X10;
				_delay_ms(10);
				PORTD = 0X20;
				_delay_ms(10);
				PORTD = 0X40;
				_delay_ms(10);
				PORTD = 0X80;
				_delay_ms(10);
			}
		}
	 }
}
SIGNAL(INT7_vect)
{
	cli();
	Time_STOP = 1;
	sei(); 
}


