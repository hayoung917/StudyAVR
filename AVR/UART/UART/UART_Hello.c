/*
 * UART.c
 *
 * Created: 2020-06-17 오후 3:04:33
 * Author : PKNU
 */ 

#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0X20)==0);
	UDR0 = data;
	UCSR0A |= (1 << UDRE0);		//송신 비트 5번
}

int main(void)
{
    unsigned char text[] = "Hello! world!! \r\n";
	unsigned char i = 0;
	
	DDRE = 0XFE;
	
	UCSR0A = 0X00;
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
    while (text[i]!='\0') 
    {
		putch(text[i++]);
    }
}

