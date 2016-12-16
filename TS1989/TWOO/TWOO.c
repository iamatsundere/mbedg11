/*
 * TWOO.c
 *
 * Created: 12/16/16 4:58:49 PM
 *  Author: truon
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "myLCD.h"
#include "myTWI.h"

//chuong trinh chinh
int main(void){
	char dis[5];

	//PORT D la input va co dien tro keo len
	PORTD=0xFF; 
	DDRD=0x00;	
	Device_Addr=PIND>>6; //xac dinh dia chi cua minh bang 2 chan PD7:PD6
	
	TWI_Init(); //khoi dong TWI
	init_LCD(); //khoi dong LCD
	clr_LCD();	
	sei(); 		//global interrupt	
	
	//gan gia tri cho mang SLAVE_wDATA, du lieu se goi den Master neu duoc yeu cau
	for (int i=0; i<100; i++) SLAVE_wData[i]=i; 
	_delay_ms(200);
	
	sprintf(dis,"%i", Device_Addr);
	print_LCD("Device addr: ");
	print_LCD(dis);
	move_LCD(2,1);
	print_LCD("Sent data: ");
	
	while(1){		
		//in len LCD du lieu cuoi cung goi den Master
		sprintf(dis,"%i", SLAVE_wData[Tran_Num]); 
		move_LCD(2,12);			
		print_LCD(dis);	
	}	
	return 0;
}
