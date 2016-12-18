/*
 * TLCD2.c
 *
 * Created: 12/18/16 8:08:05 AM
 *  Author: truon
 */ 

#include <avr/io.h>
#include <util/delay.h>

void Drawing()
{
	/*quét t?ng c?t*/
	PORTC = 0b0000001;//ch?n c?t ??u tiên
	PORTD = 0b0110000;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b0000010;//ch?n c?t th? hai
	PORTD = 0b0110110;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b0000100;//ch?n c?t th? ba
	PORTD = 0b0110110;//ch?n hàng tat ca cac hang
	_delay_ms(10);
	PORTC = 0b0001000;//ch?n c?t th? 4
	PORTD = 0b0110110;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b0010000;//ch?n c?t th? 5
	PORTD = 0b0000110;//ch?n hàng 1
	_delay_ms(10);
}



int main(void)
{
	/* Replace with your application code */
	/*Khai báo các chân nào là chân truy?n tín hi?u ra các chân ra s? ?? là 1
	th? t? t??ng ?ng các chân là PORT7-POR6-PORT5...PORT0*/
	DDRC = 0b00011111;
	DDRD = 0b01111111;
	while (1)
	{
		Drawing();
		//QuetTungCot();
	}
}


