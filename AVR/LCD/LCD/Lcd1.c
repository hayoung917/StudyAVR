/*
 * LCD.c
 *
 * Created: 2020-06-16 오후 1:51:30
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

int main(void)
{
    Byte str[] = "YEO Ga Ha ";
	Byte str1[] = "IOT fighting!!";
	DDRA = 0XFF;
	
	LcdInit_4bit();					//LCD 초기화
	
    while (1) 
    {
		Lcd_Pos(0,0);				//행열 위치지정
		Lcd_STR(str);
		Lcd_Pos(1,0);
		Lcd_STR(str1);
    }
}

