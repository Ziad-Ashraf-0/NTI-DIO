/*
 * TWI_prog.c
 *
 * Created: 10/30/2023 9:16:22 PM
 *  Author: zashr
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h" 
#include "TWI_config.h"
#include "TWI_interface.h"
#include "TWI_private.h"



void M_TWI_void_init(const TWI_Config *Config_Ptr)
{
	//put 2 in case of 8 mhz 400 bit
	//put 32 in case of 8mhz 100 bit
   // TWI->TWBR = Config_Ptr->twbr;
    TWI->TWBR = 32;
	TWI->TWSR = 0;
	
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWI->TWAR = Config_Ptr->myAddress << 1 ; // my address = 0x01 :)
	
    TWI->TWCR = (1<<TWEN); /* enable TWI */
}

void M_TWI_void_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWI->TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWI->TWCR,TWINT));
}

void M_TWI_void_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWI->TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void M_TWI_void_writeByte(u8 data)
{
    /* Put data On TWI data Register */
    TWI->TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWI->TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWI->TWCR,TWINT));
}

void M_TWI_void_readByteWithACK(u8 * ptr)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWI->TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWI->TWCR,TWINT));
    /* Read Data */
    *ptr = TWI->TWDR;
}

void M_TWI_void_readByteWithNACK(u8 * ptr)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWI->TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWI->TWCR,TWINT));
    /* Read Data */
    *ptr = TWI->TWDR;
}

void M_TWI_void_getStatus(u8 * status)
{
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    *status = TWI->TWSR & 0xF8;
}
