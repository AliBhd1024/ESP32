#include <Arduino.h>
#include <AES.h>

AES aes(AESKeyLength::AES_128);
unsigned char KEY[16];

void setKEY(uint64_t key) {
    String keystr(key);
    int c = 0 , len = keystr.length();

    while(c++ != 16) {
        KEY[c] = keystr[c % len];
    }
}


String encMsg(String text) {
    unsigned char parts[text.length()];

    text.toCharArray((char *)parts , text.length());

    String cipher (aes.EncryptECB(parts , text.length() , KEY) , text.length());
    return cipher;
}

String decMsg(String text) {
    unsigned char parts[text.length()];

    text.toCharArray((char *)parts , text.length());

    String cipher (aes.DecryptECB(parts , text.length() , KEY) , text.length());
    return cipher;
}
