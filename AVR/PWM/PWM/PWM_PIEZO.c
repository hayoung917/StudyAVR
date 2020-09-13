/*
 * PWM_PIEZO.c
 *
 * Created: 2020-06-17 오후 12:18:51
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};
	
int main()
{
	unsigned char piano = 0;
	
	DDRB = 0X80;
	
	TCCR1A |= 0X0A;
	TCCR1B |= 0X19;
	TCCR1C = 0X00;
	TCNT1 = 0X0000;
	
	while(1)
	{
		ICR1 = 7372800/DoReMi[piano];
		OCR1C = ICR1/4;
		piano++;
		if(8 < piano)
			piano = 0;
		
		_delay_ms(1000);
	}
	return 0;
}