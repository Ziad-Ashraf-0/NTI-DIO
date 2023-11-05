/*
 * LM35_interface.h
 *
 * Created: 11/5/2023 6:22:18 PM
 *  Author: zashr
 */ 


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 H_LM35_U8_getTemperature(void);



#endif /* LM35_INTERFACE_H_ */