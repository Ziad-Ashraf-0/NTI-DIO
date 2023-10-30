/*
 * USART_interface.h
 *
 * Created: 10/29/2023 2:20:58 PM
 *  Author: Ziad
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_



void USART_Init(void);
void UART_sendByte(const u8 data);
u8 MUART_voidRecieveByteSynch(void);
// Set the callback function for UART receive
void UART_setReceiveCallback(void (*ptrfn)(u8));
void UART_receiveByteAsynchCallBack(void);


#endif /* USART_INTERFACE_H_ */