/*
* main.c
*
*  Created on: Oct 21, 2023
*      Author: Ziad Ashraf
*/
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include "../HAL/Keypad/Keypad_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include <util/delay.h>



int main(void) {


	_delay_ms(50);
	H_LCD_void_Init();
	
	//H_LCD_void_gotoXY(2,5);
	//H_LCD_void_sendIntNum(14356);
	//unsigned char Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
	//H_LCD_void_creatCustomChar(Character1,0);
	//H_LCD_void_displayCustomChar(0);
	//H_LCD_void_displayFloat(25.6545);
	

	while (1) {
		
		
		
	}

	return 0;
}

