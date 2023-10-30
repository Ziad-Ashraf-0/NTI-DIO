/*
 * LCD_config.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Ziad
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_DATA_BITS_MODE 4

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT DIO_PORTA
#define LCD_EN_PORT DIO_PORTA

#define LCD_RS_PIN DIO_PIN3
#define LCD_EN_PIN DIO_PIN2


#define LCD_D4_PORT DIO_PORTB
#define LCD_D5_PORT DIO_PORTB
#define LCD_D6_PORT DIO_PORTB
#define LCD_D7_PORT DIO_PORTB


#define LCD_D4_PIN DIO_PIN0
#define LCD_D5_PIN DIO_PIN1
#define LCD_D6_PIN DIO_PIN2
#define LCD_D7_PIN DIO_PIN3


/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

#endif /* HAL_LCD_LCD_CONFIG_H_ */
