/*
 * HW_REG.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Ziad
 */

#ifndef LIB_HW_REG_H_
#define LIB_HW_REG_H_

/*************************************************************************************/
/* 								ADC REGISTERS										 */
/*************************************************************************************/

typedef struct {
	u8 ADCL;
	u8 ADCH;
	u8 ADCSRA;
	u8 ADMUX;
	u8 padding[40];
	u8 SFIOR;
}ADC_Type;

#define ADC_BASE ((volatile ADC_Type *) 0x24)
/*************************************************************************************/
/* 								EXTI REGISTERS										 */
/*************************************************************************************/
typedef struct {
	u8 MCUCSR;
	u8 MCUCR;
	u8 padding[5];
	u8 GICR;
}EXTI_Type;

#define EXTI_BASE ((volatile EXTI_Type *) 0x54)


void __vector_1 (void) __attribute__ ((signal,used, externally_visible));
void __vector_2 (void) __attribute__ ((signal,used, externally_visible));
void __vector_18 (void) __attribute__ ((signal,used, externally_visible));


#endif /* LIB_HW_REG_H_ */
