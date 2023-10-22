/*
 * EXTI_interface.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Ziad
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

// Define the IDs for external interrupts
#define EXTI_INT0_ID 6
#define EXTI_INT1_ID 7
#define EXTI_INT2_ID 5

typedef enum
{
	LOW_LEVEL = 0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
} TriggerEdge_type;

void EXTI_enable(u8 Int_ID, u8 trigger);
void EXTI_disable(u8 Int_ID);
void EXTI_setCallBack(u8 Int_ID, void (*localPtr)(void));

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
