/*
* WDT_prog.c
*
* Created: 11/5/2023 9:41:57 AM
*  Author: Ziad
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "WDT_config.h"
#include "WDT_interface.h"
#include "WDT_private.h"

// Enable Watch Dog Timer: Start counting till timeout (reset MCU)
void M_WDT_void_Enable(void)
{
	SET_BIT(WDTCR, WDE);
}


void M_WDT_void_Disable(void)
{
	
	/* Write logical one to WDTOE and WDE */
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
}

// WDT Pre-scaler Select: Each pre-scaler maps to a specific timeout value (sleep time).
// Input argument from 1 : 7 (each value maps to a specific timeout value (sleep time).
void M_WDT_void_Sleep(WDT_timeout copy_u8SleepTime)
{
	// Bit masking Sequence:
	// 1. clear the desired bits
	// 2. Put the required value in it
	WDTCR &= Prescaler_Mask;
	WDTCR |= copy_u8SleepTime;
}


void M_WDT_void_refresh(){
	 __asm__ __volatile__ ("wdr"); // Reset the Watchdog Timer
}