/*
 * TIMER0_interface.h
 *
 * Created: 10/26/2023 2:19:17 PM
 *  Author: zashr
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#define FCPU 16

#if (FCPU == 16)

typedef enum{
	FREQ_625000_HZ	=	1,
	FREQ_7812_HZ	=	2,
	FREQ_976_HZ		=	3,
	FREQ_244_HZ		=	4,
	FREQ_61_HZ		=	5
}Valid_Freq;

#endif

typedef enum
{
	OVERFLOW,
	COMPARE
}IntID;

typedef enum
{
	NORMAL = 0,
	CTC = 2,
	FAST_PWM = 3,
	PHASE_CORRECT_PWM = 1,	
}Mode;

typedef enum
{
	NO_CLK,
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXT_CLK_FALL_EDGE,
	EXT_CLK_RAIS_EDGE,

}Prescaler;

typedef enum{
	OC0_DISCONNECTED = 0,
	OC0_SET = 3,
	OC0_CLR = 2,
	OC0_TOGGLE = 1,		
}Oc0;


/*************************************************************************************/
/* TIMER0 Configuration Structure */
/*************************************************************************************/
typedef struct {
	Mode mode;
	Prescaler prescaler;
	Oc0 oc0;
	u8 ocr0;
} Timer0_Config;


void M_TIMER0_void_Init(const Timer0_Config* config);
void M_TIMER0_void_start(void);
void M_TIMER0_void_stop(void);
void M_TIMER0_void_setDelayTimeMilliSec(u32 copy_u32TimeMS);
void M_TIMER0_void_IntEnable(u8 copy_u8IntID); // id overflow or compare match
void M_TIMER0_void_IntDisable(u8 copy_u8IntID);
void M_TIMER0_void_setCallBack(void (*ptrfn)(void),u8 copy_u8IntID);
void M_TIMER0_void_setFastPWM(Valid_Freq freq, u8 duty);
void M_TIMER0_void_setPhaseCorrectPWM(Valid_Freq freq, u8 duty);




#endif /* TIMER0_INTERFACE_H_ */