#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define NUMBER_SIZE 200000
#define  BUFFER_SIZE NUMBER_SIZE / 301

typedef uint64_t key_part;
typedef key_part buffer[BUFFER_SIZE];