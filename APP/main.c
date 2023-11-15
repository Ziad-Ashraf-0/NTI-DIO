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
#include "../MCAL/WDT/WDT_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/RTC/RTC_interface.h"
#include "../HAL/Fingerprint/Fingerprint_interface.h"
#include "../HAL/LM35/LM35_interface.h"

#include <util/delay.h>


int main(void) {
	GIE_enable();
	USART_Init();
	H_LCD_void_Init();
	//FingerPS_strTemplate(0x01, 0xF769);
	
		H_LCD_void_clearScreen();
		
		u8 key = FingerPS_genImg();
		H_LCD_void_sendHexNum(key);
		//for (u8 i =0;i<12;i++)
		//{
			//H_LCD_void_sendHexNum(buffer[i]);
		//}
		_delay_ms(1000);
		//key=FingerPS_convertImg2CharFile(1);
		//H_LCD_void_sendHexNum(key);
		//_delay_ms(1000);
		//key = FingerPS_genImg();
		//H_LCD_void_sendHexNum(key);
		//_delay_ms(1000);
		//key=FingerPS_convertImg2CharFile(2);
		//H_LCD_void_sendHexNum(key);
		//_delay_ms(1000);
		//key=FingerPS_genTemplate();
		//H_LCD_void_sendHexNum(key);
		//_delay_ms(1000);
		//
		//key=FingerPS_strTemplate(2,0);
		//H_LCD_void_sendHexNum(key);
		//_delay_ms(1000);
		

	
	while (1) {
			//H_LCD_void_clearScreen();
			//key = FingerPS_genImg();
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(1000);
			//key=FingerPS_convertImg2CharFile(1);
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(1000);
			//key = FingerPS_genImg();
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(1000);
			//key=FingerPS_convertImg2CharFile(2);
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(1000);
			//key=FingerPS_genTemplate();
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(1000);
			//key =FingerPS_searchFinger(1, 0, 4);
			//H_LCD_void_sendHexNum(key);
			//_delay_ms(2000);
		
	}

	return 0;
}

