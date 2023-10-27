/*
* TIMER0_prog.c
*
* Created: 10/26/2023 2:18:58 PM
*  Author: zashr
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"


//global -> number of overflows=0 , remaing counts =0
u32 numOverflows = 0;
u32 remainingCounts = 0;

// Array of three pointers to functions
void (*Action_Timer[2])(void) = {NULL, NULL};


// mode and oc0 pin mode
void M_TIMER0_void_Init(const Timer0_Config* config){
	
	if(config->mode == TIMER0_MODE_NORMAL){
		/* Configure the timer control register
		* 1. Non PWM mode FOC0=1
		* 2. Normal Mode WGM01=0 & WGM00=0
		* 3. Normal Mode COM00=0 & COM01=0
		*/
		TCCR0_REG = (1<<FOC_BIT);
		}else if(config->mode == TIMER0_MODE_CTC){
		/* Configure the timer control register
		* 1. Non PWM mode FOC0=1
		* 2. CTC Mode WGM01=1 & WGM00=0
		* 3. Set COM00 & COM01
		* 4. set OCR0 value (compare value)
		*/
		OCR0_REG = config->ocr0;
		TCCR0_REG = (1<<FOC_BIT) | (1<< WGM01_BIT) | (config->oc0 << 4);
		}else if(config->mode == TIMER0_MODE_FAST_PWM){
		/* Configure timer control register
		* 1. Fast PWM mode FOC0=0
		* 2. Fast PWM Mode WGM01=1 & WGM00=1
		* 3. Select OC0 mode throw COM00 & COM01
		*/
		TCCR0_REG = (1<<WGM01_BIT) | (1<<WGM00_BIT) | (config->oc0 << 4);
		}else if(config->mode == TIMER0_MODE_PHASE_CORRECT_PWM){
		/* Configure the timer control register
		* 1. PWM mode FOC0=0
		* 2. Phase PWM Mode WGM01=0 & WGM00=1
		* 3. Select OC0 mode throw COM00 & COM01
		*/
		TCCR0_REG = (1<<WGM00_BIT) | (config->oc0 << 4);
	}
}

void M_TIMER0_void_start(const Timer0_Config* config){
	
	TCCR0_REG &= TIMER0_PRESCALER_MASK;
	TCCR0_REG |= config->prescaler;
}


void M_TIMER0_void_stop(void){
	
	TCCR0_REG &= TIMER0_PRESCALER_MASK;
	
}

void M_TIMER0_void_setDelayTimeMilliSec(u32 copy_u32TimeMS){
	// Create an array to map prescaler values to their numbers
	const u16 prescalerMap[] = {
		0,		// 0 is not used
		1,		//TIMER0_PRESCALER_1
		8,		//TIMER0_PRESCALER_8
		64,		//TIMER0_PRESCALER_64
		256,	//TIMER0_PRESCALER_256
		1024,	//TIMER0_PRESCALER_1024
	};

	u32 tickTime = prescalerMap[TIMER0_PRESCALER] / FCPU;
	u32 totalCounts = (copy_u32TimeMS * 1000) / tickTime;
	
	// Calculate the number of overflows required
	numOverflows = totalCounts / 256;
	// Calculate the remaining counts
	remainingCounts = totalCounts % 256;

}


void M_TIMER0_void_IntEnable(u8 copy_u8IntID){
	if(copy_u8IntID == OVERFLOW){
		TIMSK_REG |= (1<<TOIE0_BIT); // Enable Timer0 Overflow Interrupt
		}else if(copy_u8IntID == COMPARE){
		TIMSK_REG |= (1<<OCIE0_BIT); // Enable Timer0 Compare Interrupt
	}
}

void M_TIMER0_void_IntDisable(u8 copy_u8IntID){
	if(copy_u8IntID == OVERFLOW){
		CLR_BIT(TIMSK_REG,TOIE0_BIT); // Disable Timer0 Overflow Interrupt
		}else if(copy_u8IntID == COMPARE){
		CLR_BIT(TIMSK_REG,OCIE0_BIT); // Disable Timer0 Compare Interrupt
	}
}


void M_TIMER0_void_setCallBack(void (*ptrfn)(void),u8 copy_u8IntID){
	if(copy_u8IntID == OVERFLOW){
		Action_Timer[0] = ptrfn;
		}else if(copy_u8IntID == COMPARE){
		Action_Timer[1] = ptrfn;
	}
}

/*
ISR(OVR)
global -> number of overflows=0 , remaing counts =0
static counter = 0;
counter++
if counter == number of overflows
TCNT = 256 - remaining counts
counter = 0
call back();
*/

ISR(TIMER0_OVF_vect){
	static u32 counter = 0;
	if(Action_Timer[0]!= NULL){
		counter++;
		if(counter == numOverflows){
			TCNT0_REG = 256 - remainingCounts;
			counter = 0;
			Action_Timer[0]();
		}
		
	}
}

ISR(TIMER0_COMP_vect){

	if(Action_Timer[1]!= NULL){
		Action_Timer[1]();
		
	}
}
