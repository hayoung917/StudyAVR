/*
 * registerTest.c
 *
 * Created: 2020-06-12 오후 3:52:38
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	while(1)
	{
		DDRC = 0x03;		//LED0, 1출력모드, LED2, 3 입력모드로 설정 0x03 => 0000 0011
		PORTC = 0x0F;		//LED0~3 모두 1로 출력 0x0F => 0000 1111 
		_delay_ms(500);		//500ms 시간 지연
		
		PORTC = 0x00;		//LED0~3 모두 0으로 출력
		_delay_ms(500);		//500ms 시간 지연
		
		DDRC = 0x0C;
		PORTC = 0x0F;
		_delay_ms(500);
		
		PORTC = 0x00;
		_delay_ms(500);	
	}
	return 0;
}