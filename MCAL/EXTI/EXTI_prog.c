/*
 * EXTI_prog.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Ziad
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/HW_REG.h"
#include "EXTI_interface.h"



// Array of three pointers to functions
void (*Action[3])(void) = {NULL, NULL, NULL};



void EXTI_enable(u8 Int_ID, u8 trigger){

	if(Int_ID < EXTI_INT1_ID){
		SET_BIT(EXTI_BASE->GICR, Int_ID);
	}

	switch (Int_ID)
	{
	case EXTI_INT0_ID:
		EXTI_BASE->MCUCR &= 0xFC;
		EXTI_BASE->MCUCR |= trigger;
		break;
	case EXTI_INT1_ID:
		EXTI_BASE->MCUCR &= 0xF3;
		EXTI_BASE->MCUCR |= trigger << 2;
		break;
	case EXTI_INT2_ID:
		EXTI_BASE->MCUCSR &= 0xBF;
		EXTI_BASE->MCUCSR |= trigger << 6;
		break;
	}

}

void EXTI_disable(u8 Int_ID)
{
	if(Int_ID < EXTI_INT1_ID){
		CLR_BIT(EXTI_BASE->GICR, Int_ID);
	}
}

void EXTI_setCallBack(u8 Int_ID, void (*localPtr)(void))
{
	switch (Int_ID)
	{
	case EXTI_INT0_ID:
		Action[0] = localPtr;
		break;
	case EXTI_INT1_ID:
		Action[1] = localPtr;
		break;
	case EXTI_INT2_ID:
		Action[2] = localPtr;
		break;
	}
}

void __vector_1 (void){
	if(Action[0]!= NULL){
		Action[0]();
	}
}

void __vector_2 (void){
	if(Action[1]!= NULL){
		Action[1]();
	}
}

void __vector_18 (void){
	if(Action[2]!= NULL){
		Action[2]();
	}
}
