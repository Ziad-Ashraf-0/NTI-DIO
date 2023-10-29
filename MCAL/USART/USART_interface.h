/*
 * USART_interface.h
 *
 * Created: 10/29/2023 2:20:58 PM
 *  Author: Ziad
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_



void M_USART_void_Init(void);
void UART_sendByte(const u8 data);
u8 UART_recieveByte(void);


#endif /* USART_INTERFACE_H_ */