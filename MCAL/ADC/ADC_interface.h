/*
 * ADC_interface.h
 *
 *  Created on: Oct 23, 2023
 *      Author: zashr
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"


/************ ADMUX *************/

enum ADMUXRef {
    AFREF = 0,
    AVCC = 1,
    Internal = 3,
};

enum ADMUXAdj {
	LeftAdj = 1,
	RightAdj = 0,
};

enum ADMUXChannel {
	SingleADC0 = 0,
	SingleADC1 = 1,
	SingleADC2 = 2,
	SingleADC3 = 3,
	SingleADC4 = 4,
	SingleADC5 = 5,
	SingleADC6 = 6,
	SingleADC7 = 7,
	PosADC0_10x = 8,
	PosADC1_10x = 9,
	//To Be Continued .... :)
};

/************ ADCSRA *************/
enum ADCSRAControlBits {
    ADEN  = 7,
    ADSC  = 6,
    ADATE = 5,
    ADIF  = 4,
    ADIE  = 3,
};

enum ADCSRAPre{
	Prescaler_2 = 0,
	Prescaler_4 = 2,
	Prescaler_8 = 3,
	Prescaler_16 = 4,
	Prescaler_32 = 5,
	Prescaler_64 = 6,
	Prescaler_128 = 7,
};

/************ SFIOR *************/

enum SFIORControlBits {
	Free = 0,
	Analog,
	ExtInt0,
	Timer0Comp,
	Timer0Ovr,
	Timer1Comp,
	Timer1Ovr,
	TImer1Cap,
};




/* This enum is for function validation, holds the possible states of the ADC */
enum ADC_enuState {
    ADC_enuNormalState= 0,
    ADC_enuNullPointerException,
}ADC_enuState;


// Struct that holds all the enums
typedef struct{
    enum ADMUXRef ref;
    enum ADMUXAdj adj;
    enum ADMUXChannel channel;
    enum ADCSRAPre adcsraPre;
    enum SFIORControlBits sfiorControl;
}ADC_config;



/* Initalization Method*/
void ADC_Init(const ADC_config *config);

/*Polling the ADC,
The Function returns 0 "ADC_enuNormalState" when the ADC is ready for the user
and the ADC is functioning in normal state.
Otherwise, returns any other state type from the ADC_enuState enum */
void ADC_getDigitalValueAsynchCallBack(u8 channel_num,void (*localPtr)(u16 value));

/* Get ADC value, This Functions returns the value converted by the ADC ( directly from ADCH ) */
u16 ADC_getDigitalValueSynchNonBlocking (u8 channel_num);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
