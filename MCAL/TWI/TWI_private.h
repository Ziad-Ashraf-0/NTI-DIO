/*
 * TWI_private.h
 *
 * Created: 10/30/2023 9:17:00 PM
 *  Author: zashr
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_


/*************************************************************************************/
/* 								TWI REGISTERS										 */
/*************************************************************************************/

typedef struct {
	u8 TWBR;
	u8 TWSR;
	u8 TWAR;
	u8 TWDR;
	u8 padding[51];
	u8 TWCR;
}Twi_Type;

#define TWI ((volatile Twi_Type *) 0x20)


//TWI Control Register – TWCR

#define TWINT 7
#define TWEA  6
#define TWSTA 5	
#define TWSTO 4	
#define TWWC  3	
#define TWEN  2	
#define TWIE  0


//TWI Status Register – TWSR

#define TWS7   7
#define TWS6   6
#define TWS5   5
#define TWS4   4
#define TWS3   3
#define TWPS1  1
#define TWPS0  0


//TWI Data Register – TWDR

#define TWD7   7
#define TWD6   6
#define TWD5   5
#define TWD4   4
#define TWD3   3
#define TWD2   2
#define TWD1   1	
#define TWD0   0	


//TWI (Slave) Address Register – TWAR

#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0


#endif /* TWI_PRIVATE_H_ */