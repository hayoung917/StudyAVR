/*
 * PortTest.c
 *
 * Created: 2020-06-12 오후 2:10:26
 * Author : PKNU
 */ 

#include <avr/io.h>	//입출력 헤더파일

int main()
{
	DDRA = 0xFF;	//포트A 출력으로 설정
	while(1)
	{
		PORTA = 0xFF;
	}
	
	return 0;
}



