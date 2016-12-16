/*
 * myTWI.h
 *
 * Created: 12/16/16 4:57:24 PM
 *  Author: truon
 */ 


#include <avr/interrupt.h>


#ifndef cbi 
	#define cbi(port, bit) 	   (port) &= ~(1 << (bit))
#endif
#ifndef sbi 
	#define sbi(port, bit) 	   (port) |=  (1 << (bit))
#endif


//dinh nghia cac duong giao tiep TWI tren AVR, phu thuoc cau truc chan cua tung chip
#define TWI_PORT	PORTC
#define TWI_DDR		DDRC
#define	TWI_PIN		PINC

#define	SDA_PIN		6
#define	SCL_PIN		5
//------------------------------

//FOR SLAVE USE*****************************
#define GENERAL_CALL	1	//1: Enable, 0: Disable General call
	//code for SLAVE Receive----
#define OWN_ADDRESS_MATCH		0x60 //the own address is match,+W 
#define OWN_LOST_MATCH			0x68 //arbitrary lost but still match
#define OWN_DATA_Rec_ACK		0x80 //own data,received then return ACK already
#define OWN_DATA_Rec_NACK		0x88 //own data,received then return NACK 
#define STOP_Rec				0xA0

#define GENERAL_MATCH			0x70 //general call is match,
#define GENERAL_DATA_Rec_ACK	0x90 //general data,received then return ACK already 
#define GENERAL_DATA_Rec_NACK	0x98 //general data,received then return NACK

	//code for SLAVE Transmit----
#define ADDRESS_R_MATCH			0xA8 //the own address is match, Read is required
#define LOST_R_MATCH			0xB0 //Master is lost
#define DATA_Sent_ACK			0xB8 //data is sent, and ACK is received
#define DATA_Sent_NACK			0xC0 //data is sent, and NOT ACK is received, STOP will be sent soon
#define DATA_Last_Sent_ACK		0xC8 //last data is sent, and NOT ACK is received, STOP will be sent soon	

volatile uint8_t Tran_Num=0;		 	//number of transmitted data byte
volatile uint8_t SLAVE_wData[100];	
volatile uint8_t Rec_Num=0;			//number of received data byte
volatile uint8_t SLAVE_mode=0; 		//0: own address mode, 1: General call
volatile uint8_t Device_Addr=1;		//the address in SLAVE mode
volatile uint8_t SLAVE_buff[100]; //wData: data for sending, SLAVE_buff: receive data
//END FOR SLAVE USE************************

//FOR MASTER USE*****************************************

//--rate at 8MHz of CPU_CLock
#define _222K	10
#define _100K	32

//--command for TWCR--------------
#define TWI_W	0
#define TWI_R	1

#define TWI_START	(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)	//0xA4
#define TWI_STOP	(1<<TWINT)|(1<<TWSTO)|(1<<TWEN)	//0x94

#define TWI_Clear_TWINT	(1<<TWINT)|(1<<TWEN)			//0x84
#define TWI_Read_ACK	(1<<TWINT)|(1<<TWEA)|(1<<TWEN)	//0xC4 :clear TWINT for reading, set ACK after reading

//---Status for TWI Master--------
#define _START_Sent		0x08 //START Condition has been sent successful
#define	_R_START_Sent	0x10 //REPEAT START Condition has been sent successful

#define _SLA_W_ACK		0x18 //SLA address, Write bit has been sent, ACK has been received
#define _SLA_W_NACK		0x20 //SLA address, Write bit has been sent, NOT ACK has been received
#define _DATA_ACK		0x28 //DATA has been sent, ACK has been received
#define _DATA_NACK		0x30 //DATA has been sent, NOT ACK has been received

//--Master Receive-----------
#define _SLA_R_ACK		0x40 //SLA address, READ bit has been sent, ACK has been received
#define _SLA_R_NACK		0x48 //SLA address, READ bit has been sent, NOT ACK has been rece
#define _DATA_Rec_ACK	0x50 //DATA has been Received, ACK has been received
#define _DATA_Rec_NACK	0x58 //DATA has been Received, NOT ACK has been received

//FOR MASTER USE********************************************


//Khoi dong TWI
void TWI_Init(void){
	TWSR=0x00; //Prescaler=1
	TWBR=_100K;
	TWAR=(Device_Addr<<1)+GENERAL_CALL;
	TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWIE); //ready for Slave mode: Ack is set, TWI is ENABLE and interrupt is ENABLE	
}


//---MASTER transmitter : array-------------------------------------------------------
uint8_t TWI_Master_Send_array(uint8_t Addr, uint8_t Data[], uint8_t len){
	cbi(TWCR, TWIE);
	//Send START Condition---------------------
	TWCR=TWI_START;
	while((TWCR & 0x80)==0x00);		 //check and wait for TWINT bit=1
	if((TWSR&0xF8) !=_START_Sent){TWI_Init(); return (TWSR&0xF8);}; //START send error, escape anyway
	
	//Send Device Address---------------------
	TWDR=(Addr<<1)+TWI_W; //repare address on TWDR,+W (send procedure)
	TWCR=TWI_Clear_TWINT; //start send address by cleaning TWINT
	while((TWCR & 0x80)==0x00);		 //check and wait for TWINT bit=1
	if((TWSR&0xF8) !=_SLA_W_ACK){TWI_Init(); return (TWSR&0xF8);}; //addresssend error, escape anyway
	
	//send DATA array---------------------
	for (int i=0; i<len; i++){ //repeat the sending proccess until reach the end of data
		TWDR=Data[i]; //repare Data on TWDR
		TWCR=TWI_Clear_TWINT; //start send address by cleaning TWINT
		while((TWCR & 0x80)==0x00);		 //check and wait for TWINT bit=1
		if((TWSR&0xF8) !=_DATA_ACK) { TWI_Init(); return (TWSR&0xF8);}; //data send error, escape anyway	
	}	
	//send the STOP condition
	TWCR=TWI_STOP;	
	TWI_Init();
	return 0;
}

//---MASTER Receiver: array
uint8_t TWI_Master_Read_array(uint8_t Addr, uint8_t rData[], uint8_t len){	
	uint8_t Status;
	cbi(TWCR, TWIE);
	//Send START Condition---------------------
	TWCR=TWI_START;
	while((TWCR & 0x80)==0x00);		 //check and wait for TWINT bit=1
	Status=TWSR&0xF8;
	if(Status !=_START_Sent) {TWCR=TWI_STOP; TWI_Init(); return Status;}; //START send error, escape anyway	
	
	//Send Device Address---------------------
	TWDR=(Addr<<1)+TWI_R; //repare address on TWDR,+R (send procedure)
	TWCR=TWI_Clear_TWINT;  //start send address by cleaning TWINT, not send ACK
	while((TWCR & 0x80)==0x00);		 //check and wait for TWINT bit=1
	Status=TWSR&0xF8;
	if(Status !=_SLA_R_ACK) {TWCR=TWI_STOP; TWI_Init(); return Status;}; //addresssend error, escape anyway

	//Get DATA array---------------------
	for (int i=0; i<len-1; i++){
		TWCR=TWI_Read_ACK; //start read data by cleaning TWINT, set ACK after read each byte
		while ((TWCR & 0x80)==0x00)
		Status=TWSR&0xF8; 
		if (Status!=_DATA_Rec_ACK) {TWCR=TWI_STOP; TWI_Init(); return Status;};	
		rData[i]=TWDR;
	}
	
	//get last byte---------------------
	TWCR=TWI_Clear_TWINT; //start read data by cleaning TWINT, set NOT ACK
	while ((TWCR & 0x80)==0x00)
	Status=TWSR&0xF8;
	if (Status !=_DATA_Rec_NACK) {TWCR=TWI_STOP; TWI_Init(); return Status;};
	rData[len-1]=TWDR;
		
	//send the STOP condition
	TWCR=TWI_STOP;
	TWI_Init();
	return 0;
}



//---------------------------------------------SLAVE INTERRUPT------------------------------
ISR(TWI_vect){
	uint8_t Status;
	Status=TWSR;
	PORTA=Status;
	
	//**********************SLAVE RECEIVER MODE******************
	switch (Status){
	case OWN_ADDRESS_MATCH:		
		SLAVE_mode=0;
		Rec_Num=0;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;	
	case OWN_DATA_Rec_ACK:		
		SLAVE_buff[Rec_Num++]=TWDR;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;
	case OWN_DATA_Rec_NACK:		
		SLAVE_buff[Rec_Num++]=TWDR;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;	
	case GENERAL_MATCH:
		SLAVE_mode=1;
		Rec_Num=0;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;		
	case GENERAL_DATA_Rec_ACK:		
		SLAVE_buff[Rec_Num++]=TWDR;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;
	case GENERAL_DATA_Rec_NACK:		
		SLAVE_buff[Rec_Num++]=TWDR;
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;	
	case  STOP_Rec: 	
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK 
		break;
	//**********************END SLAVE RECEIVER MODE**************
	
	
	//--------------------SLAVE TRANSMITTER MODE----------------
	case ADDRESS_R_MATCH: 	//Match, Read is required
		Tran_Num++;
		TWDR=SLAVE_wData[Tran_Num];
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK
		break;
	case DATA_Sent_ACK:  	//data have been sent, get ACK then now send more
		TWDR=SLAVE_wData[Tran_Num];
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK
		break;
	case LOST_R_MATCH: 	 	//Lost Master but Match Read is required, so send data 
		TWDR=SLAVE_wData[Tran_Num];
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK	
		break;
	case DATA_Sent_NACK: 	//data have been sent, get NOT ACK then now stop, get back Slave mode		
		TWCR |=(1<<TWINT)|(1<<TWEA); //clear TWINT, set ACK
		break;
	//--------------------END SLAVE TRANSMITTER MODE------------	
	default:
		break;
	}
}
