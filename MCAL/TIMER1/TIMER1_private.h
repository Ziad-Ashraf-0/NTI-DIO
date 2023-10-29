/*
 * TIMER1_private.h
 *
 * Created: 10/28/2023 12:10:19 PM
 *  Author: Ziad
 */ 


#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

/*************************************************************************************/
/* 								TIMER1 REGISTERS										 */
/*************************************************************************************/

typedef struct {
	u16 ICR1;
	u8 OCR1BL;
	u8 OCR1BH;
	u8 OCR1AL;
	u8 OCR1AH;
	u16 TCNT1;
	u8 TCCR1B;
	u8 TCCR1A;
	u8 padding[9];
	u8 TIMSK;
}Timer1_Type;

#define TIMER1_BASE ((volatile Timer1_Type *) 0x46)

//TCCR1A bits
#define COM1A1_BIT 7
#define COM1A0_BIT 6
#define COM1B1_BIT 5
#define COM1B0_BIT 4
#define FOC1A_BIT  3
#define FOC1B_BIT  2
#define WGM11_BIT  1
#define WGM10_BIT  0


//TCCR1B
#define ICNC1_BIT 7
#define ICES1_BIT 6
#define WGM13_BIT 4
#define WGM12_BIT 3
#define CS12_BIT  2
#define CS11_BIT  1
#define CS10_BIT  0



//TIMSK bits
#define TICIE1_BIT 5
#define OCIE1A_BIT 4
#define OCIE1B_BIT 3
#define TOIE1_BIT  2

// Bit masks
#define TIMER1_PRESCALER_MASK    0xF8   //Prescaler
#define TIMER1_WGM11_WGM10_MASK  0x03
#define TIMER1_WGM12_WGM12_MASK  0xE7   



// Define the TIMER1 vector
#define TIMER1_OVF_vect			__vector_9 // Timer1 Overflow Interrupt Vector
#define TIMER1_COMPB_vect		__vector_8 // Timer1 Compare Match B Interrupt Vector
#define TIMER1_COMPA_vect		__vector_7 // Timer1 Compare Match A Interrupt Vector
#define TIMER1_CAPT_vect		__vector_6 // Timer/Counter1 Capture Event Interrupt Vector


#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal)); \
void vector (void)


#endif /* TIMER1_PRIVATE_H_ */