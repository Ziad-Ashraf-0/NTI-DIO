/*
 * keypad.h
 *
 *  Created on: Oct 21, 2023
 *      Author: zashr
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTA_ID
/*Row connections*/
#define R1 DIO_PIN3
#define R2 DIO_PIN5
#define R3 DIO_PIN6
#define R4 DIO_PIN7

#define KEYPAD_COL_PORT_ID                PORTA_ID
/*Column connections*/
#define C1 DIO_PIN2
#define C2 DIO_PIN3
#define C3 DIO_PIN4
#define C4 DIO_PIN5

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH



/*
 * Description :
 * Get the Keypad pressed button
 */
u8 KEYPAD_getPressedKey(void);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
