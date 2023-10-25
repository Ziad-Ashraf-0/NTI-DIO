/*
 * EXTI_private.h
 *
 * Created: 10/25/2023 11:26:38 AM
 *  Author: zashr
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


// Define the INT2_vect vector
#define INT0_vect  __vector_1
#define INT1_vect  __vector_2
#define INT2_vect  __vector_3

// ... (other code)

#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal)); \
void vector (void)


#endif /* EXTI_PRIVATE_H_ */