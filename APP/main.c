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
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include <util/delay.h>

void timerCallback(){
	DIO_Config led = {DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT,DIO_PIN_HIGH};
	DIO_U8SetPinDirection(&led);
	DIO_U8SetPinValue(&led);
}

int main(void) {
	DIO_Config led = {DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT};
	DIO_U8SetPinDirection(&led);
		
	GIE_enable();
	
	Timer0_Config timerConfig = {CTC, PRESCALER_1024, OC0_TOGGLE, 250};
    //M_TIMER0_void_setCallBack(timerCallback,COMPARE);
	M_TIMER0_void_Init(&timerConfig);
	//M_TIMER0_void_IntEnable(COMPARE);
	//M_TIMER0_void_setDelayTimeMilliSec(3000);
	M_TIMER0_void_start(&timerConfig);
	
	//_delay_ms(50);
	//H_LCD_void_Init();
	//H_LCD_void_sendBinaryNum(001); // Display the binary value on the LCD
	
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

