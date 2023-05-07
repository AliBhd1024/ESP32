#include <Arduino.h>
#include "ESP_NOW_.h"
#include "Diffie-Hellman.h"
#include "Encryption-Decryption.h"

// MAC_ADDRESS bobMacAddress = {0xEC, 0x62, 0x60, 0x9C, 0xE7, 0x4C};         // receiver's mac 
MAC_ADDRESS bobMacAddress = {0xEC, 0x62, 0x60, 0x94, 0xC7, 0xA4};            // sender's mac

void setup() {
  Serial.begin(115200);

  delay(1000);

  // start ESP_NOW protocol
  initESPNOW();

  delay(1000);

  // start diffie hellman protocol
  int result = DHProtocol(bobMacAddress);

  if(result == 0) 
  { 
    Serial.println("\n ** Diffie-Hellman Was Successful **\n");
    Serial.println(getParameters());
  }

  else 
  {
    Serial.println("\n ** Diffie-Hellman failed **\n");
    Serial.println(getParameters());
    while(1);                                                            // stop program if DH failed
  }

  // unsigned char message[]  = "1234567891234567";

  // AES_Encrypt(message);

}

void loop() {
  String message; 
  String recMsg;
  // while(Serial.available() == 0);                                     // wait until something is entered

  //                                                

  // broadCast(encMsg(message), bobMacAddress);                  // TODO : what if length of message was more then 250 chars

  if(Serial.available() != 0) {
    message = Serial.readString();

    broadCast(encMsg(message) , bobMacAddress);
  }

  if(getLastReceivedPacket() != "\0") {
    recMsg = decMsg(getLastReceivedPacket());
    Serial.println(recMsg);
    setLastReceivedPacket("\0");
  }
}
