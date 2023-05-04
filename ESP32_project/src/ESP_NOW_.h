#ifndef __ESP_NOW_H
#define __ESP_NOW_H

// #define ALICE {0xEC, 0x62, 0x60, 0x94, 0xC7, 0xA4}
// #define BOB   {0xEC, 0x62, 0x60, 0x9C, 0xE7, 0x4C}

#include <Arduino.h>

typedef uint8_t MAC_ADDRESS[6];

void broadCast(const String &message, MAC_ADDRESS macAddr);                   // send message to macAddr

String getLastReceivedPacket();                                               // get last received packet
 
void initESPNOW();                                                            // initialize ESP_NOW

#endif // __ESP_NOW_H