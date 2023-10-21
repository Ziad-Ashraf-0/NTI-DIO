/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad Ashraf
 */

#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include <util/delay.h>

int main (void)
{
	DIO_U8SetPinDirection(DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT);
	segment_Init();
	segment_Num(5,4);

	while (1)
	{
		DIO_U8SetPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_HIGH);
		_delay_ms(2000);
		DIO_U8SetPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_LOW);
		_delay_ms(2000);
	}

	return 0;
}
