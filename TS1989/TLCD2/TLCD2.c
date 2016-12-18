/*
 * TLCD2.c
 *
 * Created: 12/18/16 8:08:05 AM
 *  Author: truon
 */ 

#include <avr/io.h>
#include <util/delay.h>

void QuetTungCot()
{
	/*qu�t t?ng c?t*/
	PORTC = 0b0000001;//ch?n c?t ??u ti�n
	PORTD = 0b0000000;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0000010;//ch?n c?t th? hai
	PORTD = 0b1110110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0000100;//ch?n c?t th? ba
	PORTD = 0b1110110;//ch?n h�ng tat ca cac hang
	_delay_ms(10);
	PORTC = 0b0001000;//ch?n c?t th? 4
	PORTD = 0b1110110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0010000;//ch?n c?t th? 5
	PORTD = 0b1110000;//ch?n h�ng 1
	_delay_ms(10);
}

void QuetTungHang()
{
	/*quet tung hang*/
	PORTD = 0b1111011;//ch?n h�ng 1
	PORTC = 0b0011111;//chon 5 cot
	_delay_ms(5);
	PORTD = 0b1111101;//ch?n h�ng 2
	PORTC = 0b0000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b1111011;//ch?n h�ng 3
	PORTC = 0b0000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b1110111;//ch?n h�ng 4
	PORTC = 0b0000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b1101111;//ch?n h�ng 5
	PORTC = 0b0000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b1011111;//ch?n h�ng 6
	PORTC = 0b0000100;//chon cot thu 3
	_delay_ms(5);
	PORTD = 0b0111111;//ch?n h�ng 7
	PORTC = 0b0000100;//chon cot thu 3
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
		QuetTungHang();
		//QuetTungCot();
	}
}


