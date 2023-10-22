/*
 * keypad.c
 *
 *  Created on: Oct 21, 2023
 *      Author: zashr
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "keypad.h"

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number);

u8 KEYPAD_getPressedKey(void){
	u8 col,row;
    DIO_Config colPins[] = {
           {DIO_PORTD, DIO_PIN3, DIO_PIN_INPUT},
           {DIO_PORTD, DIO_PIN5, DIO_PIN_INPUT},
           {DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT},
           {DIO_PORTD, DIO_PIN7, DIO_PIN_INPUT},
       };

    DIO_Config rowPins[] = {
           {DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT},
           {DIO_PORTC, DIO_PIN3, DIO_PIN_OUTPUT},
           {DIO_PORTC, DIO_PIN4, DIO_PIN_OUTPUT},
           {DIO_PORTC, DIO_PIN5, DIO_PIN_OUTPUT}
       };

    // Initialize the keypad col pins
    for (u8 i = 0; i < sizeof(colPins) / sizeof(colPins[0]); i++) {
        DIO_U8SetPinDirection(&colPins[i]);
        //DIO_U8SetPinValue(&keypadPins[i]);
    }

    // Initialize the keypad row pins
    for (u8 i = 0; i < sizeof(rowPins) / sizeof(rowPins[0]); i++) {
        DIO_U8SetPinDirection(&rowPins[i]);
        //DIO_U8SetPinValue(&keypadPins[i]);
    }

    while(1)
    	{
    	/*for loop to set all column pins HIGH*/
    		for (u8 i = 0; i<4 ;i++ )
    		{
    			/*set current pin in Column HIGH*/
    			rowPins[i].value = DIO_PIN_HIGH;
    			DIO_U8SetPinValue(&rowPins[i]);

    		}/*end of for loop*/


    	/*for loop to scan all keypad columns*/
    		for (u8 i = 0 ; i<4 ; i++)
    		{
    			/*set current column pin low to test all row pins to find out which button has been pressed*/
    			rowPins[i].value = DIO_PIN_LOW;
    			DIO_U8SetPinValue(&rowPins[i]);

    			/*for loop to scan and test all keypad row pins*/
    			for (u8 j = 0 ; j<4 ; j++)
    			{
    				u8 key;
    				DIO_U8GetPinValue(&colPins[i], &key);
    				/*check current row pin value*/
    				if ( DIO_PIN_LOW == key )
    				{
    					/*return pressed button value*/
    					return KEYPAD_4x4_adjustKeyNumber((j*KEYPAD_NUM_COLS)+i+1);
    				}
    			}/*end of for loop*/

    			/*set current column pin HIGH again*/
    			rowPins[i].value = DIO_PIN_HIGH;
    			DIO_U8SetPinValue(&colPins[i]);

    		}/*end of for loop*/

    		/*Report no Button pressed*/
    		return '?';
    	}

}


/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number)
{
	u8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}
