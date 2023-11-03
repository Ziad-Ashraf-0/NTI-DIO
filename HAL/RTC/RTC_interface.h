/*
* RTC_interface.h
*
* Created: 11/3/2023 10:40:15 AM
*  Author: Ziad
*/


#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_



#define ERROR 0
#define SUCCESS 1

typedef enum{
	HOUR_12 = 1,
	HOUR_24 = 0,
}Hour_type;

typedef enum{
	AM = 0,
	PM = 1,
}Hour_value;

typedef enum{
	Saturday	= 1,
	Sunday		= 2,
	Monday		= 3,
	Tuesday		= 4,
	Wednesday	= 5,
	Thursday	= 6,
	Friday		= 7
}Days;


typedef struct{
	u8 hour;
	u8 minute;
	u8 sec;
	Hour_type hour_type;
	Hour_value hour_value;
}Time_Config;

typedef struct{
	Days day;
	u8 date;
	u8 month;
	u8 year;
}Date_config;


void H_RTC_void_Init();
u8 H_RTC_void_setTime(Time_Config * config);
u8 H_RTC_void_getTime(Time_Config * config);
u8 H_RTC_void_setDate(Date_config * config);
u8 H_RTC_void_getDate(Date_config * config);


#endif /* RTC_INTERFACE_H_ */