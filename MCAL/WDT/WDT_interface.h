/*
 * WDT_interface.h
 *
 * Created: 11/5/2023 9:42:40 AM
 *  Author: Ziad
 */ 


#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

typedef enum{
	WDT_17_ms,
	WDT_34_ms,
	WDT_68_ms,
	WDT_0_14_s,
	WDT_0_27_s,
	WDT_0_55_s,
	WDT_1_1_s,
	WDT_2_2_s,	
}WDT_timeout;

void M_WDT_void_Enable(void);
void M_WDT_void_refresh(void);
void M_WDT_void_Disable(void);
void M_WDT_void_Sleep(WDT_timeout copy_u8SleepTime);



#endif /* WDT_INTERFACE_H_ */