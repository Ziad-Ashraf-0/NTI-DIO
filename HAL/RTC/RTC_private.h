/*
 * RTC_private.h
 *
 * Created: 11/3/2023 10:40:38 AM
 *  Author: Ziad
 */ 


#ifndef RTC_PRIVATE_H_
#define RTC_PRIVATE_H_


#define Device_Write_address   0xD0  /* Define RTC DS1307 slave write address */
#define Device_Read_address    0xD1  /* Make LSB bit high of slave address for read */
#define Seconds_address        0x00  /* Address of the seconds register in RTC DS1307 */
#define Days_address           0x03  /* Address of the days register in RTC DS1307 */


#endif /* RTC_PRIVATE_H_ */