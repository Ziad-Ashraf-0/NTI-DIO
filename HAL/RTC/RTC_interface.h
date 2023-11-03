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


typedef struct{
 u8 hour;
 u8 minute;
 u8 sec;
 Hour_type hour_type;
 Hour_value hour_value;
}Time_Config;


void H_void_RTC_Init();
u8 H_void_RTC_setTime(Time_Config * config);
u8 H_void_RTC_getTime(Time_Config * config);


#endif /* RTC_INTERFACE_H_ */