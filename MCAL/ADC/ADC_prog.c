/*
 * ADC_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: zashr
 */
#include "ADC_interface.h"
#include "../../LIB/HW_REG.h"
#include "../../LIB/BIT_MATH.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile u16 g_adcResult = 0;


void ADC_Init(const ADC_config *config){
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADC_BASE->ADMUX = 0;
	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADC_BASE->ADCSRA = (1<<ADEN) | (1<<ADIE) | Prescaler_8;
}


u8 ADC_getDigitalValueAsynchCallBack(u8 channel_num){
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADC_BASE->ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADC_BASE->ADMUX = ADC_BASE->ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADC_BASE->ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	return 0;
}


void __vector_14 (void)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC_BASE->ADCH;
}
