/*
* Fingerprint_prog.c
*
* Created: 11/4/2023 9:31:57 AM
*  Author: Ziad
*/
#define  F_CPU 16000000UL
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/USART/USART_interface.h"
#include "Fingerprint_config.h"
#include "Fingerprint_interface.h"
#include "Fingerprint_private.h"
#include <util/delay.h>

u8 buffer[25];
u8 byte_no = 0;

void clearBuffer()
{
	for(int i=0; i<25;i++){
		buffer[i]=0xFF;
	}	
	byte_no = 0;
}

void receiveCallback(u8 data){
	buffer[byte_no] = data;
	byte_no++;
}


u8 FingerPS_strTemplate(u8 bufferId, u16 pageId){
	byte_no = 0;
	
	u8 store[15]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x06, bufferId, (pageId & 0xFF00) >> 8 , pageId, 0x00, 0x0E};
	
	for (u8 i = 0; i < 15; i++)
	{
		UART_sendByte(store[i]);
	}
	UART_receiveByteAsynchCallBack(receiveCallback);
	_delay_ms(5);
	//while(byte_no != 12);
	
	//calc checksum
	//buffer[9] == 0 return SUCESS else return error code
	//clearBuffer()
	
	return buffer[9];

}


u8 FingerPS_searchFinger(u8 bufferId, u16 startPage, u16 pageNum){
	byte_no = 0;
	u8 search[17]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, bufferId, (startPage & 0xFF00) >> 8, startPage, (pageNum & 0xFF00) >> 8, pageNum, 0x01, 0x0D};
	for (u8 i = 0; i < 17; i++)
	{
		UART_sendByte(search[i]);
	}
	UART_receiveByteAsynchCallBack(receiveCallback);
	
	_delay_ms(5);
	//while(byte_no != 16);
	
	//calc checksum
	//buffer[9] == 0 return SUCESS else return error code
	//clearBuffer();
	
	return buffer[9];
}

u8 FingerPS_handShake()
{
	byte_no = 0;
	//clearBuffer();
	u8 HandFrame[12]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x40, 0x00, 0x44};
	//u8 size=sizeof(HandFrame)/sizeof(HandFrame[0]);
	
	for (u8 i = 0; i < 12; i++)
	{
		UART_sendByte(HandFrame[i]);
	}
	
	UART_receiveByteAsynchCallBack(receiveCallback);
	_delay_ms(5);
	//while(byte_no != 2);
	
	//Call Check Sum Func()
	//Call Clear Buffer()
	
	return buffer[9];
}


u8 FingerPS_genImg()
{
	byte_no = 0;
	u8 GetImgFrame[]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
	u8 size=sizeof(GetImgFrame)/sizeof(GetImgFrame[0]);
	
	for (u8 i = 0; i < size; i++)
	{
		UART_sendByte(GetImgFrame[i]);
	}
	
	UART_receiveByteAsynchCallBack(receiveCallback);
	_delay_ms(5);
	
	return buffer[9];
	
	//Call Check Sum Func()
	//Call Clear Buffer()
}


u8 FingerPS_genTemplate(void)
{
	byte_no = 0;
	char arr [13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x05,0x00,0x09};

		for (int i = 0; i<12 ;i++)
		{
			UART_sendByte(arr[i]);
			
		}
	
	UART_receiveByteAsynchCallBack(receiveCallback);
	_delay_ms(5);
	
	return buffer[9];
}

u8 FingerPS_convertImg2CharFile(u8 bufferID)
{
	byte_no = 0;
	char arr [13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,bufferID,0x00,0x08};

		for (int i = 0; i<13 ;i++)
		{
			UART_sendByte(arr[i]);			
		}			
	UART_receiveByteAsynchCallBack(receiveCallback);
	_delay_ms(5);
	
	return buffer[9];
	
}


