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
	/*qu�t t?ng c?t*/
	PORTC = 0b0000001;//ch?n c?t ??u ti�n
	PORTD = 0b0110000;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0000010;//ch?n c?t th? hai
	PORTD = 0b0110110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0000100;//ch?n c?t th? ba
	PORTD = 0b0110110;//ch?n h�ng tat ca cac hang
	_delay_ms(10);
	PORTC = 0b0001000;//ch?n c?t th? 4
	PORTD = 0b0110110;//ch?n h�ng 1
	_delay_ms(10);
	PORTC = 0b0010000;//ch?n c?t th? 5
	PORTD = 0b0000110;//ch?n h�ng 1
	_delay_ms(10);
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
		Drawing();
		//QuetTungCot();
	}
}


