#include "../LIB/STD_TYPES.h"
#include "OS.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../LIB/BIT_MATH.h"


void runHighestPriorityTask() ;
void pendSV(void);
// Define the task functions
void Task1Callback(void) {
	// Toggle PB0 LED
	DIO_Config led = {DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT};
	DIO_U8TogglePin(&led);
}

void Task2Callback(void) {
	// Check the state of PB1 and toggle the BLUE LED if pressed
	u8 value;
	DIO_Config led = {DIO_PORTB, DIO_PIN1};
	DIO_U8GetPinValue(&led, &value);
	if (value == 0) {
		led.pin = DIO_PIN2;
		DIO_U8TogglePin(&led);
	}
}

void Task3Callback(void) {
	// Toggle the Green LED
	DIO_Config led = {DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT};
	DIO_U8TogglePin(&led);
}

// Define the task control blocks
TaskControlBlock tasks[] = {
	{Task1Callback, 1000,0 , 2}, // Task 1 with a 1-second period
	{Task2Callback, 500, 0, 1},  // Task 2 with a 500 ms period
	{Task3Callback, 3000,0 ,3}, // Task 3 with a 3-second period
};
#define NUM_TASKS 3

// Define a simple task queue using priority
TaskControlBlock* taskQueue[NUM_TASKS];
u8 queueSize = 0;

// Initialize the hardware
void startOS() {
	DIO_Config pins[] = {
		{DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT,DIO_PIN_LOW},
		{DIO_PORTB, DIO_PIN1, DIO_PIN_INPUT,DIO_PIN_HIGH},
		{DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT,DIO_PIN_LOW},
		{DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT,DIO_PIN_LOW},
	};

	// Initialize pins
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinDirection(&pins[i]);
		DIO_U8SetPinValue(&pins[i]);
	}

	Timer0_Config timer = {NORMAL, PRESCALER_1024};
	M_TIMER0_void_Init(&timer);
	M_TIMER0_void_setCallBack(pendSV, OVERFLOW);
	M_TIMER0_void_IntEnable(OVERFLOW);
	M_TIMER0_void_setDelayTimeMilliSec(500);
	M_TIMER0_void_start();
}

void pendSV(void) {
	  for (u8 i = 0; i < NUM_TASKS; i++) {
		  tasks[i].counter += 500; // Increment the counter for all tasks

		  if (tasks[i].counter >= tasks[i].period) {
			  // Task is ready to run, add it to the queue based on priority
			  if (queueSize < NUM_TASKS) {
				  u8 insertIndex = 0;
				  for (u8 j = 0; j < queueSize; j++) {
					  if (tasks[i].priority > taskQueue[j]->priority) {
						  break;
					  }
					  insertIndex++;
				  }
				  // Shift existing tasks to make space for the new task
				  for (u8 j = queueSize; j > insertIndex; j--) {
					  taskQueue[j] = taskQueue[j - 1];
				  }
				  taskQueue[insertIndex] = &tasks[i];
				  queueSize++;
			  }else{
				  	  // Clear the task queue before adding tasks
				  	  queueSize = 0;
			  }
			 
		  }
	  }
	  runHighestPriorityTask(); // Execute the highest-priority task
}

void runHighestPriorityTask() {
	for (u8 i = 0; i < NUM_TASKS; i++) {
		if (tasks[i].counter >= tasks[i].period) {
			tasks[i].counter = 0;
			tasks[i].taskFunc();
		}
	}
}