/*
 * TWI_interface.h
 *
 * Created: 10/30/2023 9:16:44 PM
 *  Author: zashr
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef struct
{
	u8 twbr;
	u8 myAddress;
}TWI_Config;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define BIT_RATE_400 12
#define BIT_RATE_100 72
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void M_TWI_void_init(const TWI_Config *Config_Ptr);
void M_TWI_void_start(void);
void M_TWI_void_stop(void);
void M_TWI_void_writeByte(u8 data);
void M_TWI_void_readByteWithACK(u8 * ptr);
void M_TWI_void_readByteWithNACK(u8 * ptr);
void M_TWI_void_getStatus(u8 * status);



#endif /* TWI_INTERFACE_H_ */