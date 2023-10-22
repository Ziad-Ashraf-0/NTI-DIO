/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad Ashraf
 */

#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include "../HAL/Keypad/keypad.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


void testCallback(void){
	DIO_Config pinTest;
	pinTest.port= DIO_PORTA;
	pinTest.direction= DIO_PIN_OUTPUT;
	pinTest.pin= DIO_PIN6;
	pinTest.value= DIO_PIN_HIGH;
	DIO_U8SetPinDirection(&pinTest);
	DIO_U8SetPinValue(&pinTest);
}

int main(void) {
	DIO_Config pinTest;
	pinTest.port= DIO_PORTD;
	pinTest.direction= DIO_PIN_INPUT;
	pinTest.pin= DIO_PIN3;
	DIO_U8SetPinDirection(&pinTest);
	// Enable global interrupts
	sei();
	EXTI_enable(EXTI_INT1_ID,FALLING_EDGE);
	EXTI_setCallBack(EXTI_INT1_ID,testCallback);
    // Initialize the 7-segment display
    //segment_Init();
    //u8 key;

    //test external inturrpet on PD3 INT1

    while (1) {

       // key = KEYPAD_getPressedKey();
       //segment_Num(key,4);
       // _delay_ms(2000);

    }

    return 0;
}

