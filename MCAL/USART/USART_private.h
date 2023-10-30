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

#define UBRRL		(*(volatile u8 *)(0x29))
#define UCSRB		(*(volatile u8 *)(0x2A))
#define UCSRA		(*(volatile u8 *)(0x2B))
#define UDR			(*(volatile u8 *)(0x2C))
#define UCSRC		(*(volatile u8 *)(0x40))
#define UBRRH		(*(volatile u8 *)(0x40))


//UCSRB bits
#define RXCIE	7
#define TXCIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

//UCSRC bits
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0

//UCSRA bits
#define RXC		7
#define TXC		6
#define UDRE	5
#define FE		4
#define DOR		3
#define PE		2
#define U2X		1
#define MPCM	0

//USART speed
#define USART_NORMAL_SPEED 0
#define USART_DOUBLE_SPEED 1

#define ENABLE  1
#define DISABLE 0


// Define the UART vector
#define USART_RXC_vect			__vector_13 // UART RX complete Interrupt Vector



#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal)); \
void vector (void)

#endif /* USART_PRIVATE_H_ */