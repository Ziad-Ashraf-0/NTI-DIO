/*
 * LCD_config.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Ziad
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

#define LCD_DATA_BITS_MODE 4

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
#define LCD_D7_PIN DIO_PIN4

#define LCD_SET_CURSOR_LOCATION        0x80

#endif /* HAL_LCD_LCD_CONFIG_H_ */
