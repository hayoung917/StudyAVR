/*
 * Led2.c
 *
 * Created: 2020-06-12 오후 4:43:39
 *  Author: PKNU
 */
 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char LED_Data = 0x01, i;		//int로 바꾸고 범위 8지정해도 됨
	DDRC = 0xFF;
	
	while(1)
	{
		LED_Data = 0x01;		//0x00으로 시작할시 0이 이동해서 불을 켤 수 없음
		
		for(i = 0; i < 7; i++)	//8로 범위 지정시 1이 한번 더 밀려서 0이 됨
		{
			PORTC = LED_Data;
			LED_Data <<= 1;
			_delay_ms(1000);
		}
		for(i = 0; i < 7; i++)
		{
			PORTC = LED_Data;
			LED_Data >>= 1;
			_delay_ms(1000);
		}
	}
	return 0;
}