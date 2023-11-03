/*
* RTC_interface.h
*
* Created: 11/3/2023 10:40:15 AM
* Author: Ziad
*/

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

// Constants for error and success status
#define ERROR 0
#define SUCCESS 1

// Enumeration for 12-hour or 24-hour clock format
typedef enum {
	HOUR_12 = 1, // 12-hour clock format
	HOUR_24 = 0  // 24-hour clock format
} Hour_type;

// Enumeration for AM or PM in 12-hour clock format
typedef enum {
	AM = 0, // AM
	PM = 1  // PM
} Hour_value;

// Enumeration for days of the week
typedef enum {
	Saturday = 1,
	Sunday = 2,
	Monday = 3,
	Tuesday = 4,
	Wednesday = 5,
	Thursday = 6,
	Friday = 7
} Days;

// Structure to hold time configuration
typedef struct {
	u8 hour;          // Hour
	u8 minute;        // Minute
	u8 sec;           // Second
	Hour_type hour_type; // 12-hour or 24-hour clock format
	Hour_value hour_value; // AM or PM (valid in 12-hour format)
} Time_Config;

// Structure to hold date configuration
typedef struct {
	Days day; // Day of the week
	u8 date;  // Date
	u8 month; // Month
	u8 year;  // Year
} Date_config;

// Function to initialize the RTC
void H_RTC_void_Init();

// Function to set the time on the RTC
u8 H_RTC_void_setTime(Time_Config * config);

// Function to get the current time from the RTC
u8 H_RTC_void_getTime(Time_Config * config);

// Function to set the date on the RTC
u8 H_RTC_void_setDate(Date_config * config);

// Function to get the current date from the RTC
u8 H_RTC_void_getDate(Date_config * config);

#endif /* RTC_INTERFACE_H_ */
