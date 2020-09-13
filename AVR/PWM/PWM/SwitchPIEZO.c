/*
 * SwitchPIEZO.c
 *
 * Created: 2020-06-17 오후 1:50:44
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};
volatile unsigned char sound_flag = 1;

int main()
{

	DDRD = 0X00;
	DDRE = 0X08;
	
	TCCR3A = 0X00;
	TCCR3B = (1 << WGM33)|(1<<WGM32)|(1<<CS30);
	TCCR3C = 0X00;
	TCNT3 = 0X0000;
	
	EICRA = 0XFF;
	EICRB = 0XFF;
	EIMSK = 0XFF;
	EIFR = 0XFF;
	
	sei();

	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
	return 0;
}
SIGNAL(INT0_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[0]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT1_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[1]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[2]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[3]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT4_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[4]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[5]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[6]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[7]/7;
	TCCR3A = (1 << COM3A0);
	sound_flag = 1;
	sei();
}