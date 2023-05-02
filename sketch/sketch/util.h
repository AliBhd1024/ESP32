#include <cstdlib>
#include <cstdint>

#define MAX_RAND 4294967295

typedef uint32_t ull;

using namespace std;

ull powerMode(ull base, ull exp, const ull mod) {
    ull res = 1;
    while(exp) {
        base %= mod;
        if(exp & 1) {
            res = (res * base) % mod;
        } base *= base;
        exp >>= 1;
    } return res;
}

// privateKey , generator
ull generateRandom() {
    return (rand() * rand()) % MAX_RAND;
}

// publicKey, secretKey
ull generateKey(ull base, ull exp, const ull mod) {
    return (powerMode(base, exp, mod));
}