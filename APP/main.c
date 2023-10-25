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


void testCallback(void){
	DIO_Config pinTest;
	pinTest.port= DIO_PORTA;
	pinTest.pin= DIO_PIN6;
	DIO_U8TogglePin(&pinTest);
}


void init(){
	DIO_Config pinTest;
	pinTest.port= DIO_PORTD;
	pinTest.direction= DIO_PIN_INPUT;
	pinTest.pin= DIO_PIN3;
	pinTest.value = DIO_PIN_HIGH;
	DIO_U8SetPinDirection(&pinTest);
	DIO_U8SetPinValue(&pinTest);
	pinTest.port= DIO_PORTA;
	pinTest.direction= DIO_PIN_OUTPUT;
	pinTest.pin= DIO_PIN6;
	DIO_U8SetPinDirection(&pinTest);
}


u16 adcValue = 0;
void getADCValue(u16 value){
	adcValue = value;
}

int main(void) {
	//init();
	// Enable global interrupts
	//GIE_enable();
	//EXTI_enable(EXTI_INT1_ID,FALLING_EDGE);
	//EXTI_setCallBack(EXTI_INT1_ID,testCallback);
	
	// Initialize the 7-segment display
	//segment_Init();

	//ADC_config adcConfig = {AVCC, LeftAdj, SingleADC0, Prescaler_128,Free};
	//ADC_Init(&adcConfig);
	_delay_ms(50);
	H_LCD_void_Init();
	
	//H_LCD_void_gotoXY(2,5);
	//H_LCD_void_sendIntNum(14356);
	//unsigned char Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
	//H_LCD_void_creatCustomChar(Character1,0);
	//H_LCD_void_displayCustomChar(0);


	while (1) {

		H_LCD_void_sendIntNum(KEYPAD_getPressedKey());
				
		//ADC pooling
		//H_LCD_void_sendIntNum(ADC_getDigitalValueSynchNonBlocking(SingleADC0));
		//ADC_getDigitalValueAsynchCallBack(SingleADC0,getADCValue);
		//_delay_ms(500);
		//if(adcValue){
		//H_LCD_void_sendIntNum(adcValue);
		//}

	}

	return 0;
}

