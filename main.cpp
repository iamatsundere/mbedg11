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
	/*qu�t t?ng c?t*/
	PORTC = 0b00000001;//ch?n c?t ??u ti�n
	PORTD = 0b01111110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b00000010;//ch?n c?t th? hai
	PORTD = 0b01111110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b00000100;//ch?n c?t th? ba
	PORTD = 0b00000000;//ch?n h�ng tat ca cac hang
	_delay_ms(10);
	PORTC = 0b00001000;//ch?n c?t th? 4
	PORTD = 0b01111110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b00010000;//ch?n c?t th? 5
	PORTD = 0b01111110;//ch?n h�ng 1
	_delay_ms(10);
}

void QuetTungHang()
{
	/*quet tung hang*/
	PORTD = 0b01111110;//ch?n h�ng 1
	PORTC = 0b00011111;//chon 5 cot
	_delay_ms(5);
	PORTD = 0b01111101;//ch?n h�ng 2
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01111011;//ch?n h�ng 3
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01110111;//ch?n h�ng 4
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01101111;//ch?n h�ng 5
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b01011111;//ch?n h�ng 6
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b00111111;//ch?n h�ng 7
	PORTC = 0b00000100;//chon cot thu 3
	_delay_ms(5);
}

int main(void)
{
	/* Replace with your application code */
	/*Khai b�o c�c ch�n n�o l� ch�n truy?n t�n hi?u ra c�c ch�n ra s? ?? l� 1
	th? t? t??ng ?ng c�c ch�n l� PORT7-POR6-PORT5...PORT0*/
	DDRC = 0b00011111;
	DDRD = 0b01111111;
	while (1)
	{
		//QuetTungHang();
		QuetTungCot();
	}
}


