/*
 * Lcd2.c
 *
 * Created: 2020-06-16 오후 2:41:21
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Lcd.h"
int GetNum(char result);

int main()
{
	Byte str[] = "Multiplication";
	Byte str1[] = "Input Switch";
	char Mul[1000];
	char bNum = 0;
		
	DDRA = 0XFF;
	DDRD = 0X00;
	LcdInit_4bit();
	
	while(1)
	{
		bNum = PIND;
		if(PIND == 0X00)
		{
			Lcd_Pos(0,0);
			Lcd_STR(str);
			Lcd_Pos(1,0);
			Lcd_STR(str1);
		}
		else
		{
			int num = GetNum(bNum);	
			Lcd_Clear();
			for(int j = 1; j < 10; j++)
			{
				sprintf(Mul,"%d * %d = %d",num, j, num*j);
				Lcd_Pos(0,0);
				Lcd_STR(Mul);
				_delay_ms(1000);
			}
			Lcd_Clear();
		}
	}
	return 0;
}


int GetNum(char result)
{
	switch(result)
	{
		case 0x01:
		return 2;
		case 0x02:
		return 3;
		case 0x04:
		return 4;
		case 0x08:
		return 5;
		case 0x10:
		return 6;
		case 0x20:
		return 7;
		case 0x40:
		return 8;
		case 0x80:
		return 9;
	}
	return 0;
}