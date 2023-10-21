/*
 * DIO_Program.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Ziad
 */


/* 		LIB LAYER 		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"

/* 		MCAL LAYER 		*/
#include "DIO_Private.h"
#include "DIO_Interface.h"

/* Arrays of pointers that point to the three DIO registers */
u8* const directionRegisters [NUMBER_OF_PORTS] = {DDRA_REGISTER, DDRB_REGISTER, DDRC_REGISTER, DDRD_REGISTER};
u8* const writeRegisters [NUMBER_OF_PORTS] = {PORTA_REGISTER, PORTB_REGISTER, PORTC_REGISTER, PORTD_REGISTER};
volatile u8* const readRegisters [NUMBER_OF_PORTS] = {PINA_REGISTER, PINB_REGISTER, PINC_REGISTER, PIND_REGISTER};


/***********************************************************************************/
/* 							PUBLIC FUNCTIONS IMPLEMENTATION						   */
/***********************************************************************************/

u8 DIO_U8SetPortDirection (const DIO_Config* config)
{
	if (config->port <= DIO_PORTD)
	{
		if (config->pin == DIO_PORT_INPUT)
		{
			*directionRegisters[config->port] = DIO_PORT_INPUT;
			return NO_ERROR;
		}
		else if (config->pin == DIO_PORT_OUTPUT)
		{
			*directionRegisters[config->port] = DIO_PORT_OUTPUT;
			return NO_ERROR;
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8SetPinDirection (const DIO_Config* config)
{
	if (config->port <= DIO_PORTD && config->pin <= DIO_PIN7)
	{
		if (config->direction == DIO_PIN_INPUT)
		{
			CLR_BIT( *directionRegisters[config->port], config->pin );
			return NO_ERROR;
		}
		else if (config->direction == DIO_PIN_OUTPUT)
		{
			SET_BIT( *directionRegisters[config->port], config->pin );
			return NO_ERROR;
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8SetPortValue(const DIO_Config* config) {
    if (config != NULL) {
        if (config->port <= DIO_PORTD) {
            *writeRegisters[config->port] = config->value;
            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR;
    }
}

u8 DIO_U8SetPinValue(const DIO_Config* config) {
    if (config != NULL) {
        if (config->port <= DIO_PORTD && config->pin <= DIO_PIN7) {
            if (config->value == DIO_PIN_HIGH) {
                SET_BIT(*writeRegisters[config->port], config->pin);
                return NO_ERROR;
            } else if (config->value == DIO_PIN_LOW) {
                CLR_BIT(*writeRegisters[config->port], config->pin);
                return NO_ERROR;
            } else {
                return ERROR;
            }
        } else {
            return ERROR;
        }
    } else {
        return ERROR;
    }
}

u8 DIO_U8TogglePin(const DIO_Config* config) {
    if (config != NULL) {
        if (config->port <= DIO_PORTD && config->pin <= DIO_PIN7) {
            TOG_BIT(*writeRegisters[config->port], config->pin);
            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR;
    }
}

u8 DIO_U8TogglePort(DIO_Port port) {
    if (port <= DIO_PORTD) {
        *writeRegisters[port] = ~(*writeRegisters[port]);
        return NO_ERROR;
    } else {
        return ERROR;
    }
}

u8 DIO_U8GetPinValue(const DIO_Config* config, u8* value) {
    if (config != NULL && value != NULL) {
        if (config->port <= DIO_PORTD && config->pin <= DIO_PIN7) {
            *value = GET_BIT(*readRegisters[config->port], config->pin);
            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR;
    }
}

u8 DIO_U8GetPortValue(DIO_Port port, u8* value) {
    if (value != NULL) {
        if (port <= DIO_PORTD) {
            *value = *readRegisters[port];
            return NO_ERROR;
        } else {
            return ERROR;
        }
    } else {
        return ERROR;
    }
}
