/*
 * GIE_prog.c
 *
 *  Created on: Oct 22, 2023
 *      Author: zashr
 */

#include "GIE_interface.h"


// Enable Global Interrupts
void GIE_enable(){
    __asm__ __volatile__ ("sei" ::);
}

// Disable Global Interrupts
void GIE_disable(){
    __asm__ __volatile__ ("cli" ::);
}
