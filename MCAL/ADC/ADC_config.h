/*
 * ADC_config.h
 *
 *  Created on: Oct 23, 2023
 *      Author: zashr
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/************ ADMUX *************/
/* Voltage Reference Bits --- Bit6 : REFS0 --- Bit7 : REFS1 */
/* R*/
#define REFS1_VAL LOW_VAL
#define REFS0_VAL HIGH_VAL
/* Left Or Right Adjustment of Data Registers */
#define ADLAR_VAL HIGH_VAL
/* Channel Selection */

#define MUX4_VAL LOW_VAL
#define MUX3_VAL LOW_VAL
#define MUX2_VAL LOW_VAL
#define MUX1_VAL LOW_VAL
#define MUX0_VAL LOW_VAL

/************ ADCSRA *************/
/* Bits 2:0 ---- Pre Scalar Bits */
#define ADPS2_VAL LOW_VAL
#define ADPS1_VAL LOW_VAL
#define ADPS0_VAL LOW_VAL

/************ SFIOR *************/
/* • Bit 7:5 – ADTS2:0: ADC Auto Trigger Source */
#define ADTS2_VAL LOW_VAL
#define ADTS1_VAL LOW_VAL
#define ADTS0_VAL LOW_VAL


#endif /* MCAL_ADC_ADC_CONFIG_H_ */
