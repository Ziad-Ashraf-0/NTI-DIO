/*
 * main.c
 *
 * Created on: Oct 21, 2023
 * Author: Ziad Ashraf
 */

// Include necessary header files
#define F_CPU 8000000UL
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/Segment/segment.h"
#include "../HAL/Keypad/Keypad_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/TIMER1/TIMER1_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../HAL/Ultrasonic/Ultrasonic_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include <util/delay.h>

// Global variables for duty cycle and frequency
u8 duty = 0;
u8 freq = 0;

// Function to take user input for duty cycle and frequency
void takeUserInput(void) {
    duty = 0;
    u8 key;
    H_LCD_void_clearScreen();
    H_LCD_void_sendString("Enter Duty Cycle: ");
    H_LCD_void_gotoXY(1, 0);
    for (u8 i = 0; i < 3; i++) {
        key = KEYPAD_getPressedKey();
        if (key == 13) {
            break;
        }
        duty = duty * 10 + key;
        H_LCD_void_sendIntNum(key);
    }
    H_LCD_void_clearScreen();
    H_LCD_void_sendString("Choose Freq : ");
    H_LCD_void_gotoXY(1, 0);
    H_LCD_void_sendString("1-62.5khz   2-7.8khz");
    H_LCD_void_gotoXY(2, 4);
    H_LCD_void_sendString("3-976hz     4-244khz");
    H_LCD_void_gotoXY(3, 4);
    H_LCD_void_sendString("5-61hz");
    freq = KEYPAD_getPressedKey();
}

int main(void) {
    // Configure the output pin for PWM signal
    DIO_Config oc0_pin = {DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT};
    DIO_U8SetPinDirection(&oc0_pin);

    // Enable global interrupt
    GIE_enable();

    // Initialize the LCD
    H_LCD_void_Init();

    while (1) {
        // Take user input for duty cycle and frequency
        takeUserInput();

        while (1) {
            // Configure and start Timer0 for PWM generation
            Timer0_Config config = {FAST_PWM, NO_CLK, OC0_CLR};
            M_TIMER0_void_Init(&config);
            M_TIMER0_void_setFastPWM(freq, duty);

            // Display a message on the LCD
            H_LCD_void_clearScreen();
            H_LCD_void_sendString("Motor Running ");
            H_LCD_void_gotoXY(1, 0);
            H_LCD_void_sendString("Go BACK?!");
            
            // Wait for the user to press a key (Enter key) to exit the loop
            u8 key = KEYPAD_getPressedKey();
            while (key != 13) {
                key = KEYPAD_getPressedKey();
            }
            break;
        }
    }

    return 0;
}
