#include <Arduino.h>
#include "ESP_NOW_.h"
#include "Diffie-Hellman.h"
#include "Encryption-Decryption.h"

MAC_ADDRESS bobMacAddress = {0xEC, 0x62, 0x60, 0x9C, 0xE7, 0x4C};         // peer's mac

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
  }

  else 
  {
    Serial.println("\n ** Diffie-Hellman failed **\n");
    Serial.println(getParameters());
    while(1);                                                                              // stop program if DH failed
  }
}

void loop() {
    while(Serial.available() == 0);                                                       // wait until something is entered

    String message = Serial.readString();                                                 

    broadCast(encryptMessage(message), bobMacAddress);
}