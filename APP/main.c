/*
* main.c
*
*  Created on: Oct 21, 2023
*      Author: Ziad Ashraf
*/
#define  F_CPU 16000000UL
// Include necessary libraries and header files
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

// Define the lock duration in seconds
#define LOCK_DURATION_SECONDS 120
#define PASSWORD 1234

// Function prototypes
void setupPins();
void displayWelcomeScreen();
void detectUltrasonic();
u32 getPassword();
void displayLoginPrompt();
void handleLogin(u32 enteredPassword, int *attempts);
void controlLEDs();

// Global LED configurations
DIO_Config led1 = {DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT};
DIO_Config led2 = {DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT};
DIO_Config relay = {DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT,DIO_PIN_HIGH};

int main(void) {
	// Setup Pins leds, relay
	setupPins();

	// Enable Global Interrupts
	GIE_enable();

	// Initialize LCD and Ultrasonic sensor
	H_LCD_void_Init();
	Ultrasonic_init();

	// Counter for unsuccessful login attempts
	int attempts = 0;
	

	while (1) {
		// Clear the LCD screen
		H_LCD_void_clearScreen();

		// Wait for an object to be detected by the Ultrasonic sensor
		detectUltrasonic();
		
		// Display login prompt and handle login
		displayLoginPrompt();
		
		// Get the password from the user	
		u32 password = getPassword();


		handleLogin(password, &attempts);
	}

	return 0;
}

// Function to configure LED pins as output
void setupPins() {
	DIO_U8SetPinDirection(&led1);
	DIO_U8SetPinDirection(&led2);
	DIO_U8SetPinDirection(&relay);
}

// Function to display a welcome message on the LCD
void displayWelcomeScreen() {
	H_LCD_void_clearScreen();
	H_LCD_void_sendString("Welcome User");
	H_LCD_void_gotoXY(1,0);
	H_LCD_void_sendString("Door opened");
	DIO_U8SetPinValue(&relay);
	_delay_ms(2000);
	
	
}

// Function to wait for an object to be detected by the Ultrasonic sensor
void detectUltrasonic() {
	u16 distance =Ultrasonic_readDistance(); 
	while (distance > 15){
		H_LCD_void_clearScreen();
		H_LCD_void_sendString("Distance: ");
		H_LCD_void_sendIntNum(distance);
		distance = Ultrasonic_readDistance(); 
		_delay_ms(1000);
	}
}

// Function to get the password from the user
u32 getPassword() {
	u32 enteredPassword = 0;
	H_LCD_void_gotoXY(1, 0);
	for (int i = 0; i < 4; ++i) {
		enteredPassword = enteredPassword * 10 + KEYPAD_getPressedKey();
		H_LCD_void_sendData('*');
	}
	return enteredPassword;
}

// Function to display a login prompt on the LCD and handle the login process
void displayLoginPrompt() {
	H_LCD_void_clearScreen();
	H_LCD_void_sendString("Pls Enter Password:");
}

// Function to handle the login process, including checking the password and handling lockout
void handleLogin(u32 enteredPassword, int *attempts) {
	if (enteredPassword == PASSWORD) {
		// Successful login
		displayWelcomeScreen();
		controlLEDs();
		} else {
		(*attempts)++;

		if (*attempts >= 3) {
			// Lock system for 2 minutes after 3 unsuccessful attempts
			H_LCD_void_clearScreen();
			H_LCD_void_sendString("System Locked.");
			H_LCD_void_gotoXY(1, 0);
			H_LCD_void_sendString("Please wait.");

			for (int seconds = LOCK_DURATION_SECONDS; seconds > 0; seconds--) {
				H_LCD_void_gotoXY(2, 4);
				H_LCD_void_sendString("Remaining: ");
				u32 minutes = seconds / 60;
				u32 remainingSeconds = seconds % 60;
				H_LCD_void_sendIntNum(minutes);
				H_LCD_void_sendData(':');

				if (remainingSeconds < 10) {
					H_LCD_void_sendData('0');
				}
				H_LCD_void_sendIntNum(remainingSeconds);
				_delay_ms(1000);
			}

			*attempts = 0;
			} else {
			// Incorrect Password
			H_LCD_void_clearScreen();
			H_LCD_void_sendString("Wrong Password.");
			H_LCD_void_gotoXY(1, 0);
			H_LCD_void_sendString("Please try again");
			_delay_ms(500);
		}
	}
}

// Function to control LEDs based on user choice
void controlLEDs() {
	H_LCD_void_clearScreen();
	H_LCD_void_gotoXY(1, 0);
	H_LCD_void_sendString("1- Leds ON");
	H_LCD_void_gotoXY(2, 4);
	H_LCD_void_sendString("2- Leds OFF");

	while (1) {
		u8 choice = KEYPAD_getPressedKey();

		if (choice == 1) {
			led1.value = DIO_PIN_HIGH;
			led2.value = DIO_PIN_HIGH;
			DIO_U8SetPinValue(&led1);
			DIO_U8SetPinValue(&led2);
			} else if (choice == 2) {
			led1.value = DIO_PIN_LOW;
			led2.value = DIO_PIN_LOW;
			DIO_U8SetPinValue(&led1);
			DIO_U8SetPinValue(&led2);
			} else {
			// Handle invalid choice
		}
	}
}

