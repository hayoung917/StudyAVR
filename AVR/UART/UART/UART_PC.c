/*
 * UART_PC.c
 *
 * Created: 2020-06-17 오후 3:59:36
 *  Author: PKNU
 */ 
#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0X20)==0);
	UDR0 = data;
	UCSR0A |= 0X20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0X80;
	return data;
}

int main()
{
	unsigned char text[] = "\r\nWelcom! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	DDRE = 0XFE;
	
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
	while(text[i]!='\0')
	{
		putch(text[i++]);
	}
	i=0;
	while(echo[i]!='\0')
	{
		putch(echo[i++]);
	}
	while(1)
	{
		putch(getch());
	}
}