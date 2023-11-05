/*
 * WDT_private.h
 *
 * Created: 11/5/2023 9:42:26 AM
 *  Author: Ziad
 */ 


#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_


// Watch dog Timer Control Register – WDTCR
#define WDTCR		*((volatile u8*)0x41)
#define WDTOE		4
#define WDE			3
#define WDP2		2
#define WDP1		1
#define WDP0		0

#define Prescaler_Mask 0xF8


#endif /* WDT_PRIVATE_H_ */