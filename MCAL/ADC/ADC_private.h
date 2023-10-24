/*
 * ADC_private.h
 *
 *  Created on: Oct 23, 2023
 *      Author: zashr
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal)) __VA_ARGS__; \
    void vector (void)

/* ADC Conversion Complete */
#define ADC_vect			_VECTOR(14)
#define SIG_ADC				_VECTOR(14)

#define LOW_VAL 0
#define HIGH_VAL 1
#define NULL (void *)0x00



#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
