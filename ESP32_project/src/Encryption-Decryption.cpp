#include <mbedtls/aes.h>
#include <Arduino.h>
#include <mbedtls/platform.h>

u_char ciphertext[16] = {};
u_char KEY1[16] = {};
u_char plaintext[16] = {} ;
u_char plain[16] = "FUCKYOU AESFuCK";

mbedtls_aes_context aes;

void setKEY(uint64_t key) {
    mbedtls_aes_init(&aes);

    String keystr(key);
    int c = 0 , len = keystr.length();

    while(c != 16) {
        KEY1[c] = keystr[c % len];

        c++;
    }

    mbedtls_aes_setkey_enc(&aes , KEY1 , 128);
}


String encMsg(String text) {
    mbedtls_aes_crypt_ecb(&aes , MBEDTLS_AES_ENCRYPT , plain , ciphertext);
    String ctext(ciphertext , 16);
    return ctext;

    // mbedtls_aes_free(&aes);
}


String decMsg(String text) {
    mbedtls_aes_decrypt(&aes , ciphertext , plaintext);
    String ptext(plaintext , 16);
    return ptext;
}
