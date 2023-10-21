/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad Ashraf
 */

#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include <util/delay.h>

int main(void) {
    // Initialize DIO pins
    DIO_Config ledPin;
    ledPin.port = DIO_PORTA;
    ledPin.pin = DIO_PIN6;
    ledPin.direction = DIO_PIN_OUTPUT;
    ledPin.value = DIO_PIN_LOW;

    // Configure and set the LED pin
    DIO_U8SetPinDirection(&ledPin);

    // Initialize the 7-segment display
    segment_Init();

    while (1) {
        // Display the number 5 on the 7-segment display
        segment_Num(5, 4);

        // Turn on the LED
        ledPin.value = DIO_PIN_HIGH;
        DIO_U8SetPinValue(&ledPin);
        _delay_ms(2000);

        // Turn off the LED
        ledPin.value = DIO_PIN_LOW;
        DIO_U8SetPinValue(&ledPin);
        _delay_ms(2000);
    }

    return 0;
}

