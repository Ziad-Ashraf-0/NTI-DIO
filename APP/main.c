/*
 * main.c
 *
 * Created on: Oct 21, 2023
 * Author: Ziad Ashraf
 */

// Include necessary header files
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
#include "../HAL/ESP8266/ESP32_interface.h"

#include <util/delay.h>


// Main function
int main(void) {
    // Enable global interrupts
    GIE_enable();
    // Initialize USART communication
    USART_Init();
    // Initialize LCD
    H_LCD_void_Init();
	
	ESP8266_Init();
	
	H_LCD_void_sendData('g');

	//H_LCD_void_sendData(ESP8266_Begin());
	UART_sendString("AT");		/* Send AT command to ESP8266 */
	UART_sendString("\r\n");

	
	H_LCD_void_sendData('a');

    // Main loop
    while (1) {

    }
    return 0;
}

