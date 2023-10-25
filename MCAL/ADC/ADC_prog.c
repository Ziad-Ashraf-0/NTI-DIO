/*
 * ADC_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: zashr
 */
#include "ADC_interface.h"
#include "ADC_private.h"
#include "../../LIB/HW_REG.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>


void (*ADC_callBack)(u16 value) = NULL; // Function pointer for ADC interrupt callback

// Function to initialize the ADC module with the given configuration
void ADC_Init(const ADC_config *config) {
    /* ADMUX Register Bits Description: */

    // Clear the ADMUX register
    ADC_BASE->ADMUX = 0;

    // Clear the ADEN bit in ADCSRA to disable the ADC
    CLR_BIT(ADC_BASE->ADCSRA, ADEN);

    // Configure ADMUX with reference selection, adjustment, and channel
    ADC_BASE->ADMUX = (config->ref << 6) | (config->adj << 5) | (config->channel);

    // Configure SFIOR with special control options
    ADC_BASE->SFIOR = config->sfiorControl;

    /* ADCSRA Register Bits Description:
     * ADEN = 1 Enable ADC
     */
    ADC_BASE->ADCSRA = (1 << ADEN) | config->adcsraPre;
}

// Function to initiate an asynchronous ADC conversion with a callback function
void ADC_getDigitalValueAsynchCallBack(u8 channel_num, void (*localPtr)(u16 value)) {
    // ADIE = 1 Enable ADC interrupt
    SET_BIT(ADC_BASE->ADCSRA, ADIE);

    // Set the callback function
    ADC_callBack = localPtr;

    channel_num &= 0x07; // Input channel number must be from 0 to 7

    // Clear the first 5 bits in ADMUX (channel number MUX4:0 bits) before setting the required channel
    ADC_BASE->ADMUX &= 0xE0;

    // Choose the correct channel by setting the channel number in MUX4:0 bits
    ADC_BASE->ADMUX = ADC_BASE->ADMUX | channel_num;

    // Start conversion by writing '1' to ADSC
    SET_BIT(ADC_BASE->ADCSRA, ADSC);
}

// Function to perform a synchronous non-blocking ADC conversion
u16 ADC_getDigitalValueSynchNonBlocking(u8 channel_num) {
    static u8 flag = 0;
    u8 time_out = 50;
    u16 value;

    channel_num &= 0x07; // Input channel number must be from 0 to 7

    // Clear the first 5 bits in ADMUX (channel number MUX4:0 bits) before setting the required channel
    ADC_BASE->ADMUX &= 0xE0;

    // Choose the correct channel by setting the channel number in MUX4:0 bits
    ADC_BASE->ADMUX = ADC_BASE->ADMUX | channel_num;

    // Start Conversion if flag is zero
    if (!flag) {
        flag = 1;
        SET_BIT(ADC_BASE->ADCSRA, ADSC);
    }

    // Poll the ADC until the value is ready
    while (GET_BIT(ADC_BASE->ADCSRA, ADIF) == LOW_VAL) {
        _delay_ms(1);
        if (time_out == 0) {
            break;
        }
        time_out--;
    }

    // Clear the Interrupt Flag Manually
    SET_BIT(ADC_BASE->ADCSRA, ADIF);

    value = ADC_BASE->ADCL;
    value = (value >> 6) | (ADC_BASE->ADCH << 2);

    flag = 0;
    return value;
}

// ADC Interrupt Service Routine
void __vector_16(void) {
    /* Read ADC Data after conversion complete */
	u16 adcResult;
    adcResult = ADC_BASE->ADCL;
    adcResult = (adcResult >> 6) | (ADC_BASE->ADCH << 2);
    ADC_callBack(adcResult); // Call the user-defined callback function
}
