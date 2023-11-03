/*
* RTC_prog.c
*
* Created: 11/3/2023 10:39:45 AM
*  Author: Ziad
*/

// Include necessary header files
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/TWI/TWI_interface.h"
#include "RTC_config.h"
#include "RTC_interface.h"
#include "RTC_private.h"

// Function to initialize the RTC
void H_RTC_void_Init()
{
	// Configure TWI (I2C) communication with a bit rate of 100
	TWI_Config twi_config = {BIT_RATE_100};
	M_TWI_void_init(&twi_config);
}

// Function to set the time on the RTC
u8 H_RTC_void_setTime(Time_Config * config)
{
	u8 status;

	// Start the TWI communication
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the start condition was successful
	if (status != TWI_START)
	return ERROR;

	// Send the device write address
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_W_ACK)
	return ERROR;

	// Send the address of the register where we want to write time data (0x00)
	M_TWI_void_writeByte(Seconds_address);
	M_TWI_void_getStatus(&status);

	// Check if the data address was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the time data in BCD format
	M_TWI_void_writeByte((config->sec / 10) << 4 | (config->sec % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the minute data in BCD format
	M_TWI_void_writeByte((config->minute / 10) << 4 | (config->minute % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the hour data in BCD format
	M_TWI_void_writeByte(config->hour_type << 6 | config->hour_value << 5 | (config->hour / 10) << 4 | (config->hour % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Stop the TWI communication
	M_TWI_void_stop();

	return SUCCESS;
}

// Function to get the current time from the RTC
u8 H_RTC_void_getTime(Time_Config * config)
{
	u8 status, data;

	// Start the TWI communication
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the start condition was successful
	if (status != TWI_START)
	return ERROR;

	// Send the device write address
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_W_ACK)
	return ERROR;

	// Send the address of the register from which we want to read time data (0x00)
	M_TWI_void_writeByte(0x00);
	M_TWI_void_getStatus(&status);

	// Check if the data address was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Start a repeated start condition for reading
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the repeated start condition was successful
	if (status != TWI_REP_START)
	return ERROR;

	// Send the device read address
	M_TWI_void_writeByte(Device_Read_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_R_ACK)
	return ERROR;

	// Read seconds data and acknowledge
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MR_DATA_ACK)
	return ERROR;

	// Extract and store the seconds from the received data
	config->sec = (data & 0x0F) + (((data & 0x70) * 10) >> 4);

	// Read minutes data and acknowledge
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MR_DATA_ACK)
	return ERROR;

	// Extract and store the minutes from the received data
	config->minute = (data & 0x0F) + (((data & 0x70) * 10) >> 4);

	// Read hour data without acknowledging
	M_TWI_void_readByteWithNACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was not acknowledged
	if (status != TWI_MR_DATA_NACK)
	return ERROR;

	// Check if the RTC is using 12-hour format
	if (BIT_IS_SET(data, 6))
	{
		// Extract and store the hour from the received data (12-hour format)
		config->hour = (data & 0x0F) + (((data & 0x10) * 10) >> 4);
		config->hour_type = HOUR_12;
		config->hour_value = (data >> 5) & 1;
	}
	else
	{
		// Extract and store the hour from the received data (24-hour format)
		config->hour = (data & 0x0F) + (((data & 0x30) * 10) >> 4);
	}

	// Stop the TWI communication
	M_TWI_void_stop();

	return SUCCESS;
}

// Function to set the date on the RTC
u8 H_RTC_void_setDate(Date_config * config)
{
	u8 status;

	// Start the TWI communication
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the start condition was successful
	if (status != TWI_START)
	return ERROR;

	// Send the device write address
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_W_ACK)
	return ERROR;

	// Send the address of the register where we want to write date data (0x03)
	M_TWI_void_writeByte(Days_address);
	M_TWI_void_getStatus(&status);

	// Check if the data address was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the day data
	M_TWI_void_writeByte(config->day);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the date data in BCD format
	M_TWI_void_writeByte((config->date / 10) << 4 | (config->date % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the month data in BCD format
	M_TWI_void_writeByte((config->month / 10) << 4 | (config->month % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Send the year data in BCD format
	M_TWI_void_writeByte((config->year / 10) << 4 | (config->year % 10));
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Stop the TWI communication
	M_TWI_void_stop();

	return SUCCESS;
}

// Function to get the current date from the RTC
u8 H_RTC_void_getDate(Date_config * config)
{
	u8 status, data;

	// Start the TWI communication
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the start condition was successful
	if (status != TWI_START)
	return ERROR;

	// Send the device write address
	M_TWI_void_writeByte(Device_Write_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_W_ACK)
	return ERROR;

	// Send the address of the register from which we want to read date data (0x03)
	M_TWI_void_writeByte(0x03);
	M_TWI_void_getStatus(&status);

	// Check if the data address was acknowledged
	if (status != TWI_MT_DATA_ACK)
	return ERROR;

	// Start a repeated start condition for reading
	M_TWI_void_start();
	M_TWI_void_getStatus(&status);

	// Check if the repeated start condition was successful
	if (status != TWI_REP_START)
	return ERROR;

	// Send the device read address
	M_TWI_void_writeByte(Device_Read_address);
	M_TWI_void_getStatus(&status);

	// Check if the device address was acknowledged
	if (status != TWI_MT_SLA_R_ACK)
	return ERROR;

	// Read day data and acknowledge
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MR_DATA_ACK)
	return ERROR;

	// Store the day
	config->day = data;

	// Read date data and acknowledge
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MR_DATA_ACK)
	return ERROR;

	// Extract and store the date from the received data
	config->date = (data & 0x0F) + (((data & 0x30) * 10) >> 4);

	// Read month data and acknowledge
	M_TWI_void_readByteWithACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was acknowledged
	if (status != TWI_MR_DATA_ACK)
	return ERROR;

	// Extract and store the month from the received data
	config->month = (data & 0x0F) + (((data & 0x10) * 10) >> 4);

	// Read year data without acknowledging
	M_TWI_void_readByteWithNACK(&data);
	M_TWI_void_getStatus(&status);

	// Check if the data was not acknowledged
	if (status != TWI_MR_DATA_NACK)
	return ERROR;

	// Extract and store the year from the received data
	config->year = (data & 0x0F) + (((data & 0xF0) * 10) >> 4);

	// Stop the TWI communication
	M_TWI_void_stop();

	return SUCCESS;
}
