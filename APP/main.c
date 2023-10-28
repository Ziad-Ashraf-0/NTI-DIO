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
#include <util/delay.h>

void timerCallback(){
	DIO_Config led = {DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT,DIO_PIN_HIGH};
	DIO_U8SetPinDirection(&led);
	DIO_U8TogglePin(&led);
}

int main(void) {
	//DIO_Config led1 = {DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT};
	//DIO_U8SetPinDirection(&led1);
	
	GIE_enable();
	
	Timer1_Config timerConfig = {Timer1_NORMAL, Timer1_PRESCALER_1024};
	M_TIMER1_void_setCallBack(timerCallback,TIMER1_OVERFLOW);
	M_TIMER1_void_Init(&timerConfig);
	M_TIMER1_void_IntEnable(TIMER1_OVERFLOW);
	M_TIMER1_void_setDelayTimeMilliSec(5000);
	M_TIMER1_void_start();

	//M_TIMER0_void_setPhaseCorrectPWM(1,80);

	//H_LCD_void_Init();
	//H_LCD_void_sendBinaryNum(001); // Display the binary value on the LCD
	
	//H_LCD_void_gotoXY(2,5);
	//H_LCD_void_sendIntNum(14356);
	//unsigned char Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
	//H_LCD_void_creatCustomChar(Character1,0);
	//H_LCD_void_displayCustomChar(0);
	//H_LCD_void_displayFloat(25.6545);
	

	while (1) {
		
		for (u8 i =0;i<100;i++){
			//M_TIMER0_void_setFastPWM(FREQ_61_HZ,i);
			M_TIMER0_void_setPhaseCorrectPWM(FREQ_61_HZ,i);
		}
		
	}

	return 0;
}

