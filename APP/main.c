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

// Database of names, IDs, and passwords
const s8 *names[] = {"Ahmed Ali", "Sara Omar"};
const s32 IDs[] = {1234, 5678};
const s32 passwords[] = {5060, 1020};
const s32 databaseSize = 2;


int main(void) {

	// Define variables to store the user's input
	s32 enteredID = 0;
	s32 enteredPassword = 0;
	_delay_ms(50);
	H_LCD_void_Init();
	
	//H_LCD_void_gotoXY(2,5);
	//H_LCD_void_sendIntNum(14356);
	//unsigned char Character1[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 };  /* Custom char set for alphanumeric LCD Module */
	//H_LCD_void_creatCustomChar(Character1,0);
	//H_LCD_void_displayCustomChar(0);
	
	
	 // Display a message to enter the ID
	 H_LCD_void_sendString("Enter ID: ");

	 // Get the user's input for ID using the keypad
	 for (u8 i = 0; i < 4; i++) {
		 u8 key = KEYPAD_getPressedKey();
		 H_LCD_void_sendIntNum(key);
		 enteredID = enteredID * 10 + key;
	 }
	 // Clear the LCD screen
	 H_LCD_void_clearScreen();

	 // Display a message to enter the password
	 H_LCD_void_sendString("Enter Password: ");

	 // Get the user's input for the password using the keypad and display '*' characters
	 for (u8 i = 0; i < 4; i++) {
		 u8 key = KEYPAD_getPressedKey();
		 enteredPassword = enteredPassword * 10 + key;
		 H_LCD_void_sendData('*');
	 }
	 
	 H_LCD_void_clearScreen();
	 
	 // At this point, 'enteredID' and 'enteredPassword' variables hold the user's input.
	 // You can compare these values with the database as shown in the previous response.
	 // The following code assumes that you have a database as mentioned earlier.

	 int found = 0;
	 u8 i;
	 for (u8 i = 0; i < databaseSize; i++) {
		 if (enteredID == IDs[i] && enteredPassword == passwords[i]) {
			 found = 1;
			 break;
		 }
	 }

	 // Display appropriate messages based on the comparison results
	 if (found) {
		 H_LCD_void_sendString("Welcome, ");
		 H_LCD_void_sendString(names[i]);
		 } else {
		  // Check if the ID is incorrect
		  int incorrectID = 1;
		  for (u8 i = 0; i < databaseSize; i++) {
			  if (enteredID == IDs[i]) {
				  incorrectID = 0;
				  break;
			  }
		  }

		  if (incorrectID) {
			  H_LCD_void_sendString("Wrong ID");
			  } else {
			  H_LCD_void_sendString("Wrong Password");
		  }
	 }


	while (1) {
		
		
						
	}

	return 0;
}

