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
#include <stdlib.h>     /* srand, rand */

void processLedRoutine();


// Define the 4-byte key
u8 key[4] = {0xAA, 0xBB, 0xCC, 0xDD};

// Function to encrypt a 4-byte data block using XOR
void encrypt(uint8_t *plaintext, uint8_t *ciphertext) {
	for (uint8_t i = 0; i < 4; ++i) {
		ciphertext[i] = plaintext[i] ^ key[i];
	}
}

typedef enum{
	ACCESS,
	NO_ACCESS
}access;

u8 state = NO_ACCESS;


// Main function
int main(void) {
	// Enable global interrupts
	GIE_enable();
	// Initialize USART communication
	USART_Init();
	// Initialize LCD
	H_LCD_void_Init();
	
	// 4-byte data to encrypt
	u8 plaintext[4] = {0x01, 0x23, 0x45, 0x67};
	
	// 4-byte random to encrypt
	u8 randomtext[4] = {0};
	
	//receive buffer
	u8 buffer[4] = {0};
	
	//receive buffer
	u8 ciphertext[4] = {0};


	// Encrypt the data
	encrypt(plaintext, ciphertext);
	

	// Main loop
	while (1) {
		
		for(int i=0;i<4;i++){
			buffer [i] = MUART_voidRecieveByteSynch();
		}
		
		if(buffer[0] == 0x31 && buffer[1] == 0x01){
			processLedRoutine();

			}else if(buffer[0] == 0x27 && buffer[1]==0x01){
			  for (u8 i = 0; i < 4; ++i) {
				  randomtext[i] = rand() % 256;  // % 256 limits the range to 0-255
			  }
			}else if(buffer[0] == 0x27 && buffer[1] ==0x02){
			for(int i=0;i<4;i++){
				ciphertext [i] = MUART_voidRecieveByteSynch();
			}
			
				// Encrypt the data
				encrypt(randomtext, ciphertext);
			
			//calculate cipher from random4 bytes and compare with recived ciphertext
			// if = set state to ACCESS and 6702 on lcd
			//else 7f 27 35 on lcd
			
		}
		

		

		
		
		_delay_ms(5000);
	}
	return 0;
}



void processLedRoutine(){
	if(state == ACCESS){
		H_LCD_void_sendHexNum(0x71);
		H_LCD_void_sendData(' ');
		H_LCD_void_sendHexNum(0x01);
		H_LCD_void_sendData(' ');
		H_LCD_void_sendHexNum(0xAA);
		H_LCD_void_sendData(' ');
		H_LCD_void_sendHexNum(0x00);
		}else{
		H_LCD_void_sendHexNum(0x7F);
		H_LCD_void_sendData(' ');
		H_LCD_void_sendHexNum(0x31);
		H_LCD_void_sendData(' ');
		H_LCD_void_sendHexNum(0x33);
	}
}