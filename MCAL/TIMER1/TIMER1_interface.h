/*
 * TIMER1_interface.h
 *
 * Created: 10/28/2023 12:09:42 PM
 *  Author: Ziad
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#define FCPU 16

#if (FCPU == 16)

//typedef enum{
//	FREQ_625000_HZ	=	1,
//	FREQ_7812_HZ	=	2,
//	FREQ_976_HZ		=	3,
//	FREQ_244_HZ		=	4,
//	FREQ_61_HZ		=	5
//}Valid_Freq;

#endif

typedef enum
{
	TIMER1_OVERFLOW,
	TIMER1_COMPARE
}Timer1_IntID;

typedef enum
{
	Timer1_NORMAL = 0,
	PWM_PHASE_CORRECT_8_BIT,
	PWM_PHASE_CORRECT_9_BIT,
	PWM_PHASE_CORRECT_10_BIT,
	CTC_OCR1A,
	FAST_PWM_8_BIT,
	FAST_PWM_9_BIT,
	FAST_PWM_10_BIT,
	PWM_PAHSE_FREQ_CORRECT_ICR1,
	PWM_PAHSE_FREQ_CORRECT_OCRA1,
	PWM_PHASE_CORRECT_ICR1,
	PWM_PHASE_CORRECT_OCR1A,
	CTC_ICR1,
	FAST_PWM_ICR1=14,
	FAST_PWM_OCR1A=15,
}Timer1_Mode;

typedef enum
{
	Timer1_NO_CLK,
	Timer1_PRESCALER_1,
	Timer1_PRESCALER_8,
	Timer1_PRESCALER_64,
	Timer1_PRESCALER_256,
	Timer1_PRESCALER_1024,
	Timer1_EXT_CLK_FALL_EDGE,
	Timer1_EXT_CLK_RAIS_EDGE,
}Timer1_Prescaler;

typedef enum{
	Timer1_OC0_DISCONNECTED = 0,
	Timer1_OC0_SET = 3,
	Timer1_OC0_CLR = 2,
	Timer1_OC0_TOGGLE = 1,
}Timer1_Oc0;

/*************************************************************************************/
/* TIMER0 Configuration Structure */
/*************************************************************************************/
typedef struct {
	Timer1_Mode mode;
	Timer1_Prescaler prescaler;
	Timer1_Oc0 oc0;
	u8 ocr0;
} Timer1_Config;


void M_TIMER1_void_Init(const Timer1_Config* config);
void M_TIMER1_void_start(void);
void M_TIMER1_void_stop(void);
void M_TIMER1_void_setDelayTimeMilliSec(u32 copy_u32TimeMS);
void M_TIMER1_void_IntEnable(Timer1_IntID copy_u8IntID); // id overflow or compare match
void M_TIMER1_void_IntDisable(u8 copy_u8IntID);
void M_TIMER1_void_setCallBack(void (*ptrfn)(void),Timer1_IntID copy_u8IntID);
void M_TIMER1_void_setFastPWM(u8 freq, u8 duty);
void M_TIMER1_void_setPhaseCorrectPWM(u8 freq, u8 duty);


#endif /* TIMER1_INTERFACE_H_ */