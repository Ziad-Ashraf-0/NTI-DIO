/*
 * SPI_interface.h
 *
 * Created: 10/30/2023 11:24:54 AM
 *  Author: Ziad
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


#define SPI_MASTER 1
#define SPI_SLAVE  0


#define MSB_FIRST 0
#define LSB_FIRST 1

#define IDLE_HIGH 1
#define IDLE_LOW  0

//in case of double speed is divided by 2 so F_4 becomes F_2
#define F_4   0
#define F_16  1
#define F_64  2
#define F_128 3

#define SPEED_NORMAL 0
#define SPEED_DOUBLE 1


typedef struct{
	u8 mode_selct;
	u8 bit_order;
	u8 idle;
	u8 freq;
	u8 speed;	
}SPI_Config;


void SPI_init(const SPI_Config* config);
void SPI_sendReceiveByte(u8 copy_u8ch, u8* ch);

#endif /* SPI_INTERFACE_H_ */