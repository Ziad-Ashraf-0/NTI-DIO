/*
 * TIMER0_private.h
 *
 * Created: 10/26/2023 2:19:38 PM
 *  Author: zashr
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define TCCR0_REG	(*((u8*)0x53))
#define TCNT0_REG	(*((u8*)0x52))
#define OCR0_REG	(*((u8*)0x5C))
#define TIMSK_REG	(*((u8*)0x59))
#define TIFR_REG	(*((u8*)0x58))


//TCCR0_REG
#define FOC_BIT		7
#define WGM00_BIT	6
#define COM01_BIT	5
#define COM00_BIT	4
#define WGM01_BIT	3
#define CS02_BIT	2
#define CS01_BIT	1
#define CS00_BIT	0

//TIMSK_REG

#define OCIE0_BIT	1 //compare match IE
#define TOIE0_BIT	0 //overflow IE

#define TIMER0_NO_CLK				0
#define	TIMER0_PRESCALER_1			1
#define	TIMER0_PRESCALER_8			2
#define	TIMER0_PRESCALER_64			3	
#define	TIMER0_PRESCALER_256		4
#define	TIMER0_PRESCALER_1024		5
#define	TIMER0_EXT_CLK_FALL_EDGE	6
#define	TIMER0_EXT_CLK_RAIS_EDGE	7


#define TIMER0_PRESCALER_MASK	0xF8


#endif /* TIMER0_PRIVATE_H_ */