/*
 * USART_private.h
 *
 * Created: 10/29/2023 2:21:41 PM
 *  Author: Ziad
 */ 


#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

/*************************************************************************************/
/* 								USART REGISTERS										 */
/*************************************************************************************/

typedef struct {
	u8 UBRRL;
	u8 UCSRB;
	u8 UCSRA;
	u8 UDR;
	u8 padding[19];
	u8 UCSRC;
}Usart_Type;

#define USART_BASE ((volatile Usart_Type *) 0x29)



#endif /* USART_PRIVATE_H_ */