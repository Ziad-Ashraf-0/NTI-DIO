/*
 * Keypad_private.h
 *
 * Created: 10/25/2023 12:27:00 PM
 *  Author: zashr
 */ 


#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_


/*
* Function responsible for mapping the switch number in the keypad to
* its corresponding functional number for 4x4 keypad
*/
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number);


#endif /* KEYPAD_PRIVATE_H_ */