#ifndef __ENCRYPTION_DECRYPTION_H
#define __ENCRYPTION_DECRYPTION_H

#include <Arduino.h>

void setKEY(uint64_t key);

String encMsg(String text);
String decMsg(String text);

// String decryptMessage(const String encryptedMessage);

// void encryptMessageECB(unsigned char* message);

// void kee(unsigned char* key);

#endif // __ENCRYPTION_DECRYPTION_H
