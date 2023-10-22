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


/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH



/*
 * Description :
 * Get the Keypad pressed button
 */
u8 KEYPAD_getPressedKey(void);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
