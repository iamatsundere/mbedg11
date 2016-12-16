#include <avr/io.h>
#include <util/delay.h>
#include <font.h>

#define DATA_PORT 	PORTD //PORTD is connected to the data bus of DotMatrix
#define DATA_DDR	DDRD

#define CTRL_PORT 	PORTC //PORTC is connected to control lines of DotMatrix
#define CTRL_DDR	DDRC

void DOTputChar75(uint8_t chr) {
	uint8_t line=1,i;
	uint16_t tchr=chr;
	for(i=0; i<5; i++) {
		CTRL_PORT=line;
		DATA_PORT=~pgm_read_byte(&font7x5[((tchr - 32) * 5) + i]);
		line<<=1;
		_delay_loop_2(1000);
	}
}

int main(void) {
	DATA_DDR=0xFF; // DATA_PORT is selected as an ouput PORT
	CTRL_DDR=0xFF;
	while(1) {
		DOTputChar75('4');
	}
	return 0;
}
