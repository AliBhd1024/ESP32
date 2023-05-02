#include "util.h"
#include <string.h>
#include <iostream>

// using namespace std;

// declaring global variables
ull generator = 0, prime = 0, sharedKey = 0, publicKey = 0, privateKey = 0, secretKey = 0; // they are set to 0 for error handling
std::string initPacket = "", sharedPacket = ""; // thay are set to "" for error handling 
bool DHIsDone = false;


// it initializes diffie hellman
void initDH() {
    generator = generateRandom();
    prime = 857328397;
    initPacket =  std::to_string(generator) + std::to_string(prime); // I is flag for initPacket
}

// it generates publicKey and privateKey
void generateKeys() {
  privateKey = generateRandom();

  publicKey = generateKey(generator, privateKey, prime);
}

// it defines sharedPacket for sharing publicKey
void shareKey() {
  if (publicKey != -1) sharedPacket = "S " + std::to_string(publicKey); // S is flag for sharedPacket
}

// it gets another perons's public key
void getSharedKey(string packet) {

}

// it generates secret key
void generateSecretKey() {
  secretKey = generateKey(sharedKey, privateKey, prime);
  DHIsDone = true;
}
 
string getInitPacket() {
  return initPacket;
}

string getSharedPacket() {
  return sharedPacket;
}

ull getSharedKey() {
  return sharedKey;
}

ull getPrivateKey() {
  return privateKey;
}

ull getPublicKey() {
  return publicKey;
}

ull getSecretKey() {
  return secretKey;
}