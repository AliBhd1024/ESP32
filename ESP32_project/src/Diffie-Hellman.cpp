#include <Arduino.h>
#include "ESP_NOW_.h"                   // to send and receive packet
#include "Encryption-Decryption.h"      // to save secret KEY

#define MAX_RAND 4294967295
#define SENDER_DH                       // *!* this file is sender's file *!* note : for receiver file remove this macro

typedef uint32_t ui;                    // unsigned int

String parameters = "\0";

/* Util Functions */

ui powerMode(ui base, ui exp, const ui mod)
// (base ^ exp) % mod
{
    ui res = 1;
    while(exp) {
        base %= mod;
        if(exp & 1) {
            res = (res * base) % mod;
        } base *= base;
        exp >>= 1;
    } return res;
}

ui generateRandom() 
// privateKey , generator
{
    return (rand() * rand()) % MAX_RAND;
}

ui generateKey(ui base, ui exp, const ui mod)
// publicKey , secretKey
{
    return (powerMode(base, exp, mod));
}

/* End Util Functions */

int DHProtocol(MAC_ADDRESS macAddr) {
    int result = 0;

    Serial.println("\n** Diffie-Hellman started **");

    #ifdef SENDER_DH
    /* this part is for sender */
        Serial.println("\n** Role : Sender **");

        ui generator = generateRandom();
        ui prime = 857328397;                                                                           // TODO : implement a randomPrime func
    
        String generatorStr = std::to_string(generator).c_str();
        String primeStr = std::to_string(prime).c_str();
        String initPacket = "<diffie-hellman/initPacket>\n" + generatorStr + "\n" + primeStr + "\n";    // <diffie-hellman/initPacket> is flag for initPacket , TODO : packet could be better

        broadCast(initPacket, macAddr);
    /* ---------------------- */
    #endif
    #ifndef SENDER_DH
    /* this part is for receiver */
        Serial.println("\n** Role : Receiver **");

        String generatorStr = "", primeStr = "", header = "", data = "";                                // split packet  
        int dataCounter = 0;

        while(getLastReceivedPacket() == "\0");

        String initPacket = getLastReceivedPacket();

        Serial.println("\n>> packet received : " + initPacket);

        for(int i = 0; i < initPacket.length(); i++) {
            if(initPacket[i] == '\n') {
                dataCounter++;
                if(dataCounter == 1) header = data;
                else {
                    if(header == "<diffie-hellman/initPacket") {                                       // TODO : what if packet was wrong
                        if(dataCounter == 2) {
                            generatorStr = data;
                        } else if(dataCounter == 3) {
                            primeStr = data;
                        }
                    }
                }
                data = "";
            } else {
                data += initPacket[i];
            }
        }

        ui generator = generatorStr.toInt();
        ui primt = primeStr.toInt();
    /* ---------------------- */
    #endif  

    ui privateKey = generateRandom();
    ui publicKey = generateKey(generator, privateKey, prime);

    String publicKeyStr = std::to_string(publicKey).c_str();
    String sharedPacket = "<diffie-hellman/sharedPacket>\n" + publicKeyStr + "\n";         // <diffie-hellman/sharedPacket> is flag for sharedPacket , TODO : packet could be better

    broadCast(sharedPacket, macAddr);                                                      // TODO : implement RSA or DSA algorithm for this part

    while(getLastReceivedPacket() == "\0");                                                // wait until peer sends packet

    String packet = getLastReceivedPacket(), data = "", header = "", keyStr = "";          // split packet
    int dataCounter = 0;

    Serial.println("\n>> packet received : " + packet);

    for(int i = 0; i < packet.length(); i++) {
        if(packet[i] == '\n') {
            dataCounter++;
            if(dataCounter == 1) header = data;
            else {
                if(header == "<diffie-hellman/sharedPacket>") {                             // TODO : what if packet was wrong
                    if(dataCounter == 2) keyStr = data;
                }
            }
        } else {   
            data += packet[i];
        }
    }

    ui sharedKey = keyStr.toInt();

    ui secretKey = generateKey(sharedKey, privateKey, prime);
    setKEY(secretKey);

    // save parameters for testing if DH failed
    String privateKeyStr = std::to_string(privateKey).c_str();
    String secretKeyStr = std::to_string(secretKey).c_str();
    parameters= "generator = "  + generatorStr  + "\n" +
                "prime = "      + primeStr      + "\n" +
                "privateKey = " + privateKeyStr + "\n" +
                "publicKey = "  + publicKeyStr  + "\n" +
                "sharedKey = "  + keyStr        + "\n" +
                "secretKey = "  + secretKeyStr  + "\n";

    return result;
}

String getParameters() {
    return parameters;
}