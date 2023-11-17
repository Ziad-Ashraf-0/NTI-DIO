/*
 * main.c
 *
 * Created on: Oct 21, 2023
 * Author: Ziad Ashraf
 */

// Include necessary header files
#define  F_CPU 16000000UL
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
#include "../MCAL/TWI/TWI_interface.h"
#include "../MCAL/WDT/WDT_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../HAL/RTC/RTC_interface.h"
#include "../HAL/Fingerprint/Fingerprint_interface.h"
#include "../HAL/LM35/LM35_interface.h"

#include <util/delay.h>

// Function prototypes
u8 registerFingerprint(void);
u8 searchFingerprint(void);
void app(void);

// Main function
int main(void) {
    // Enable global interrupts
    GIE_enable();
    // Initialize USART communication
    USART_Init();
    // Initialize LCD
    H_LCD_void_Init();
    // Initialize Fingerprint Sensor
    FingerPS_Init();
    _delay_ms(500);

    u8 key;
    u8 status;

    // Main loop
    while (1) {
        // Display welcome screen
        H_LCD_void_clearScreen();
        welcomeScreen();

        // Get the pressed key from the keypad
        key = KEYPAD_getPressedKey();

        // Check the pressed key and perform corresponding actions
        if(key == 1){
            // Register a new fingerprint
            status  = registerFingerprint();
            if(status == 0){
                H_LCD_void_clearScreen();
                H_LCD_void_sendString(" New User Added ");
                FingerPS_AuraLedControl(LIGHT_ALWAYS_ON,255,BLUE_COLOR,100);
                _delay_ms(2000);
            } else {
                H_LCD_void_clearScreen();
                H_LCD_void_sendString(" Error Pls Try Again");
                FingerPS_AuraLedControl(LIGHT_ALWAYS_ON,255,RED_COLOR,100);
                _delay_ms(2000);
                FingerPS_AuraLedControl(LIGHT_ALWAYS_OFF,255,RED_COLOR,100);
            }
        } else if(key == 2){
            // Search for a fingerprint
            status = searchFingerprint();
            if(status == 0){
                H_LCD_void_clearScreen();
                H_LCD_void_sendString("Hello User");
                FingerPS_AuraLedControl(LIGHT_ALWAYS_ON,255,BLUE_COLOR,100);
                _delay_ms(2000);
                // Perform application actions
                app();
            } else {
                H_LCD_void_clearScreen();
                H_LCD_void_sendString(" Error Pls Try Again");
                FingerPS_AuraLedControl(LIGHT_ALWAYS_ON,255,RED_COLOR,100);
                _delay_ms(2000);
                FingerPS_AuraLedControl(LIGHT_ALWAYS_OFF,255,RED_COLOR,100);
            }
        } else if(key == 3){
            // Empty Fingerprint Flash
            status = FingerPS_EmptyLibrary();
            if(status == 0){
                H_LCD_void_clearScreen();
                H_LCD_void_sendString("Flash Erased");
                _delay_ms(2000);
            } else {
                H_LCD_void_clearScreen();
                H_LCD_void_sendString(" Error Pls Try Again");
                FingerPS_AuraLedControl(LIGHT_ALWAYS_ON,255,RED_COLOR,100);
                _delay_ms(2000);
                FingerPS_AuraLedControl(LIGHT_ALWAYS_OFF,255,RED_COLOR,100);
            }
        }
    }
    return 0;
}

// Function to register a fingerprint
u8 registerFingerprint(void){
    u8 key;
    H_LCD_void_clearScreen();
    H_LCD_void_sendString("Place your finger");
    FingerPS_AuraLedControl(BREATHING_LIGHT,255,BLUE_COLOR,100);
    key = FingerPS_genImg();
    while(key!= 0x00){
        key = FingerPS_genImg();
    }

    key=FingerPS_convertImg2CharFile(T_BUFFER_1);

    key = FingerPS_genImg();

    key=FingerPS_convertImg2CharFile(T_BUFFER_2);

    key=FingerPS_genTemplate();

    key=FingerPS_strTemplate(T_BUFFER_1,1);

    return key;
}

// Function to search for a fingerprint
u8 searchFingerprint(void){
    u8 key;
    H_LCD_void_clearScreen();
    H_LCD_void_sendString("Place your finger");
    FingerPS_AuraLedControl(BREATHING_LIGHT,255,BLUE_COLOR,100);
    key = FingerPS_genImg();
    while(key!= 0x00){
        key = FingerPS_genImg();
    }

    key=FingerPS_convertImg2CharFile(T_BUFFER_1);

    key = FingerPS_genImg();

    key=FingerPS_convertImg2CharFile(T_BUFFER_2);

    key=FingerPS_genTemplate();

    key =FingerPS_searchFinger(T_BUFFER_1, 1, 4);

    _delay_ms(1000);
    return key;
}

// Function to display the welcome screen
void welcomeScreen(void){
    H_LCD_void_clearScreen();
    H_LCD_void_sendString("1- Register ");
    H_LCD_void_sendString("2- Login");
    H_LCD_void_gotoXY(2,4);
    H_LCD_void_sendString("3- Empty FP Flash");
    FingerPS_AuraLedControl(FLASHING_LIGHT,255,PURPLE_COLOR,100);
}

// Application function
void app(void){
    // Configuration of LED pins
    DIO_Config ledsPins[] = {
        {DIO_PORTA, DIO_PIN5, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
        {DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT, DIO_PIN_HIGH},
    };

    // Set LED pin directions and initial values
    DIO_U8SetPinDirection(&ledsPins[0]);
    DIO_U8SetPinDirection(&ledsPins[1]);
    u8 key;
    H_LCD_void_clearScreen();
    H_LCD_void_gotoXY(1,0);
    H_LCD_void_sendString("1- LEDS ON ");
    H_LCD_void_gotoXY(2,4);
    H_LCD_void_sendString("2- LEDS OFF");
    
    // Loop for LED control
    while(1){
        // Get the pressed key from the keypad
        key = KEYPAD_getPressedKey();
        if(key == 1){
            // Turn ON LEDs
            for (u8 i = 0; i < 2; i++) {
                ledsPins[i].value = DIO_PIN_HIGH;
                DIO_U8SetPinValue(&ledsPins[i]);
            }
        } else if(key
