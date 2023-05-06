#ifndef __DIFFIE_HELLMAN_H
#define __DIFFIE_HELLMAN_H

#include <Arduino.h>
#include "ESP_NOW_.h"

// #define SENDER_DH

/*
                                                  <Diffie-Hellman protocol steps>
             **sender**                                                                             **receiver**
  1.  generating g and p randomly                                                                                    listening
  2.  sending g and p to receiver                     ------- initPacket ----->                           receiving initPacket
  3.  generating privateKey randomly = PrKS                                              generating privateKey randomly = PrKR
  4.  generating publicKey = (g ^ PrKS) % p = PuKS                                generating publicKey = (g ^ PrKR) % p = PuKR
  5.  sending PuKS to receiver  ----- sharedPacket ---->                   <---- sharedPacket -----     sending PuKR to sender
  6.  receiving receiver's publicKey = SKS                                                  receiving sender's publicKey = SKR
  7.  generating secretKey = (SKS ^ PrKS) % p                                          generating secretKey = (SKR ^ PrKR) % p

                                     note:         *!* This File Is Sender's File *!*

*/

int DHProtocol(MAC_ADDRESS macAddr);  // macAddr = peer you want to exchange key , it returns 0 if everything is ok otherwise it returns -1

String getParameters();

#endif // __DIFFIE_HELLMAN_H