/*
 * myLCD.h
 *
 * Created: 9/5/16 1:54:22 PM
 *  Author: truon
 */

#include <util/delay.h>
#include "utils.h"

//_BV() bit value
//There is a way to convert a bit number (usually within a byte register) into a byte 
//value that can be assigned directly to the register. However, sometimes the direct bit numbers are 
//needed as well (e. g. in an SBI() instruction), so the definitions cannot usefully be made as byte 
//values in the first place.

#define sbi(sfr,bit) sfr|=_BV(bit) //turn on bit number in sfr (port...) ex: porta |= 0x80 means turn on bit 7
#define cbi(sfr,bit) sfr&=~_BV(bit) //turn of bit number in sfr (port...) ex: porta &= ~0x80 means turn off bit 7
#define EN                            2
#define RW                           1
#define RS                            0
#define CTRL                       PORTA
#define DDR_CTRL             DDRA

#define DATA_O                  PORTA
#define DATA_I                    PINA
#define DDR_DATA             DDRA
/*
#define LCD8BIT
#define DATA_O                  PORTD
#define DATA_I                    PIND
#define DDR_DATA             DDRD
*/

char Read2Nib() {
	char HNib, LNib;
	DATA_O |=0xF0;

	//có th? ??t dòng code này ? ?ây
	DDR_DATA &=0x0F; //set 4 bits cao cua PORT DATA lam input
	sbi(CTRL,EN); //enable
	//sau dòng này thì LCD s? ??y d? li?u ra các chân data, trong khi các chân này trên c?a AVR 
	//v?n còn ? h??ng output (vì các nhi?m v? tr??c ?ó), nên xung ??t d? li?u có th? x?y ra
	////c?ng có th? ??t dòng code trên ? ?ây
	//DDR_DATA &=0x0F; 
	HNib=DATA_I & 0xF0;
	cbi(CTRL,EN); //disable

	sbi(CTRL,EN); //enable
	LNib = DATA_I & 0xF0;
	cbi(CTRL,EN); //disable
	LNib>>=4;
	return (HNib|LNib);
}

void Write2Nib(uint8_t chr) {
	uint8_t HNib, LNib, temp_data;
	temp_data=DATA_O & 0x0F; //doc 4 bit thap cua DATA_O de mask,

	HNib=chr & 0xF0;
	LNib=(chr<<4) & 0xF0;

	DATA_O =(HNib |temp_data);
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable

	DATA_O =(LNib|temp_data);
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable
}

void Write8Bit(uint8_t chr) {
	DATA_O=chr;   //out 8 bits to DATA Line
	sbi(CTRL,EN); //enable
	cbi(CTRL,EN); //disable
}

void wait_LCD() {
#ifdef LCD8BIT
	while(1) {
		cbi(CTRL,EN); //xóa EN
		cbi(CTRL,RS);  //?ây là Instruction
		sbi(CTRL,RW); //Chieu tu LCD ra ngoai

		DDR_DATA=0xFF; //h??ng data out
		DATA_O=0xFF;    // g?i l?nh ??c BF
		sbi(CTRL,EN);     //enable

		DDR_DATA=0x00; // ??i h??ng data in
		if(bit_is_clear(DATA_I,7)) break;
	}
	cbi(CTRL,EN); //disable for next step
	cbi(CTRL,RW); //ready for next step
	DDR_DATA=0xFF; //Ready to Out
#else
	char temp_val;
	while(1) {
		cbi(CTRL,RS); //RS=0, the following data is COMMAND
		sbi(CTRL,RW); //LCD -> AVR
		temp_val=Read2Nib();
		if (bit_is_clear(temp_val,7)) break;
	}
	cbi(CTRL, RW); //ready for next step
	DDR_DATA=0xFF;//Ready to Out
#endif
	//_delay_ms(1);
}

void init_LCD() {
	DDR_CTRL=0xFF;
	DDR_DATA=0xFF;
//Function set------------------------------------------------------------------------------
	cbi(CTRL,RS);   // the following data is COMMAND
	cbi(CTRL, RW); // AVR->LCD
	cbi(CTRL, EN);
#ifdef LCD8BIT
	Write8Bit(0x38);
	wait_LCD();
#else
	sbi(CTRL,EN); //enable
	sbi(DATA_O, 5);
	cbi(CTRL,EN); //disable
	wait_LCD();
	Write2Nib(0x28);//4 bit mode, 2 line, 5x8 font
	wait_LCD();
#endif
//Display control-------------------------------------------------------------------------
	cbi(CTRL,RS); // the following data is COMMAND
#ifdef LCD8BIT
	Write8Bit(0x0E);
	wait_LCD();
#else
	Write2Nib(0x0E);
	wait_LCD();
#endif
//Entry mode set------------------------------------------------------------------------
	cbi(CTRL,RS); // the following data is COMMAND
#ifdef LCD8BIT
	Write8Bit(0x06);
	wait_LCD();
#else
	Write2Nib(0x06);
	wait_LCD();
#endif
}

void home_LCD() {
	cbi(CTRL,RS); // the following data is COMMAND
#ifdef LCD8BIT
	Write8Bit(0x02);
	wait_LCD();
#else
	Write2Nib(0x02);
	wait_LCD();
#endif
}
void move_LCD(uint8_t y,uint8_t x) {
	uint8_t Ad;
	Ad=64*(y-1)+(x-1)+0x80; // tính mã l?nh
	cbi(CTRL,RS); // the following data is COMMAND
#ifdef LCD8BIT
	Write8Bit(Ad);
	wait_LCD();
#else
	Write2Nib(Ad);
	wait_LCD();
#endif
}

void clr_LCD() { //xóa toàn b? LCD
	cbi(CTRL,RS); //RS=0 mean the following data is COMMAND (not normal DATA)
#ifdef LCD8BIT
	Write8Bit(0x01);
	wait_LCD();
#else
	Write2Nib(0x01);
	wait_LCD();
#endif
}
void putChar_LCD(uint8_t chr) { //hi?n th? 1 ký t? chr lên LCD
	sbi(CTRL,RS); //this is a normal DATA
#ifdef LCD8BIT
	Write8Bit(chr);
	wait_LCD();
#else
	Write2Nib(chr);
	wait_LCD();
#endif
}

void print_LCD(char* str) { //Hi?n th? 1 chu?i ký t?
	unsigned char i;
	unsigned char max=16;

	unsigned char len=strlen(str);

	if (len>=max) {
		for(int j=0; j<len; j++)
			putChar_LCD(str[j]);
	} else {
		for(int k=0; k<(max-len)/2; k++)
			putChar_LCD(' ');
		for(int j=0; j<len; j++)
			putChar_LCD(str[j]);
	}
}
