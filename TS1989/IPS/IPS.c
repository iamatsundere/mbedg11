/*
 * IPS.c
 *
 * Created: 12/16/16 1:15:40 PM
 *  Author: truon
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "myLCD.h"

#define cbi(port, bit) 	   (port) &= ~(1 << (bit))
#define sbi(port, bit) 	   (port) |=  (1 << (bit))

//dinh nghia cac duong giao tiep SPI tren AVR, phu thuoc cau truc chan cua tung chip
#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define	SCK_PIN		7
#define	MISO_PIN	6
#define	MOSI_PIN	5

#define ADDRESS_PORT	PORTB
#define ADDRESS_DDR		DDRB
#define Slave(i)		i	 //i la thu tu chan tren AVR Master dieu khien cac Slave

volatile uint8_t wData[3]={0, 80, 160}, dis[]; //wData: du lieu de send

//Khoi dong SPI o che do Master 
void SPI_MasterInit(void){
        SPI_DDR |=(1<<SCK_PIN)|(1<<MOSI_PIN);
		SPI_PORT|=(1<<MISO_PIN); //dien tro keo len cho chan MISO 			
        SPCR=(1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0); 
		//SPIE: interrupt, SPE: enable, MSTR: Master mode, CPHA: Phase, SPR1:0: prescaler=128		
		//Setup cho cac chan dieu khien dia chi Slave
		ADDRESS_DDR |=(1<<Slave(2))|(1<<Slave(1))|(1<<Slave(0));
		ADDRESS_PORT|=(1<<Slave(2))|(1<<Slave(1))|(1<<Slave(0)); //keo len muc cao de disable Slavers
}

//Send data, 1 byte, qua SPI
void SPI_Transmit(uint8_t i, uint8_t data){
		cbi(ADDRESS_PORT, Slave(i));
        SPDR=data;
        while (bit_is_clear(SPSR,SPIF)); //cho den khi bit SPIF duoc set, qua trinh truyen ket thuc
		sbi(ADDRESS_PORT, Slave(i));
}

//chuong trinh chinh
int main(){
	SPI_MasterInit(); //khoi dong SPI Master
	_delay_ms(100);	  //cho 1 khoang ngan de Slave kip khoi dong
	while(1){
		SPI_Transmit(0, wData[0]++); if (wData[0]>80)  wData[0]=0;   _delay_ms(10);	//to Salve 0
		SPI_Transmit(1, wData[1]++); if (wData[1]>160) wData[1]=80;  _delay_ms(10);	//to Salve 1
		SPI_Transmit(2, wData[2]++); if (wData[2]>240) wData[2]=160; _delay_ms(10);	//to Salve 2	
		_delay_ms(500);
	}	
	return 0;
}
