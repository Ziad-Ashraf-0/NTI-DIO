/*
 * LM35_prog.c
 *
 * Created: 11/5/2023 6:22:05 PM
 *  Author: zashr
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_config.h"
#include "LM35_interface.h"






/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
u8 H_LM35_U8_getTemperature(void)
{
	u8 temp_value = 0;

	u16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_getDigitalValueSynchNonBlocking(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (u8)(((u32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}