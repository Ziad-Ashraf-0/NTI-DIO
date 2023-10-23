/*
 * LCD_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Ziad
 */
#include <stdlib.h>
#include <util/delay.h> /* For the delay functions */
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../LIB/BIT_MATH.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void functionSet();

void H_LCD_void_Init(void){
	DIO_Config lcdInit[] = {
			{LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT},//PA3 RS
			{LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT},//PA2 EN
	};
	// Initialize RS EN pins
	for (u8 i = 0; i < 2; i++) {
		DIO_U8SetPinDirection(&lcdInit[i]);
	}

#if (LCD_DATA_BITS_MODE == 4)
	DIO_Config dataPins[] = {
			{LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT},//PD4 data bin
			{LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT},//PD5 data bin
			{LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT},//PD6 data bin
			{LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT},//PD7 data bin
	};
	// Initialize RS EN pins
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinDirection(&dataPins[i]);
	}

	//Function Set Corner Case
	functionSet();
	//H_LCD_void_sendCommand(0x02);
	//	_delay_ms(1);
	//	H_LCD_void_sendCommand(0x28);
	_delay_ms(1);
	H_LCD_void_sendCommand(0x0F);
	_delay_ms(1);
	H_LCD_void_sendCommand(0x01);
	_delay_ms(2);
	H_LCD_void_sendCommand(0x06);

#elif (LCD_DATA_BITS_MODE == 8)

#endif
}



void H_LCD_void_sendCommand(u8 copy_u8command)
{
	//set mode to command
	DIO_Config mode[] = {
			{LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW},//PA3 RS
			{LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT,DIO_PIN_HIGH},//PA2 EN
	};
	// Initialize RS EN pins
	for (u8 i = 0; i < 2; i++) {
		DIO_U8SetPinValue(&mode[i]);
		_delay_ms(1); /* delay for processing Tas = 50ns */
	}
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */


#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required command to the data bus D4 --> D7 */
	H_LCD_void_latchByte(copy_u8command);
#else

#endif

}

void H_LCD_void_sendData(u8 copy_u8data )
{
	DIO_Config mode[] = {
			{LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT, DIO_PIN_HIGH},//PA3 RS
			{LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT,DIO_PIN_HIGH},//PA2 EN
	};
	// Initialize RS EN pins
	for (u8 i = 0; i < 2; i++) {
		DIO_U8SetPinValue(&mode[i]);
		_delay_ms(1); /* delay for processing Tas = 50ns */
	}
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */


#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required command to the data bus D4 --> D7 */
	H_LCD_void_latchByte(copy_u8data);
#else

#endif
}


void H_LCD_void_sendString(const s8 * pstr){
	u8 i = 0;
	while(pstr[i] != '\0')
	{
		H_LCD_void_sendData(pstr[i]);
		i++;
	}
}

void H_LCD_void_sendIntNum(s32 copy_s32Num){
	s8 buff[16]; /* String to hold the ascii result */
	itoa(copy_s32Num,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	H_LCD_void_sendString(buff); /* Display the string */
}

void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col){
	u8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(copy_u8Row)
	{
	case 0:
		lcd_memory_address=copy_u8Col;
		break;
	case 1:
		lcd_memory_address=copy_u8Col+0x40;
		break;
	case 2:
		lcd_memory_address=copy_u8Col+0x10;
		break;
	case 3:
		lcd_memory_address=copy_u8Col+0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	H_LCD_void_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}


void H_LCD_void_creatCustomChar(const u8 * ArrPattern,u8 copy_u8charCode){
	unsigned char i;
	if(copy_u8charCode<8)
	{
		H_LCD_void_sendCommand(0x40 + (copy_u8charCode*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++){	/* Write 8 byte for generation of 1 character */
			H_LCD_void_sendData(ArrPattern[i]);
		}
	}
}


void H_LCD_void_displayCustomChar(u8 copy_u8charCode){

	H_LCD_void_sendCommand(0xc0);
	H_LCD_void_sendData(copy_u8charCode);

}



void functionSet(){
	DIO_Config dataPins[] = {
			{LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT,DIO_PIN_LOW},//PD4 data bin
			{LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT,DIO_PIN_HIGH},//PD5 data bin
			{LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT,DIO_PIN_LOW},//PD6 data bin
			{LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT,DIO_PIN_LOW},//PD7 data bin
	};
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinValue(&dataPins[i]);
	}

	DIO_Config enable;
	enable.port = LCD_EN_PORT;
	enable.pin = LCD_EN_PIN;
	enable.value = DIO_PIN_LOW;
	_delay_ms(1); /* delay for processing*/
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing*/
	enable.value = DIO_PIN_HIGH;
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing */

	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinValue(&dataPins[i]);
	}

	_delay_ms(1); /* delay for processing*/
	enable.value = DIO_PIN_LOW;
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing*/


	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinValue(&dataPins[i]);
	}

	_delay_ms(1); /* delay for processing*/
	enable.value = DIO_PIN_LOW;
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing*/
}

static void H_LCD_void_latchByte(u8 copy_u8Byte){
	DIO_Config dataPins[] = {
			{LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT,GET_BIT(copy_u8Byte, 4)},//PD4 data bin
			{LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT,GET_BIT(copy_u8Byte, 5)},//PD5 data bin
			{LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT,GET_BIT(copy_u8Byte, 6)},//PD6 data bin
			{LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT,GET_BIT(copy_u8Byte, 7)},//PD7 data bin
	};
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinValue(&dataPins[i]);
	}

	DIO_Config enable;
	enable.port = LCD_EN_PORT;
	enable.pin = LCD_EN_PIN;
	enable.value = DIO_PIN_LOW;
	_delay_ms(1); /* delay for processing */
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing */
	enable.value = DIO_PIN_HIGH;
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing */

	for (u8 i = 0; i < 4; i++) {
		dataPins[i].value = GET_BIT(copy_u8Byte, i);
		DIO_U8SetPinValue(&dataPins[i]);
	}

	_delay_ms(1); /* delay for processing */
	enable.value = DIO_PIN_LOW;
	DIO_U8SetPinValue(&enable);
	_delay_ms(1); /* delay for processing*/


}
