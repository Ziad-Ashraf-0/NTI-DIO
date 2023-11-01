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
#include "../HAL/EEPROM/EEPROM_interface.h"
#include <util/delay.h>


u8 duty=0;
u8 freq=0;

void takeUserInput(void){
	u8 key;
	H_LCD_void_clearScreen();
	H_LCD_void_sendString("Enter Duty Cycle (0-100)");
	H_LCD_void_gotoXY(1,0);
	for(u8 i =0; i<3;i++){
		key = KEYPAD_getPressedKey();
		if(key != '#'){
			duty = duty * 10 + key;
		}
		break;
	}
	
	H_LCD_void_clearScreen();
	H_LCD_void_sendString("Choose Freq :");
	H_LCD_void_gotoXY(1,0);
	H_LCD_void_sendString("1- 62.5khz   2- 7.8khz");
	H_LCD_void_gotoXY(2,0);
	H_LCD_void_sendString("3- 976hz   4- 244khz");
	H_LCD_void_gotoXY(3,0);
	H_LCD_void_sendString("5- 61hz");
	freq = KEYPAD_getPressedKey();
	
}

int main(void) {

	H_LCD_void_Init();
	

	while (1) {
		takeUserInput();
		while(1){
			//set motor
			//display speed is ... press # to reconfigure
			//key = getpressedkey
			//if key == # break
		}

	}

	return 0;
}

