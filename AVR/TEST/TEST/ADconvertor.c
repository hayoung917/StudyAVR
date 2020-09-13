/*
 * ADconvertor.c
 *
 * Created: 2020-06-16 오후 4:55:10
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

#define MAX_STR 16
int main()
{
	unsigned int AdData = 0;
	Byte cds[MAX_STR];
	DDRA = 0XFF;
	DDRF = (1 << DDRF1);	//DDRF1번 출력 나머지 입력 바꿔줌
	ADMUX = 0X00;
	ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1);		//64분주비
	
	LcdInit_4bit();
	while(1)
	{
		//Lcd_Clear();
		//Lcd_STR("Sampling..");
		PORTF = (1 << PORTF1);						//VCC값 줌
		ADCSRA |= (1 << ADSC);						//읽은 아날로그를 디지털로 변환 시작해줘
		
		while((ADCSRA & 0x10)==0x00);				//끝날때 까지 기다림
		AdData = ADC;								//변환된 데이터 읽어옴
		
		sprintf(cds, "Data : %d", AdData);
		Lcd_Clear();
		Lcd_Pos(0,0);
		Lcd_STR(cds);
		_delay_ms(500);
	}
}