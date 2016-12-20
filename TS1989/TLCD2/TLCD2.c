/*
 * TLCD2.c
 *
 * Created: 12/18/16 8:08:05 AM
 *  Author: truon
 */

#include <avr/io.h>
#include <util/delay.h>

void Drawing() {
	PORTA = 0b0000001;
	PORTB = 0b0110000;
	_delay_ms(100);
	PORTA = 0b0000010;
	PORTB = 0b0110110;
	_delay_ms(100);
	PORTA = 0b0000100;
	PORTB = 0b0110110;
	_delay_ms(100);
	PORTA = 0b0001000;
	PORTB = 0b0110110;
	_delay_ms(100);
	PORTA = 0b0010000;
	PORTB = 0b0000110;
	_delay_ms(100);
}



int main(void) {
	DDRA = 0b0011111;
	DDRB = 0b1111111;
	while (1) {
		Drawing();
	}
}


