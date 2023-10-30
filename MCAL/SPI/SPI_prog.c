/*
 * SPI_prog.c
 *
 * Created: 10/30/2023 11:23:14 AM
 *  Author: Ziad
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"



/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_init(const SPI_Config* config) 
{	
    /************************** SPCR Description **************************
     * SPE     = 1 Enable SPI Driver
     * DORD    = 0 Transmit the MSB first
     * MSTR    = 1 Enable Master
     * CPOL    = 0 SCK is low when idle
     * CPHA    = 0 Sample Data with the raising edge (dont care)
     * SPR1:0  = 00 Choose SPI clock = Fosc/4
     ***********************************************************************/
	SPI->SPCR = (1<<SPE) | (config->mode_selct << MSTR) | (config->bit_order << DORD) | (config->idle << CPOL ) | (config->freq);

	/* Clear the SPI2X bit in SPSR to Choose SPI clock = Fosc/4 */
	SPI->SPSR = config->speed;
}


/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
void SPI_sendReceiveByte(u8 copy_u8ch, u8* ch)
{
	/* Initiate the communication and send data by SPI */
	SPI->SPDR = copy_u8ch;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while(BIT_IS_CLEAR(SPI->SPSR,SPIF)){}

	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	*ch = SPI->SPDR;
}