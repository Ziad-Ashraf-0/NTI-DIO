/*
 * Fingerprint_private.h
 *
 * Created: 11/4/2023 9:32:44 AM
 *  Author: Ziad
 */ 


#ifndef FINGERPRINT_PRIVATE_H_
#define FINGERPRINT_PRIVATE_H_


static void receiveCallback(u8 data);
static u16 FingerPS_calcCheckSum(u8 *arr , u8 length);

#endif /* FINGERPRINT_PRIVATE_H_ */