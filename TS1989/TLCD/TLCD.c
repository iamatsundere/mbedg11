/*
 * TLCD.c
 *
 * Created: 12/16/16 1:55:33 AM
 *  Author: truon
 */

#include <avr/io.h>
#include <util/delay.h>

#include "myLCD.h" //include th? vi?n myLCD
int main() {
	init_LCD(); //kh?i ?? LCD
	clr_LCD(); // xóa toà b? LCD
	//putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	//putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	//putChar_LCD('D'); //Hi?n th? kýt
	print_LCD("123456789"); //hi?n th? chu?i th? 2
	move_LCD(2,1);//di chuy?n cursor ??n dòng 2, c?t ??u tiên
	//home_LCD();
	print_LCD("2x16 LCD Display"); //hi?n th? chu?i th? 2
	while(1) {

	};
}
