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
#include "../MCAL/TWI/TWI_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/RTC/RTC_interface.h"
#include <util/delay.h>



int main(void) {
	H_LCD_void_Init();
	H_RTC_void_Init();
	Time_Config config = {10,18,59,HOUR_12,PM};
	H_RTC_void_setTime(&config);
	Date_config date_config = {Monday,25,10,23};
	H_RTC_void_setDate(&date_config);
	Time_Config time;
	
	while (1) {
		H_LCD_void_clearScreen();
		H_RTC_void_getDate(&date_config);
		H_RTC_void_getTime(&time);
		H_LCD_void_sendString("TIME : ");
		H_LCD_void_sendIntNum(time.hour);
		H_LCD_void_sendData(':');
		H_LCD_void_sendIntNum(time.minute);
		H_LCD_void_sendData(':');
		H_LCD_void_sendIntNum(time.sec);
		if(time.hour_type == HOUR_12){
			if(time.hour_value == AM){
				H_LCD_void_sendString(" AM");
				}else{
				H_LCD_void_sendString(" PM");
			}			
		}
		H_LCD_void_gotoXY(1,0);
		H_LCD_void_sendString("DATE : ");
		H_LCD_void_sendIntNum(date_config.date);
		H_LCD_void_sendData(':');
		H_LCD_void_sendIntNum(date_config.month);
		H_LCD_void_sendData(':');
		H_LCD_void_sendIntNum(date_config.year);
		_delay_ms(500);
	}

	return 0;
}

