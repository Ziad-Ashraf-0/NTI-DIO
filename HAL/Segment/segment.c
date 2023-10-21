/*
 * segment.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad
 */

/* 		LIB LAYER 		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "segment.h"


void segment_Init(){
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(DIO_PORTA, DIO_PIN3, DIO_PIN_OUTPUT);

}

void segment_Num(u8 num, u8 segmentNum) {
    // First, clear the relevant pins to 0
	DIO_U8SetPinValue(DIO_PORTA, DIO_PIN2, DIO_PIN_HIGH);
	DIO_U8SetPinValue(DIO_PORTA, DIO_PIN3, DIO_PIN_HIGH);
	DIO_U8SetPinValue(DIO_PORTB, DIO_PIN5, DIO_PIN_HIGH);
	DIO_U8SetPinValue(DIO_PORTB, DIO_PIN6, DIO_PIN_HIGH);

    // Then, set the specified segment pin to 1 based on segmentNum
    switch (segmentNum) {
        case 1:
        	DIO_U8SetPinValue(DIO_PORTA, DIO_PIN3, DIO_PIN_LOW);
            break;
        case 2:
        	DIO_U8SetPinValue(DIO_PORTA, DIO_PIN2, DIO_PIN_LOW);
            break;
        case 3:
        	DIO_U8SetPinValue(DIO_PORTB, DIO_PIN5, DIO_PIN_LOW);
            break;
        case 4:
        	DIO_U8SetPinValue(DIO_PORTB, DIO_PIN6, DIO_PIN_LOW);
            break;
        default:
            // Handle invalid segmentNum, for example, turn off all segments
            break;
    }

    // Now, set pins PB0, PB1, PB2, and PB4 to display the number
    DIO_U8SetPinValue(DIO_PORTB, DIO_PIN0, (num & 0x01) ? DIO_PIN_HIGH : DIO_PIN_LOW);
    DIO_U8SetPinValue(DIO_PORTB, DIO_PIN1, (num & 0x02) ? DIO_PIN_HIGH : DIO_PIN_LOW);
    DIO_U8SetPinValue(DIO_PORTB, DIO_PIN2, (num & 0x04) ? DIO_PIN_HIGH : DIO_PIN_LOW);
    DIO_U8SetPinValue(DIO_PORTB, DIO_PIN4, (num & 0x08) ? DIO_PIN_HIGH : DIO_PIN_LOW);
}


