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
#include <util/delay.h>


u8 g_edgeCount = 0;
u16 g_timeHigh = 0;
u16 g_timePeriod = 0;

static u32 ovFCounter = 0;
void TimerOVFCallBack()
{	
	ovFCounter++;
}
void ICUtimerCallback(){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		ovFCounter = 0;
		/*
		* Clear the timer counter register to start measurements from the
		* first detected rising edge
		*/
		M_TIMER1_void_clearTimerValue();
		/* Detect falling edge */
		M_TIMER1_void_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = M_TIMER1_void_getInputCaptureValue();
		/* Detect rising edge */
		M_TIMER1_void_setEdgeDetectionType(RISING);
	}
	else if(g_edgeCount == 3)
	{
		/* Store the Period time value */
		g_timePeriod = M_TIMER1_void_getInputCaptureValue();
	}
}

int main(void) {
	//ICU input pin
	//DIO_Config icu_bit = {DIO_PORTD,DIO_PIN6,DIO_PIN_INPUT};
	//DIO_U8SetPinDirection(&icu_bit);
	
	//TIMER0 output pin OC0
	//DIO_Config oc0_bit = {DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT};
	//DIO_U8SetPinDirection(&oc0_bit);
	
	//GIE_enable();
	H_LCD_void_Init();
	

	
	//Timer0_Config timerConfig0 = {FAST_PWM,PRESCALER_1024,OC0_CLR};
	//M_TIMER0_void_Init(&timerConfig0);
	//M_TIMER0_void_setFastPWM(FREQ_976_HZ,30);
	//
	//Timer1_Config timerConfig1 = {Timer1_NORMAL,Timer1_PRESCALER_64};
	//M_TIMER1_void_setCallBack(ICUtimerCallback,TIMER1_ICU);
	//M_TIMER1_void_setCallBack(TimerOVFCallBack,TIMER1_OVERFLOW);
	//M_TIMER1_void_Init(&timerConfig1);
	//M_TIMER1_void_IntEnable(TIMER1_ICU);
	//M_TIMER1_void_IntEnable(TIMER1_OVERFLOW);
	//M_TIMER1_void_setEdgeDetectionType(RISING);
	//M_TIMER1_void_start();
	//while(g_edgeCount < 4);
	//u32 dutyCycle = ((float)(g_timeHigh) / (g_timePeriod)) * 100;
	//H_LCD_void_sendIntNum(dutyCycle);
	//H_LCD_void_sendData('%');
	
	
	M_USART_void_Init();


	while (1) {
		
			u8 key = KEYPAD_getPressedKey();
			UART_sendByte(key);
			H_LCD_void_sendData(key);
		
	}

	return 0;
}

