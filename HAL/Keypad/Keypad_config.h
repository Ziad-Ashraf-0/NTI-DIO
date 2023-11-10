/*
 * Keypad_config.h
 *
 * Created: 10/25/2023 1:25:17 PM
 *  Author: zashr
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define COL1_PORT DIO_PORTD
#define COL2_PORT DIO_PORTD
#define COL3_PORT DIO_PORTD
#define COL4_PORT DIO_PORTD

#define COL1_PIN DIO_PIN5
#define COL2_PIN DIO_PIN4
#define COL3_PIN DIO_PIN2
#define COL4_PIN DIO_PIN1

#define ROW1_PORT DIO_PORTC
#define ROW2_PORT DIO_PORTC
#define ROW3_PORT DIO_PORTC
#define ROW4_PORT DIO_PORTC

#define ROW1_PIN DIO_PIN5
#define ROW2_PIN DIO_PIN4
#define ROW3_PIN DIO_PIN3
#define ROW4_PIN DIO_PIN2


#endif /* KEYPAD_CONFIG_H_ */