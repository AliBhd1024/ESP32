#ifndef __ENCRYPTION_DECRYPTION_H
#define __ENCRYPTION_DECRYPTION_H

#include <Arduino.h>

void setKEY(uint32_t key);

String encryptMessage(const String plainTextMessage);

String decryptMessage(const String encryptedMessage);

#endif // __ENCRYPTION_DECRYPTION_H