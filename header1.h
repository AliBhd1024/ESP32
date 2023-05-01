#include <cmath>

typedef uint32_t ull;

ull power_mod(ull a , ull b , ull mod) {
    ull res = 1;

    while(b) {
        a %= mod;

        if(b & 1) {
            res = (res * a) %mod;
        }

        a *= a;

        b >>= 1;
    }

    return res;
}