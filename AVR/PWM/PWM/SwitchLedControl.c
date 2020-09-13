/*
 * SwitchLedControl.c
 *
 * Created: 2020-06-17 오전 11:34:37
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Light = 0;
volatile unsigned char Light_flag = 1;

int main()
{
	DDRB = 0XFF;
	DDRD = 0X00;
	DDRE = 0X00;
	
	TCCR2 = (1 << WGM20)|(1 << COM21)|(1 << CS21);					//PC PWM모드, 8분주
	TCNT2 = 0X00;		//타이머2 카운터 초기화
	
	EICRA = 0XFF;		//인터럽트 0,1,2,3 상승엣지 동작
	EICRB = 0XFF;		//인터럽트 4,5,6,7 상승엣지 동작
	EIMSK = 0XFF;		//인터럽트 0,1,2,3,4,5,6,7 허용
	EIFR = 0XFF;		//인터럽트 0,1,2,3,4,5,6,7 플래그 클리어
	
	sei();

	while(1)
	{
		if(Light_flag)
		{
			OCR2 = Light;
			Light_flag = 0;
		}		
	}
	return 0;
}
SIGNAL(INT0_vect)
{
	cli();
	Light = 0;
	Light_flag = 1;
	sei();
}
SIGNAL(INT1_vect)
{
	cli();
	Light -= 51;
	if(Light < 0)
		Light = 0;
	Light_flag = 1;
	
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	Light += 51;
	if(Light > 255)
		Light = 255;
	Light_flag = 1;
	
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	Light -= 51;
	if(Light < 0)
		Light = 0;
	Light_flag = 1;
	
	sei();
}
SIGNAL(INT4_vect)
{
	cli();
	Light += 51;
	if(Light > 255)
		Light = 255;
	Light_flag = 1;
	
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	Light -= 51;
	if(Light < 0)
		Light = 0;
	Light_flag = 1;

	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	Light += 51;
	if(Light > 255)
		Light = 255;
	Light_flag = 1;
	
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	Light = 255;
	Light_flag = 1;
	sei();
}