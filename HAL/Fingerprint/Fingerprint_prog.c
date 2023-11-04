/*
 * Fingerprint_prog.c
 *
 * Created: 11/4/2023 9:31:57 AM
 *  Author: Ziad
 */ 

#include "../MCAL/USART/USART_interface.h"



u8 FingerPS_handShake(){
	u8 handshack[12] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x40,0x00,0x44};
	for (u8 i = 0; i < 12; i++)
	{
		UART_sendByte(handshack[i]);
	}
}