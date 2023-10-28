/*
 * TIMER0_private.h
 *
 * Created: 10/26/2023 2:19:38 PM
 * Author: zashr
 */

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* Definitions for Timer0 Register Addresses */

#define TCCR0_REG    (*((u8*)0x53))  // Timer Control Register
#define TCNT0_REG    (*((u8*)0x52))  // Timer Counter Register
#define OCR0_REG     (*((u8*)0x5C))  // Output Compare Register
#define TIMSK_REG    (*((u8*)0x59))  // Timer Interrupt Mask Register
#define TIFR_REG     (*((u8*)0x58))  // Timer Interrupt Flag Register

// Bit positions in TCCR0_REG
#define FOC_BIT		7   // Force Output Compare Bit
#define WGM00_BIT   6 // Waveform Generation Mode Bit 0
#define COM01_BIT   5 // Compare Output Mode Bit 1
#define COM00_BIT   4 // Compare Output Mode Bit 0
#define WGM01_BIT   3 // Waveform Generation Mode Bit 1
#define CS02_BIT    2  // Clock Select Bit 2
#define CS01_BIT    1  // Clock Select Bit 1
#define CS00_BIT    0  // Clock Select Bit 0

// Bit positions in TIMSK_REG
#define OCIE0_BIT    1 // Output Compare Match Interrupt Enable Bit
#define TOIE0_BIT    0 // Timer Overflow Interrupt Enable Bit

// Prescaler values
#define TIMER0_NO_CLK               0
#define TIMER0_PRESCALER_1          1
#define TIMER0_PRESCALER_8          2
#define TIMER0_PRESCALER_64         3    
#define TIMER0_PRESCALER_256        4
#define TIMER0_PRESCALER_1024       5
#define TIMER0_EXT_CLK_FALL_EDGE    6
#define TIMER0_EXT_CLK_RAIS_EDGE	7

// Timer modes
#define TIMER0_MODE_NORMAL              0
#define TIMER0_MODE_CTC                 2
#define TIMER0_MODE_FAST_PWM			3
#define TIMER0_MODE_PHASE_CORRECT_PWM	1

// Output Compare (OC0) modes
#define TIMER0_OC0_DISCONNECTED			0
#define TIMER0_OC0_SET					3
#define TIMER0_OC0_CLR					2
#define TIMER0_OC0_TOGGLE				1

// Bit mask to isolate the prescaler bits
#define TIMER0_PRESCALER_MASK    0xF8

// Define the TIMER0 vector
#define TIMER0_OVF_vect     __vector_11 // Timer0 Overflow Interrupt Vector
#define TIMER0_COMP_vect    __vector_10 // Timer0 Compare Match Interrupt Vector


#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal)); \
void vector (void)

#endif /* TIMER0_PRIVATE_H_ */
