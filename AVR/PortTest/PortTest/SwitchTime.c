/*
 * SwitchTime.c
 *
 * Created: 2020-06-15 오전 10:21:12
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char Switch_flag = 0;
	unsigned char Switch_flag_pre = 0x01;		// 0000 0001 최초 delay
	
	DDRA = 0x0F;		// 0000 1111 0~3번 출력
	DDRD = 0x00;		// 0000 0000 D입력
	PORTA = 0x00;		// 0000 0000
	
	while(1)
	{
		Switch_flag = PIND >> 4;	// 0000 0001 -> 0000 0000
									// 0000	0010 -> 0000 0000
									// 0000 0100 -> 0000 0000
									// 0000 1000 -> 0000 0000
									// 0001 0000 -> 0000 0001
									// 0010 0000 -> 0000 0010
									// 0100 0000 -> 0000 0100
									// 1000 0000 -> 0000 1000
									
		if((Switch_flag == 0x01)||(Switch_flag==0x02)||(Switch_flag==0x04)||(Switch_flag==0x08))
		{
			Switch_flag_pre = Switch_flag;
		}
		
		PORTA ^= 0x0f;	// 0000 1111 [BIT OR 연산자 0^1 = 1, 1^1 = 0]
		
		if(Switch_flag_pre == 0x01)
			_delay_ms(250);
		else if(Switch_flag_pre == 0x02)
			_delay_ms(500);
		else if(Switch_flag_pre == 0x04)
			_delay_ms(750);
		else if(Switch_flag_pre == 0x08)
			_delay_ms(1000);
	}
	return 0;
}