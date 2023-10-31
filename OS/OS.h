/*
 * OS.h
 *
 * Created: 10/31/2023 7:32:32 PM
 *  Author: zashr
 */ 


#ifndef OS_H_
#define OS_H_


typedef void (*TaskFunction)(void);

typedef struct {
	TaskFunction taskFunc;
	u16 period;
	u16 counter;
	u8 priority;
} TaskControlBlock;

void startOS(void);



#endif /* OS_H_ */