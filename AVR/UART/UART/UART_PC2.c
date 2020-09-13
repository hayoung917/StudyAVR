/*
 * UART_PC2.c
 *
 * Created: 2020-06-17 오후 6:29:16
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char TX_flag = 0;
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
	
	DDRE = 0x0E;             
	DDRB = 0x80;
	
	TCCR1A |= 0x0A;                     
	TCCR1B |= 0x19;                     
	TCCR1C |= 0x00;                     
	TCNT1 = 0x0000;
	  
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	  
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	  
	ICR1 = 10;
	OCR1C = ICR1/10;
  
	while(1)
	{
		i=0;
		while(echo[i]!='\0')
		{
			putch(echo[i++]);
		}

		RX_data = getch();
		putch(RX_data);
		
		if(RX_data >= '0' && RX_data <= '7')
		{
			ICR1 = 7372800 / DoReMi[RX_data - '0'];
			OCR1C = ICR1 / 10;
			
			_delay_ms(500);
			
			TCCR1A |= 0x0A;
			ICR1 = 10;
			OCR1C = ICR1/10;
		}
		else continue;
	}
}

	
	