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



int main(void) {

	
	
	GIE_enable();
	H_LCD_void_Init();
	
	Ultrasonic_init();
	
	


	while (1) {
		H_LCD_void_clearScreen();
		u16 reading = Ultrasonic_readDistance();
		H_LCD_void_sendIntNum(reading);
		_delay_ms(250);
	}

	return 0;
}

