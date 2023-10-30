/*
 * SPI_private.h
 *
 * Created: 10/30/2023 11:25:09 AM
 *  Author: Ziad
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/*************************************************************************************/
/* 								SPI REGISTERS										 */
/*************************************************************************************/

typedef struct {
	u8 SPCR;
	u8 SPSR;
	u8 SPDR;
}Spi_Type;

#define SPI ((volatile Spi_Type *) 0x2D)

//SPI Control Register – SPCR bits
#define SPIE 7
#define SPE	 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

//SPI Status Register –SPSR
#define SPIF  7
#define WCOL  6
#define SPI2X 0





#endif /* SPI_PRIVATE_H_ */