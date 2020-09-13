/*
 * PWM.c
 *
 * Created: 2020-06-17 오전 11:21:12
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	unsigned char Light = 0;
	
	DDRB = (1 << DDRB4);
	
	TCCR0 = (1 << WGM00)|(1 <<COM01)|(1 << COM00)|(1 << CS22)|(1 << CS21)|(1 << CS20);
	TCNT0 = 0X00;
   
    while (1) 
    {
		for(Light = 0; Light < 255; Light++)
		{
			OCR0 = Light;
			_delay_ms(100);
		}

		for(Light = 255; 0 < Light; Light--)
		{
			OCR0 = Light;
			_delay_ms(100);
		}
    }
}

