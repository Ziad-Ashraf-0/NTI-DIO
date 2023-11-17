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

volatile u8 buffer[30];
volatile static u8 byte_no = 0;


void receiveCallback(u8 data){
	buffer[byte_no] = data;
	byte_no++;
}


Error_FingerPS_t FingerPS_Init(void)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	UART_receiveByteAsynchCallBack(receiveCallback);

	return ret;
}


Error_FingerPS_t FingerPS_AuraLedControl(AuraLightControl_t l_code, u8 l_speed, AuraColorControl_t l_color, u8 l_count)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	u8 i;
	u8 Frame_TX[16]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, l_code, l_speed, l_color, l_count, 0x00, 0x00};
	u16 sum= 0;

	sum= FingerPS_calcCheckSum(Frame_TX, 16);
	Frame_TX[14]= (u8)(sum >> 8);
	Frame_TX[15]= (u8)(sum & 0x00FF);

	/* Send Command Frame using UART Sync */
	for(i= 0; i<16; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	/* Wait till Receive ACK Frame (Using RX Interrupt) */
	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;

	return ret;
}


Error_FingerPS_t FingerPS_handShake(void)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;
	u8 Frame_TX[12]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x40, 0x00, 0x44};
	
	for (u8 i = 0; i < 12; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}
	
	/* Wait till Receive ACK Frame (Using RX Interrupt) */
	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;

	return ret;
}


Error_FingerPS_t FingerPS_genImg(void)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	u8 Frame_TX[12]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};

	for(u8 i= 0; i<12; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;
	
	return ret;
}


Error_FingerPS_t FingerPS_convertImg2CharFile(Template_Buffer_t bufferID)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	u8 Frame_TX[13]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, bufferID, 0x00, 0x00};

	u16 sum= FingerPS_calcCheckSum(Frame_TX, 13);
	Frame_TX[11]= (u8)(sum >> 8);
	Frame_TX[12]= (u8)(sum);

	for(u8 i= 0; i<13; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;
	
	return ret;
	
}


Error_FingerPS_t FingerPS_genTemplate(void)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	u8 Frame_TX[12]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09};

	for(u8 i= 0; i<12; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;
	return ret;
}



Error_FingerPS_t FingerPS_strTemplate(Template_Buffer_t bufferId, u16 pageId){
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;

	u8 Frame_TX[15]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x06, bufferId, (pageId>>8), pageId, 0x00, 0x00};
	u16 sum= FingerPS_calcCheckSum(Frame_TX, 15);
	Frame_TX[13]= (u8)(sum >> 8);
	Frame_TX[14]= (u8)sum;

	for(u8 i= 0; i<15; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;

	return ret;

}


Error_FingerPS_t FingerPS_searchFinger(Template_Buffer_t bufferId, u16 startPage, u16 pageNum){
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;
	u8 Frame_TX[17]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, bufferId, (startPage>>8), (startPage), (pageNum>>8), (pageNum), 0x00, 0x00};
	u16 sum= FingerPS_calcCheckSum(Frame_TX, 17);
	Frame_TX[15]= (u8)(sum >> 8);
	Frame_TX[16]= (u8)sum ;

	for(u8 i= 0; i<17; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 16);
	ret= buffer[9];
	byte_no= 0;

	return ret;
}


Error_FingerPS_t FingerPS_DeleteFinger(u16 l_startPage, u16 l_numOfTemp)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;
	u8 i;
	u8 Frame_TX[16]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x0C, (l_startPage>>8), l_startPage, (l_numOfTemp>>8), l_numOfTemp, 0x00, 0x00};
	u16 sum= 0;

	sum= FingerPS_calcCheckSum(Frame_TX, 16);
	Frame_TX[14]= (u8)(sum >> 8);
	Frame_TX[15]= (u8)sum;

	for(i= 0; i<12; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;

	return ret;
}


Error_FingerPS_t FingerPS_EmptyLibrary(void)
{
	Error_FingerPS_t ret= FAILED_TO_OPERATE_COMM_PORT;
	u8 i;
	u8 Frame_TX[12]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0D, 0x00, 0x11};

	for(i= 0; i<12; i++)
	{
		UART_sendByte(Frame_TX[i]);
	}

	while(byte_no < 12);
	ret= buffer[9];
	byte_no= 0;
	return ret;
}



static u16 FingerPS_calcCheckSum(u8 *arr , u8 length)
{
	u16 sum = 0 ;
	
	for(int i = 6 ; i<length-2 ; i++)
	{
		sum = sum + arr[i];
	}
	return sum ;
}


