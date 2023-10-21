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
    for (u8 i = 0; i < sizeof(segmentPins) / sizeof(segmentPins[0]); i++) {
        DIO_U8SetPinDirection(&segmentPins[i]);
        DIO_U8SetPinValue(&segmentPins[i]);
    }
}

void segment_Num(u8 num, u8 segmentNum) {
    // First, clear the relevant pins to 0
    DIO_Config clearPins[] = {
        {DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
        {DIO_PORTA, DIO_PIN3, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
        {DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
        {DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT, DIO_PIN_HIGH}
    };

    for (u8 i = 0; i < sizeof(clearPins) / sizeof(clearPins[0]); i++) {
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

    DIO_Config displayPin;

    // Set the common configuration for the display pin
    displayPin.port = DIO_PORTB;
    displayPin.direction = DIO_PIN_OUTPUT;

    // Now, set pins PB0, PB1, PB2, and PB4 to display the number
    for (u8 i = 0; i < 4; i++) {
        displayPin.pin = i;
        // Set the pin value based on the number (num)
        u8 pinValue = (num & (1 << i)) ? DIO_PIN_HIGH : DIO_PIN_LOW;

        // Call the function with the configured pin and its value
        displayPin.value = pinValue;
        DIO_U8SetPinValue(&displayPin);
    }


}

