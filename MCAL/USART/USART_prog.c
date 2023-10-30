/*
* USART_prog.c
*
* Created: 10/29/2023 2:20:38 PM
*  Author: Ziad
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"



// Array of pointers to functions
void (*Action_Uart[3])(u8) = {NULL, NULL, NULL};


void USART_Init(void){
	
	
	#if(USART_SPEED == USART_DOUBLE_SPEED)
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);
	#endif
	
	/************************** UCSRB Description **************************
	Set each bit with corresponding value
	***********************************************************************/
	UCSRB = ( USART_RX_INTERRUPT << RXCIE ) | ( USART_TX_INTERRUPT << TXCIE ) | ( Receiver_Enable << RXEN ) | ( Transmitter_Enable << TXEN );
	
	/************************** UCSRC Description **************************
	* URSEL   = 1 The URSEL must be one when writing the UCSRC
	* UMSEL   = 0 Asynchronous Operation
	* UPM1:0  = 00 Disable parity bit
	* USBS    = 0 One stop bit
	* UCSZ1:0 = 11 For 8-bit data mode
	* UCPOL   = 0 Used with the Synchronous operation only
	***********************************************************************/
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	
	/* Calculate the UBRR register value */
	u16 ubrr_value = (u16)(((F_CPU / (BAUD_RATE * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}


/*
* Description :
* Functional responsible for send byte to another UART device.
*/
void UART_sendByte(const u8 data)
{
	/*
	* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	* transmitting a new byte so wait until this flag is set to one
	*/
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	* Put the required data in the UDR register and it also clear the UDRE flag as
	* the UDR register is not empty now
	*/
	UDR = data;

}

/*
* Description :
* Functional responsible for receive byte from another UART device.
*/
u8 MUART_voidRecieveByteSynch(void)
{
	u16 Timeout = 50000;
	/* RXC flag is set when the UART receive data so wait until this flag is set to one with timeout*/
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	do 
	{
		if(BIT_IS_SET(UCSRA,RXC)){
			return UDR;
		}
	} while (--Timeout);
	/*
	* Read the received data from the Rx buffer (UDR)
	* The RXC flag will be cleared after read the data
	*/
	return 0;
}

/*
* Description :
* Send the required string through UART to the other UART device.
*/
void UART_sendString(const u8 *Str)
{
	u8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
* Description :
* Receive the required string until the '#' symbol through UART from the other UART device.
*/
void UART_receiveString(u8 *Str)
{
	u8 i = 0;

	/* Receive the first byte */
	Str[i] = MUART_voidRecieveByteSynch();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = MUART_voidRecieveByteSynch();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

void UART_receiveByteAsynchCallBack(void (*ptrfn)(u8)) {
	// Enable UART receiver interrupt
	UCSRB |= (1 << RXCIE);
	//set callback
	Action_Uart[0] = ptrfn;
}

// UART receive interrupt service routine
ISR(USART_RXC_vect) {
	 u8 receivedData = UDR; // Read the received data
	if(Action_Uart[0] != NULL){
		Action_Uart[0](receivedData);
	}
}