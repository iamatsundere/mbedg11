/*
* LedMatrixColumn.cpp
*
* Created: 12/17/2016 5:11:38 PM
* Author : anhtu
*/

#include <avr/io.h>
#include <util/delay.h>

void QuetTungCot()
{
	/*quét t?ng c?t*/
	PORTC = 0b00000001;//ch?n c?t ??u tiên
	PORTD = 0b01111110;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b00000010;//ch?n c?t th? hai
	PORTD = 0b01111110;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b00000100;//ch?n c?t th? ba
	PORTD = 0b00000000;//ch?n hàng tat ca cac hang
	_delay_ms(10);
	PORTC = 0b00001000;//ch?n c?t th? 4
	PORTD = 0b01111110;//ch?n hàng 1
	_delay_ms(10);
	PORTC = 0b00010000;//ch?n c?t th? 5
	PORTD = 0b01111110;//ch?n hàng 1
	_delay_ms(10);
}

void QuetTungHang()
{
	/*quet tung hang*/
	PORTD = 0b01111110;//ch?n hàng 1
	PORTC = 0b00011111;//chon 5 cot
	_delay_ms(5);
	PORTD = 0b01111101;//ch?n hàng 2
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01111011;//ch?n hàng 3
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01110111;//ch?n hàng 4
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01101111;//ch?n hàng 5
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01011111;//ch?n hàng 6
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b00111111;//ch?n hàng 7
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
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
		//QuetTungHang();
		QuetTungCot();
	}
}


