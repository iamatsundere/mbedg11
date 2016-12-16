/*
 * TWO.c
 *
 * Created: 12/16/16 4:47:36 PM
 *  Author: truon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "myLCD.h"
#include "myTWI.h"
volatile uint8_t Slave_Addr;//dia chi Slave
//chuong trinh chinh
int main(void){
	uint8_t Data[50], i;//Data: du lieu tam thoi, goi cho Slaves
	TWI_Init();	//khoi dong TWI
	init_LCD(); //khoi dong LCD
	clr_LCD();	
	
	//khoi dong ngat INT0----------------
	PORTD=0xFF;	//pull-up
	DDRD=0x00;	
	MCUCR	|=(1<<ISC01); // falling edge
    GICR    |=(1<<INT0);  // enable INT0
	//----------------------------------	
	sei(); //global interrupt
		
	_delay_ms(100); //cho de cac Slaves san sang;	
	
	//thu goi 1 mang du lieu den Slave 2
	for (i=0; i< 50; i++) Data[i]=i;
	TWI_Master_Send_array(2,Data,40);
	
	//thu goi 1 mang du lieu den Slave 3
	for (i=0; i< 50; i++) Data[i]=i*2;
	TWI_Master_Send_array(3,Data,50);

	print_LCD("From Slave : ");	
	while(1){		
	}	
	return 0;
}
//trinh phuc vu ngat INT0 (nhan button)
ISR (INT0_vect){	
	uint8_t res, rData[2];
	char dis[5];
	Slave_Addr =PIND & 0x03; //xac dinh Slave de giao tiep
	res=TWI_Master_Read_array(Slave_Addr,rData,1); //Master nhan du lieu	
	//in dia chi Slave len LCD (dong 1)
	move_LCD(1,12);
	sprintf(dis,"%i", Slave_Addr);	
	print_LCD(dis);	
	//in du lieu nhan tu Slave len LCD (dong 2)
	sprintf(dis,"%i", rData[0]);	
	move_LCD(2,1);
	print_LCD("   ");
	move_LCD(2,1);
	print_LCD(dis);
}