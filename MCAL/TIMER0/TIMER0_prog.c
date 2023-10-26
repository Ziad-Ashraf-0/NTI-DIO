/*
 * TIMER0_prog.c
 *
 * Created: 10/26/2023 2:18:58 PM
 *  Author: zashr
 */ 
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"



// mode and oc0 pin mode
void M_TIMER0_void_Init(void){
	
}

//prescaler 
void M_TIMER0_void_start(void){
	
	TCCR0_REG &= TIMER0_PRESCALER_MASK;
	TCCR0_REG |= TIMER0_PRESCALER;
}


void M_TIMER0_void_setDelayTimeMilliSec(u32 copy_u32TimeMS){
	/*	number or req count ?
		number of overflow?
		tck time = prescaler / FCPU     1->1  2->8 3->64 
		define fcpu ->16
		total counts = delaytime / tick time   -> kam count     delaytime *1000
		num of overflows = totalcount /256
		remaining counts = totalcount % 256
	*/	
	#if(TIMER0_MODE == TIMER0_MODE_NORMAL)
	
	#elif(TIMER0_MODE == TIMER0_MODE_CTC)
}


/*
ISR(OVR)
global -> number of overflows=0  , remaing counts =0



*/