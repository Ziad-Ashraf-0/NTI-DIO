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


//#define TCNT1   _SFR_IO16(0x2C)
//#define OCR1A   _SFR_IO16(0x2A)
//#define OCR1B   _SFR_IO16(0x28)
//#define ICR1    _SFR_IO16(0x26)

//global -> number of overflows=0 , remaing counts =0
static u32 req_numOverflows = 0;
static u32 remainingCounts = 0;
static Timer1_Prescaler prescaler = 0;

static u32 numOverflows = 0;
static u8 g_edgeCount = 0;
static u16 g_timeHigh = 0;
static u16 g_timePeriod = 0;
static u16 g_timePeriodPlusHigh = 0;



// Array of two pointers to functions
static void (*Action_Timer[4])(void) = {NULL, NULL, NULL, NULL};

void M_TIMER1_void_Init(const Timer1_Config* config) {
	prescaler = config->prescaler;

	switch (config->mode) {
		case Timer1_NORMAL:
		/* Configure the timer control register
		* 1. Non PWM mode FOC1A=1 & FOCA1B=1
		* 2. Normal Mode WGM13=0 & WGM12=0 & WGM11=0 & WGM10=0
		* 3. Normal Mode COM1A1=0 & COM1A0=0 & COM1B1=0 & COM1B0=0
		*/
		TIMER1_BASE->TCCR1A = (1 << FOC1A_BIT) | (1 << FOC1B_BIT);
		
		break;
		case  FAST_PWM_OCR1A:
		/* Configure the timer control register
		* 1. PWM mode FOC1A=0 & FOCA1B=0
		* 2. Fast PWM OCR1A Mode WGM13=1 & WGM12=1 & WGM11=1 & WGM10=1
		* 3. config COM1A1 & COM1A0 & COM1B1 & COM1B0
		*/
		TIMER1_BASE->TCCR1A = (config->oc1 << 6) | (config->oc1 << 4) | (1 << WGM11_BIT) | (1<<WGM10_BIT);
		TIMER1_BASE->TCCR1B = (1 << WGM12_BIT) | (1 << WGM13_BIT);
		default:
		// Handle any invalid or unsupported mode here
		break;
	}
}



void M_TIMER1_void_start(void){
	
	TIMER1_BASE-> TCCR1B &= TIMER1_PRESCALER_MASK;
	TIMER1_BASE-> TCCR1B |= prescaler;
}

void M_TIMER1_void_IntEnable(Timer1_IntID copy_u8IntID){
	if(copy_u8IntID == TIMER1_OVERFLOW){
		TIMER1_BASE->TIMSK |= (1<<TOIE1_BIT);	   // Enable Timer1 Overflow Interrupt
		}else if(copy_u8IntID == TIMER1_COMPARE_A){
		TIMER1_BASE->TIMSK |= ( 1 << OCIE1A_BIT ); // Enable Timer1 Compare A Interrupt
		}else if(copy_u8IntID == TIMER1_ICU){
		TIMER1_BASE->TIMSK |= ( 1 << TICIE1_BIT ); // Enable Timer1 ICU Interrupt
	}
}


void M_TIMER1_void_setFastPWM(TIMER1_Valid_Freq freq, u8 duty){
	u16 ocr1_value = (duty * 65536) / 100 ;
	TIMER1_BASE->OCR1AL = ocr1_value;
	TIMER1_BASE->OCR1AH = ocr1_value >> 8;
	
	TIMER1_BASE-> TCCR1B &= TIMER1_PRESCALER_MASK;
	//are they constants??
	TIMER1_BASE-> TCCR1B |= freq;
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
	req_numOverflows = totalCounts / 65536;
	// Calculate the remaining counts
	remainingCounts = totalCounts % 65536;

}

void M_TIMER1_void_setCallBack(void (*ptrfn)(void),Timer1_IntID copy_u8IntID){
	if(copy_u8IntID == TIMER1_OVERFLOW){
		Action_Timer[0] = ptrfn;
		}else if(copy_u8IntID == TIMER1_COMPARE_A){
		Action_Timer[1] = ptrfn;
		}else if(copy_u8IntID == TIMER1_ICU){
		Action_Timer[3] = ptrfn;
	}
}

u16 M_TIMER1_void_getInputCaptureValue(void){
	return TIMER1_BASE->ICR1;
}

void M_TIMER1_void_setEdgeDetectionType(const Icu_EdgeType a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TIMER1_BASE-> TCCR1B = (TIMER1_BASE-> TCCR1B & 0xBF) | (a_edgeType << 6);
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void M_TIMER1_void_clearTimerValue(void)
{
	TIMER1_BASE->TCNT1 = 0;
}

u32 M_TIMER1_void_measureDutyCycle(void){
	u32 dutyCycle = 0;
	/*
	* insert the required clock value in the first three bits (CS10, CS11 and CS12)
	* of TCCR1B Register
	*/
	TIMER1_BASE-> TCCR1B &= TIMER1_PRESCALER_MASK;
	TIMER1_BASE-> TCCR1B |= prescaler;
	/*
	* insert Rising EDGE at beginning
	*/
	TIMER1_BASE-> TCCR1B = (TIMER1_BASE-> TCCR1B & 0xBF) | (RISING << 6);
	/* Initial Value for Timer1 */
	TIMER1_BASE->TCNT1 = 0;
	/* Initial Value for the input capture register */
	TIMER1_BASE->ICR1 = 0;
	
	while(g_edgeCount < 5);
	
	dutyCycle = ((float)(g_timePeriodPlusHigh-g_timePeriod) / (g_timePeriodPlusHigh - g_timeHigh)) * 100;

	
	return dutyCycle;
	
}

u32 M_TIMER1_void_freq(void){
	u32 freq = 0;
	/*
	* insert the required clock value in the first three bits (CS10, CS11 and CS12)
	* of TCCR1B Register
	*/
	TIMER1_BASE-> TCCR1B &= TIMER1_PRESCALER_MASK;
	TIMER1_BASE-> TCCR1B |= prescaler;
	/*
	* insert Rising EDGE at beginning
	*/
	TIMER1_BASE-> TCCR1B = (TIMER1_BASE-> TCCR1B & 0xBF) | (RISING << 6);
	/* Initial Value for Timer1 */
	TIMER1_BASE->TCNT1 = 0;
	/* Initial Value for the input capture register */
	TIMER1_BASE->ICR1 = 0;
	
	while(g_edgeCount < 5);
	
	const u16 prescalerMap[] = {
		0,		// 0 is not used
		1,		//TIMER1_PRESCALER_1
		8,		//TIMER1_PRESCALER_8
		64,		//TIMER1_PRESCALER_64
		256,	//TIMER1_PRESCALER_256
		1024,	//TIMER1_PRESCALER_1024
	};

	u32 tickTime = prescalerMap[prescaler] / FCPU;
	
	freq = g_timePeriod * tickTime;
	return freq;
}

ISR(TIMER1_OVF_vect){
	Action_Timer[0]();
	numOverflows++;
	static u32 counter = 0;
	if(Action_Timer[0]!= NULL){
		counter++;
		if(counter == req_numOverflows){
			//TIMER1_BASE-> = 256 - remainingCounts;
			counter = 0;
			Action_Timer[0]();
		}
		
	}
}

ISR(TIMER1_COMPA_vect){
	if(Action_Timer[1]!= NULL){
		Action_Timer[1]();
	}
}


ISR(TIMER1_CAPT_vect){
		if(Action_Timer[3]!= NULL){
			Action_Timer[3]();
			
			
		}
}