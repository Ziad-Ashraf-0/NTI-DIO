/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad Ashraf
 */

#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include "../HAL/Keypad/keypad.h"
#include <util/delay.h>

int main(void) {

    // Initialize the 7-segment display
    segment_Init();

    u8 key;

    while (1) {

        key = KEYPAD_getPressedKey();
        segment_Num(key,4);
        _delay_ms(2000);

    }

    return 0;
}

