/*
 * segment.c
 *
 * Created on: Oct 21, 2023
 * Author: Ziad
 */

/* LIB LAYER */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "segment.h"

void segment_Init() {
    DIO_Config segmentPins[] = {
        {DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT},
        {DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT},
        {DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT},
        {DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT},
        {DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT},
        {DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT},
        {DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT},
        {DIO_PORTA, DIO_PIN3, DIO_PIN_OUTPUT}
    };

    // Initialize the segment pins
    for (u8 i = 0; i < 4; i++) {
        DIO_U8SetPinDirection(&segmentPins[i]);
    }
}

void segment_Num(u8 num, u8 segmentNum) {
    // First, clear the relevant pins to 0
	// First, clear the relevant pins to 0
	DIO_Config clearPins[] = {
	    {DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
	    {DIO_PORTA, DIO_PIN3, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
	    {DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
	    {DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT, DIO_PIN_HIGH}
	};

	for (u8 i = 0; i < 4; i++) {
	    DIO_U8SetPinValue(&clearPins[i]); // Set pin value to low
	}

	// Then, set the specified segment pin to 1 based on segmentNum
	DIO_Config segmentPins[] = {
	    {DIO_PORTA, DIO_PIN3, DIO_PIN_OUTPUT, DIO_PIN_LOW},
	    {DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT, DIO_PIN_LOW},
	    {DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT, DIO_PIN_LOW},
	    {DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT, DIO_PIN_LOW}
	};

	if (segmentNum >= 1 && segmentNum <= 4) {
	    DIO_U8SetPinValue(&segmentPins[segmentNum - 1]); // Set segment pin value to high
	}

	DIO_Config displayPins[] = {
	    {DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT, DIO_PIN_LOW}, // Pin 0
	    {DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT, DIO_PIN_LOW}, // Pin 1
	    {DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT, DIO_PIN_LOW}, // Pin 2
	    {DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT, DIO_PIN_LOW}  // Pin 4
	};

	// Set the common configuration for the display pins
	for (u8 i = 0; i < 4; i++) {
	    // Set the pin value based on the number (num)
	    u8 pinValue = (num & (1 << i)) ? DIO_PIN_HIGH : DIO_PIN_LOW;

	    // Set the pin value for each digit based on the binary representation
	    displayPins[i].value = pinValue;
	    DIO_U8SetPinValue(&displayPins[i]);
	}


}

