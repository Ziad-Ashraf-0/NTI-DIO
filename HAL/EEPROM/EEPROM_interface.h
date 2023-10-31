/*
 * EEPROM_interface.h
 *
 * Created: 10/31/2023 12:01:42 PM
 *  Author: Ziad
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define ERROR 0
#define SUCCESS 1


void EEPROM_Init();
u8 EEPROM_WriteByte(u16 Addr,u8 data);
u8 EEPROM_ReadByte(u16 Addr,u8 *data);



#endif /* EEPROM_INTERFACE_H_ */