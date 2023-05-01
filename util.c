#include <stdlib.h>
#include <stdint.h>

#define MAX_RAND 4294967295

typedef uint32_t ull;

ull powerMode(ull base, ull exp, const ull mod) {
    ull res = 1;
    while(exp) {
        base %= mod;
        if(exp & 1) {
            res = (res * base) % mod;
        } base *= base
        exp >>= 1;
    } return res;
}


static ull generateRandom() {
    return (rand() * rand()) % MAX_RAND;
}

static ull generateKey(ull base, ull exp, const ull mod) {
    return (powerMode(base, exp, mod));
}