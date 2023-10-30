/*
* main.c
*
*  Created on: Oct 21, 2023
*      Author: Ziad Ashraf
*/
#define  F_CPU 16000000UL
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include "../HAL/Keypad/Keypad_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/TIMER1/TIMER1_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../HAL/Ultrasonic/Ultrasonic_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include <util/delay.h>


u8 g_recievedData =0;



void UartCallback(u8 data){
	g_recievedData = data;
}

int main(void) {

	
	
	GIE_enable();
	H_LCD_void_Init();
	

	
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DIO_Config dataPins[] = {
		{DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT},//PD4 data bin
		{DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT},//PD5 data bin
		{DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT},//PD6 data bin
		{DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT},
	};
	// Initialize RS EN pins
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinDirection(&dataPins[i]);
	}
	
	SPI_Config spi_config = {SPI_MASTER,MSB_FIRST,IDLE_LOW,F_4,SPEED_NORMAL};
	SPI_init(&spi_config);
	u8 key;
	SPI_sendReceiveByteAsync(0x7F,UartCallback);
	_delay_ms(1000);
	SPI_sendReceiveByteAsync(0x7F,UartCallback);
	H_LCD_void_sendData(g_recievedData);
	_delay_ms(1000);
	SPI_sendReceiveByteAsync(0x7F,UartCallback);
	


	while (1) {

	}

	return 0;
}

