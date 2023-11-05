/*
* Fingerprint_prog.c
*
* Created: 11/4/2023 9:31:57 AM
*  Author: Ziad
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/USART/USART_interface.h"
#include "Fingerprint_config.h"
#include "Fingerprint_interface.h"
#include "Fingerprint_private.h"

u8 buffer[25];
u8 byte_no = 0;

void clearBuffer()
{
	for(int i=0; i<25;i++)
	buffer[i]=0xFF;
	byte_no = 0;
}

void receiveCallback(u8 data){
	buffer[byte_no] = data;
	byte_no++;
}


u8 FingerPS_strTemplate(){
	
	u8 store[15]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x06, 0x01, 0x00, 0x00, 0x00, 0x0E};
	
	for (u8 i = 0; i < 15; i++)
	{
		UART_sendByte(store[i]);
	}
	UART_receiveByteAsynchCallBack(receiveCallback);
	//_delay_ms(5);
	while(byte_no != 12);
	
	//calc checksum
	//buffer[9] == 0 return SUCESS else return error code
	//clearBuffer()
	
	return buffer[9];

}


u8 FingerPS_searchFinger(){
	u8 search[17]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x0D};
	for (u8 i = 0; i < 17; i++)
	{
		UART_sendByte(search[i]);
	}
	UART_receiveByteAsynchCallBack(receiveCallback);
	
	//_delay_ms(5);
	while(byte_no != 16);
	
	//calc checksum
	//buffer[9] == 0 return SUCESS else return error code
	//clearBuffer();
	
	return buffer[9];
}
