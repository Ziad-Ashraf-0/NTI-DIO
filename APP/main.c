/*
* main.c
*
*  Created on: Oct 21, 2023
*      Author: Ziad Ashraf
*/
#define  F_CPU 1000000UL
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
	
	DIO_Config adc0 = {DIO_PORTA, DIO_PIN0,DIO_PIN_INPUT};
	DIO_U8SetPinDirection(&adc0);
	
	DIO_Config oc0 = {DIO_PORTB, DIO_PIN3,DIO_PIN_OUTPUT};
	DIO_U8SetPinDirection(&oc0);
	
	// ADPS2:0 = 011 to choose ADC_Clock=F_CPU/16=1Mhz/8=62.5Khz --> ADC must operate in range 50-200Khz
	ADC_config config = {AFREF,LeftAdj,SingleADC0,Prescaler_16};
	ADC_Init(&config);
	
	H_LCD_void_Init();
	
	Timer0_Config timer_config = {FAST_PWM,NO_CLK,OC0_CLR};
	M_TIMER0_void_Init(&timer_config);
	
	M_TIMER0_void_setFastPWM(FREQ_625000_HZ,50);
	
	
	u8 customChar[] = {
		0x07,  // B00111
		0x05,  // B00101
		0x07,  // B00111
		0x00,  // B00000
		0x00,  // B00000
		0x00,  // B00000
		0x00,  // B00000
		0x00   // B00000
	};
	
	H_LCD_void_creatCustomChar(customChar,1);
	
	u8 duty;
	
	

	
	while (1) {
		H_LCD_void_clearScreen();
		u16 temperature = H_LM35_U8_getTemperature();
		// Control logic based on temperature
		if (temperature < 25) {
			// 0% duty cycle (motor off)
			duty = 0;
			M_TIMER0_void_setFastPWM(FREQ_625000_HZ,0);
			} else if (temperature >= 25 && temperature <= 35) {
			// 50% duty cycle (half speed)
			duty = 50;
			M_TIMER0_void_setFastPWM(FREQ_625000_HZ,50);
			} else {
			duty=80;
			// 80% duty cycle (high speed)
			M_TIMER0_void_setFastPWM(FREQ_625000_HZ,80);
		}
		H_LCD_void_sendString("TEMP: ");
		H_LCD_void_sendIntNum(temperature);
		H_LCD_void_displayCustomChar(1);
		H_LCD_void_sendData('C');
		H_LCD_void_gotoXY(1,0);
		H_LCD_void_sendString("DUTY: ");
		H_LCD_void_sendIntNum(duty);
		H_LCD_void_sendString("%");
		_delay_ms(2000);
	}

	return 0;
}

