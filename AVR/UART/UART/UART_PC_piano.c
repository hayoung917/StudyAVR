/*
 * UART_PC_piano.c
 *
 * Created: 2020-06-17 오후 4:16:28
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char TX_flag = 0;
volatile char sound_flag = 1;
unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 = data;
	UCSR0A |= 0X20;
}

unsigned char getch(void)
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0X80;
	return data;
}

int main()
{
	unsigned char RX_data = 0;
	unsigned char echo[] = "ECHO >> ";
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
		while(echo[i]!='\0')
		{
			putch(echo[i++]);
		}

		RX_data = getch();
		putch(RX_data);
		
		if(RX_data >= '0' && RX_data <= '8')
		{
			ICR3 = 7372800/DoReMi[RX_data-'0']/7;
			TCCR3A = 0X40;
			_delay_ms(500);
			TCCR3A = 0X00;
		}
	} 
}