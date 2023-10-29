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

typedef enum{
	TIMER1_FREQ_244_HZ		=	1,
	TIMER1_FREQ_30_HZ		=	2,
	TIMER1_FREQ_4_HZ		=	3,
	TIMER1_FREQ_1_HZ		=	4,
	TIMER1_FREQ_Quarter_HZ	=	5
}TIMER1_Valid_Freq;

#endif

typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

typedef enum
{
	TIMER1_OVERFLOW,
	TIMER1_COMPARE_A,
	TIMER1_COMPARE_B,
	TIMER1_ICU,
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
	Timer1_OC1A_OC1B_DISCONNECTED = 0,
	Timer1_OC1A_TOGGLE = 1,
	Timer1_OC1A_OC1B_CLR = 2,
	Timer1_OC1A_OC1B_SET = 3,
}Timer1_Oc1;

/*************************************************************************************/
/* TIMER0 Configuration Structure */
/*************************************************************************************/
typedef struct {
	Timer1_Mode mode;
	Timer1_Prescaler prescaler;
	Timer1_Oc1 oc1;
	u16 ocr1;
} Timer1_Config;


void M_TIMER1_void_Init(const Timer1_Config* config);
void M_TIMER1_void_start(void);
void M_TIMER1_void_stop(void);
void M_TIMER1_void_setDelayTimeMilliSec(u32 copy_u32TimeMS);
void M_TIMER1_void_IntEnable(Timer1_IntID copy_u8IntID); // id overflow or compare match
void M_TIMER1_void_IntDisable(u8 copy_u8IntID);
void M_TIMER1_void_setCallBack(void (*ptrfn)(void),Timer1_IntID copy_u8IntID);
void M_TIMER1_void_setFastPWM(TIMER1_Valid_Freq freq, u8 duty);
void M_TIMER1_void_setPhaseCorrectPWM(u8 freq, u8 duty);
u32 M_TIMER1_void_measureDutyCycle(void);
u16 M_TIMER1_void_getInputCaptureValue(void);
void M_TIMER1_void_setEdgeDetectionType(const Icu_EdgeType a_edgeType);
void M_TIMER1_void_clearTimerValue(void);


#endif /* TIMER1_INTERFACE_H_ */