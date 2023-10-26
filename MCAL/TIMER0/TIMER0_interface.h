/*
 * TIMER0_interface.h
 *
 * Created: 10/26/2023 2:19:17 PM
 *  Author: zashr
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_



void M_TIMER0_void_Init(void);
void M_TIMER0_void_start(void);
void M_TIMER0_void_stop(void);
void M_TIMER0_void_setDelayTimeMilliSec(u32 copy_u32TimeMS);
void M_TIMER0_void_IntEnable(u8 copy_u8IntID);
void M_TIMER0_void_IntDisable(u8 copy_u8IntID);
void M_TIMER0_void_setCallBack(void (*ptrfn)(void),u8 copy_u8IntID);




#endif /* TIMER0_INTERFACE_H_ */