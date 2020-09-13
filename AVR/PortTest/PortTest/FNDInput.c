/*
 * FNDInput.c
 *
 * Created: 2020-06-15 오전 11:17:20
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int Count_TR(unsigned char flag);

int main()
{
	unsigned char FND_DATA_TBL [] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
	
	int cnt = 0;
	unsigned char Switch_flag = 0;
	
	DDRA = 0XFF;
	DDRD = 0X00;
	
	while(1)
	{
		Switch_flag = PIND;
		
		while(PIND != 0X00);
		if(Switch_flag != 0)
			cnt += Count_TR(Switch_flag);
			
		if(cnt < 0)
			cnt = 0;
		else if(cnt > 15)
			cnt = 15;
			
		PORTA = FND_DATA_TBL[cnt];
		_delay_ms(100);
	}
	return 0;
}

int Count_TR(unsigned char flag)
{
	int count = 0;
	switch(flag)
	{
		case 0x01:
			count = 1;
			break;
		case 0x02:
			count = 2;
			break;
		case 0x04:
			count = 3;
			break;
		case 0x08:
			count = 4;
			break;
		case 0x10:
			count = -1;
			break;
		case 0x20:
			count = -2;
			break;
		case 0x40:
			count = -3;
			break;
		case 0x80:
			count = -4;
			break;
		
	}
	return count;
}