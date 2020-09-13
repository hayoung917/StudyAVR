/*
 * SwitchUART.c
 *
 * Created: 2020-06-17 오후 3:46:21
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

void putch(unsigned char data)
{
	
	while((UCSR0A & 0X20) == 0);
	UDR0 = data;
	UCSR0A |= 0X20;
}

void putch_Str(char*str)
{
	unsigned char i = 0;
	while(str[i]!='\0')
	putch(str[i++]);
}

int main()
{
	DDRE = 0X02;
	DDRD = 0X00;
	
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
	EICRA = 0XFF;
	EICRB = 0XFF;
	EIMSK = 0XFF;
	EIFR = 0XFF;
	
	sei();
	
	while(1)
	{
		if(TX_flag == 1)
		{
			putch_Str("\n\r Input Switch : ");
			putch(TX_data);
			TX_flag = 0;
		}	
	}
	return 0;
}

SIGNAL(INT0_vect)
{
	cli();
	TX_data = '0';
	TX_flag = 1;
	sei();
}
SIGNAL(INT1_vect)
{
	cli();
	TX_data = '1';
	TX_flag = 1;
	sei();
}
SIGNAL(INT2_vect)
{
	cli();
	TX_data = '2';
	TX_flag = 1;
	sei();
}
SIGNAL(INT3_vect)
{
	cli();
	TX_data = '3';
	TX_flag = 1;
	sei();
}
SIGNAL(INT4_vect)
{
	cli();
	TX_data = '4';
	TX_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	TX_data = '5';
	TX_flag = 1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	TX_data = '6';
	TX_flag = 1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	TX_data = '7';
	TX_flag = 1;
	sei();
}