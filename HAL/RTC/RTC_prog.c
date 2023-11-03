/*
* RTC_prog.c
*
* Created: 11/3/2023 10:39:45 AM
*  Author: Ziad
*/
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/TWI/TWI_interface.h"
#include "RTC_config.h"
#include "RTC_interface.h"
#include "RTC_private.h"



void H_RTC_void_Init()
{
	TWI_Config twi_config = {BIT_RATE_100};
	M_TWI_void_init(&twi_config);
}

u8 H_RTC_void_setTime(Time_Config * config){
	u8 status;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	M_TWI_void_writeByte(0x00);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_writeByte((config->sec / 10) << 4 | (config->sec % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_writeByte((config->minute / 10) << 4 | (config->minute % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_writeByte(config->hour_type << 6 | config->hour_value << 5 | (config->hour / 10) << 4 | (config->hour % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	M_TWI_void_stop();
	return SUCCESS;
}


u8 H_RTC_void_getTime(Time_Config * config){
	u8 status,data;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	
	M_TWI_void_writeByte(0x00);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_REP_START)
	return ERROR;
	
	M_TWI_void_writeByte(Device_Read_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_R_ACK)
	return ERROR;
	
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_ACK)
	return ERROR;
	config->sec = (data & 0x0F) + (((data & 0x70) * 10) >> 4);
	
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_ACK)
	return ERROR;
	config->minute = (data & 0x0F) + (((data & 0x70) * 10) >> 4);
	
	M_TWI_void_readByteWithNACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_NACK)
	return ERROR;
	if(BIT_IS_SET(data,6)){
		config->hour = (data & 0x0F) + (((data & 0x10) * 10) >> 4);
		config->hour_type = HOUR_12;
		config->hour_value = (data >> 5 ) & 1;
		}else{
		config->hour = (data & 0x0F) + (((data & 0x30) * 10) >> 4);
	}
	
	M_TWI_void_stop();
	return SUCCESS;
}


u8 H_RTC_void_setDate(Date_config * config){
	u8 status;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	
	M_TWI_void_writeByte(0x03);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_writeByte(config->day);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_writeByte((config->date / 10) << 4 | (config->date % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_writeByte((config->month / 10) << 4 | (config->month % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_writeByte((config->year / 10) << 4 | (config->year % 10));
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	
	M_TWI_void_stop();
	return SUCCESS;
}


u8 H_RTC_void_getDate(Date_config * config){
	u8 status,data;
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_START)
	return ERROR;
	
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_W_ACK)
	return ERROR;
	
	M_TWI_void_writeByte(0x03);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_DATA_ACK)
	return ERROR;
	
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);
	if(status != TWI_REP_START)
	return ERROR;
	
	M_TWI_void_writeByte(Device_Read_address);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MT_SLA_R_ACK)
	return ERROR;
	
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_ACK)
	return ERROR;
	config->day = data;
	
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_ACK)
	return ERROR;
	config->date = (data & 0x0F) + (((data & 0x30) * 10) >> 4);
	
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_ACK)
	return ERROR;
	config->month = (data & 0x0F) + (((data & 0x10) * 10) >> 4);
	
	M_TWI_void_readByteWithNACK(&data);
	M_TWI_void_getStatus(&status);
	if(status != TWI_MR_DATA_NACK)
	return ERROR;
	config->year = (data & 0x0F) + (((data & 0xF0) * 10) >> 4);

	
	M_TWI_void_stop();
	return SUCCESS;
}