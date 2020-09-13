/*
 * Lcd3.c
 *
 * Created: 2020-06-16 오후 4:19:20
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

volatile unsigned int num = 2;
unsigned int i = 1;

int main()
{
	Byte str[] = "Multiplication";
	Byte str1[] = "Input Switch";
	char Mul[1000];
	
	LcdInit_4bit();
	
	DDRA = 0XFF;
	DDRD = 0X00;
	DDRE = 0X00;
	
	EICRA = 0XFF;
	EICRB = 0XFF;
	
	EIMSK = 0XFF;
	EIFR = 0XFF;
	
	sei();
	
	while(1)
	{
		Lcd_Clear();
		sprintf(Mul,"%d * %d = %d",num, i++, num*i);
		Lcd_Pos(0,0);
		Lcd_STR(Mul);
		_delay_ms(1000);
		
		if(i == 9)
			i = 1;
		
		Lcd_Clear();
	}
	return 0;
}

SIGNAL(INT0_vect){
	cli();
	num = 2;
	i = 0;
	sei();
}

SIGNAL(INT1_vect){
	cli();
	num = 3;
	i = 0;
	sei();
}

SIGNAL(INT2_vect){
	cli();
	num = 4;
	i = 0;
	sei();
}

SIGNAL(INT3_vect){
	cli();
	num = 5;
	i = 0;
	sei();
}

SIGNAL(INT4_vect){
	cli();
	num = 6;
	i = 0;
	sei();
}

SIGNAL(INT5_vect){
	cli();
	num = 7;
	i = 0;
	sei();
}

SIGNAL(INT6_vect){
	cli();
	num = 8;
	i = 0;
	sei();
}

SIGNAL(INT7_vect){
	cli();
	num = 9;
	i = 0;
	sei();
}

	
	
	
