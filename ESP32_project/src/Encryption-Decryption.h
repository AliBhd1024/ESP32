#ifndef __ENCRYPTION_DECRYPTION_H
#define __ENCRYPTION_DECRYPTION_H

#include <Arduino.h>

void setKEY(uint32_t key);

void AES_Encrypt(unsigned char* message);

// String decryptMessage(const String encryptedMessage);

// void encryptMessageECB(unsigned char* message);

// void kee(unsigned char* key);

#endif // __ENCRYPTION_DECRYPTION_H