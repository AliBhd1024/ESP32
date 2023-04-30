#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define NUMBER_SIZE 200
#define BUFFER_SIZE 2 * (NUMBER_SIZE * 1000) / 301
#define MAX_NUM 10000000000 // 10**10
#define PRIME 2147483647

typedef uint32_t key_part;
typedef key_part buffer[BUFFER_SIZE];

void generatePrivateKey(buffer b) {
    for(int i = 0; i < BUFFER_SIZE; i++)
        b[i] = rand() % (9 * (MAX_NUM / 10)) + MAX_NUM / 10;
}


// (a + b + c + d + ...) * (A + B + C + ...) mod prime
// (a * A mod prime) + (a * B mod prime) + ... + (b * A mod prime) + ... mod prime