/*
 * EEPROM_prog.c
 *
 * Created: 10/31/2023 12:01:24 PM
 *  Author: Ziad
 */ 
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../LIB/BIT_MATH.h"
#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "../../MCAL/TWI/TWI_interface.h"

void EEPROM_Init()
{
	TWI_Config twi_config = {BIT_RATE_400,0x01};
	M_TWI_void_init(&twi_config);
}

u8 EEPROM_WriteByte(u16 Addr,u8 data)
{
	u8 status;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	M_TWI_void_writeByte((u8)(0xA0 | ((Addr & 0x0300) >> 7)));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	M_TWI_void_writeByte((u8)Addr);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_writeByte(data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_stop();

	return SUCCESS;
}

u8 EEPROM_ReadByte(u16 Addr,u8 *data)
{
	u8 status;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	M_TWI_void_writeByte((u8)(0xA0 | ((Addr & 0x0300) >> 7)));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	M_TWI_void_writeByte((u8)Addr);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_REP_START)
	return ERROR;
	M_TWI_void_writeByte((u8)(0xA0 | ((Addr & 0x0300) >> 7) | 1));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_R_ACK)
	return ERROR;
	M_TWI_void_readByteWithNACK(data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_NACK)
	return ERROR;
	M_TWI_void_stop();

	return SUCCESS;
}