/*
* OS.c
*
* Created: 10/31/2023 7:32:14 PM
*  Author: zashr
*/
#include "../LIB/STD_TYPES.h"
#include "OS.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../LIB/BIT_MATH.h"


void pendSV(void);
void runHighestPriorityTask();

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
		led.pin= DIO_PIN2;
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
	{Task1Callback, 1000, 0}, // Task 1 with a 1-second period
	{Task2Callback, 500, 0},  // Task 2 with a 500 ms period
	{Task3Callback, 3000, 0}, // Task 3 with a 3-second period
};
#define NUM_TASKS 5

// Define a simple task queue using FIFO
TaskControlBlock* taskQueue[5];
u8 queueSize = 0;
u8 queueFront = 0; // Front of the queue
u8 queueRear = 0;  // Rear of the queue

// Initialize the hardware
void startOS() {
	DIO_Config pins[] = {
		{DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT},
		{DIO_PORTB, DIO_PIN1, DIO_PIN_INPUT},
		{DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT},
		{DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT},
	};
	// Initialize pins
	for (u8 i = 0; i < 4; i++) {
		DIO_U8SetPinDirection(&pins[i]);
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
			// Add the task to the task queue (FIFO)
			if (queueSize < NUM_TASKS) {
				taskQueue[queueRear] = &tasks[i];
				queueRear = (queueRear + 1) % NUM_TASKS; // Circular queue
				queueSize++;
			}
			tasks[i].counter = 0; // Reset the counter
		}
	}
	runHighestPriorityTask(); // Execute the highest-priority task
}

// Execute the next task from the FIFO queue
void runHighestPriorityTask() {
	if (queueSize > 0) {
		TaskControlBlock* nextTask = taskQueue[queueFront];
		queueFront = (queueFront + 1) % NUM_TASKS; // Circular queue
		queueSize--;

		// Execute the next task in the queue
		nextTask->taskFunc();
	}
}