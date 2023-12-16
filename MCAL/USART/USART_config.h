/*
 * USART_config.h
 *
 * Created: 10/29/2023 2:21:18 PM
 *  Author: Ziad
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_
#define SIM   0
#define FARES 1

#define KIT  SIM


#if (KIT == SIM)
#define  F_CPU 8000000UL
#elif(KIT == FARES)
#define  F_CPU 16000000UL
#endif
/*
Choose one of the following :

USART_NORMAL_SPEED
USART_DOUBLE_SPEED
*/

#define USART_SPEED		USART_DOUBLE_SPEED


/*
Choose one of the following :

ENABLE
DISABLE
*/

#define USART_RX_INTERRUPT					DISABLE
#define USART_TX_INTERRUPT					DISABLE
#define USART_Data_Register_Empty_Interrupt DISABLE
#define Receiver_Enable                     ENABLE
#define Transmitter_Enable					ENABLE

/*
Choose one of the following :

2400
4800
9600
14400
19200
28800
38400
57600
115200
*/

#define BAUD_RATE	9600







#endif /* USART_CONFIG_H_ */