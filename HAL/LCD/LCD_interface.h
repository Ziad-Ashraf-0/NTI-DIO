/*
 * lcd.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Ziad
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LCD_DATA_BITS_MODE 4


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void H_LCD_void_Init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void H_LCD_void_sendCommand(u8 copy_u8command);

/*
 * Description :
 * Display the required character on the screen
 */
void H_LCD_void_sendData(u8 copy_u8data );

/*
 * Description :
 * Display the required string on the screen
 */
void H_LCD_void_sendString(const s8 * pstr);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(u8 row,u8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void H_LCD_void_sendIntNum(s32 copy_s32Num);

/*
 * Description :
 * Send the clear screen command
 */
void H_LCD_void_clearScreen(void);

/*
 * Description :
 * Send Custom char to GCRAM
 */
void H_LCD_void_creatCustomChar(const u8 * ArrPattern,u8 copy_u8charCode);

/*
 * Description :
 * Display the required custom char number 
 */
void H_LCD_void_displayCustomChar(u8 copy_u8charCode);

/*
 * Description :
 * Display float number 
 */
void H_LCD_void_displayFloat(f64 copy_u8floatNumber);


/*
 * Description :
 * Display Hex value 
 */
void H_LCD_void_sendHexNum(u32 copy_u32Num);

/*
 * Description :
 * Display char as binary 
 */
void H_LCD_void_sendBinaryNum(u8 copy_u8Num);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
