/*
 * FND2.c
 *
 * Created: 2020-06-15 오전 11:08:51
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	// 7-segment에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL [] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};
	unsigned char cnt = 0;
	
	DDRA = 0xff;
	
	while(1)
	{
		PORTA = FND_DATA_TBL[cnt];
		cnt++;
		if(cnt>17) cnt = 0;
		_delay_ms(500);	//주파수 안맞추면 딜레이값 안먹을 수 있다.
	}
	return 0;
}
