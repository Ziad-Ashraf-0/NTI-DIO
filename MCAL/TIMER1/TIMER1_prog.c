/*
* TIMER1_prog.c
*
* Created: 10/28/2023 12:09:04 PM
*  Author: Ziad
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER1_config.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"


//global -> number of overflows=0 , remaing counts =0
static u32 numOverflows = 0;
static u32 remainingCounts = 0;
static Timer1_Prescaler prescaler = 0;



// Array of two pointers to functions
static void (*Action_Timer[4])(void) = {NULL, NULL, NULL, NULL};

void M_TIMER1_void_Init(const Timer1_Config* config){
	prescaler = config->prescaler;
	
	if(config->mode == Timer1_NORMAL){
		/* Configure the timer control register
		* 1. Non PWM mode FOC1A=1 & FOCA1B=1
		* 2. Normal Mode WGM13=0 & WGM12=0 & WGM11=0 & WGM10=0
		* 3. Normal Mode COM1A1=0 & COM1A0=0 & COM1B1=0 & COM1B0=0
		*/
		TIMER1_BASE->TCCR1A = (1<<FOC1A_BIT) | (1<<FOC1B_BIT);
		}
	
}


void M_TIMER1_void_start(void){
	
	TIMER1_BASE-> TCCR1B &= TIMER1_PRESCALER_MASK;
	TIMER1_BASE-> TCCR1B |= prescaler;
}

void M_TIMER1_void_IntEnable(Timer1_IntID copy_u8IntID){
	if(copy_u8IntID == TIMER1_OVERFLOW){
		TIMER1_BASE->TIMSK |= (1<<TOIE1_BIT); // Enable Timer1 Overflow Interrupt
	}
}


void M_TIMER1_void_setDelayTimeMilliSec(u32 copy_u32TimeMS){
	// Create an array to map prescaler values to their numbers
	const u16 prescalerMap[] = {
		0,		// 0 is not used
		1,		//TIMER1_PRESCALER_1
		8,		//TIMER1_PRESCALER_8
		64,		//TIMER1_PRESCALER_64
		256,	//TIMER1_PRESCALER_256
		1024,	//TIMER1_PRESCALER_1024
	};

	u32 tickTime = prescalerMap[prescaler] / FCPU;
	u32 totalCounts = (copy_u32TimeMS * 1000) / tickTime;
	
	// Calculate the number of overflows required
	numOverflows = totalCounts / 65536;
	// Calculate the remaining counts
	remainingCounts = totalCounts % 65536;

}

void M_TIMER1_void_setCallBack(void (*ptrfn)(void),Timer1_IntID copy_u8IntID){
	if(copy_u8IntID == TIMER1_OVERFLOW){
		Action_Timer[0] = ptrfn;
	}
}


ISR(TIMER1_OVF_vect){
	static u32 counter = 0;
	if(Action_Timer[0]!= NULL){
		
		counter++;
		if(counter == numOverflows){
			//TIMER1_BASE-> = 256 - remainingCounts;
			counter = 0;
			Action_Timer[0]();
		}
		
	}
}