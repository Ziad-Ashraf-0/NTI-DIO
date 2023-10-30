/*
 * Ultrasonic_interface.h
 *
 * Created: 10/30/2023 10:27:28 AM
 *  Author: Ziad
 */ 


#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_


/*
 *  Description :1- Initialize the ICU driver as required.
                 2- Setup the ICU call back function.
                 3- Setup the direction for the trigger pin as output pin through the GPIO driver.
     Inputs      : None
     Return      : None
 * */
void Ultrasonic_init(void);

/*
• Description : Send the Trigger pulse to the ultrasonic.
• Inputs      : None
• Return      : None
 */

void Ultrasonic_Trigger(void);

/*
• Description : 1- Send the trigger pulse by using Ultrasonic_Trigger function.
                2- Start the measurements by the ICU from this moment.
• Inputs      : None
• Return      : The measured distance in cm
 */

u16 Ultrasonic_readDistance(void);


#endif /* ULTRASONIC_INTERFACE_H_ */