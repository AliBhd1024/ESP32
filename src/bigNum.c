#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 4
#define END_BUFFER -1

typedef int8_t digit;
typedef digit buffer[BUFFER_SIZE + 1];

buffer prime = {8,1,9,1} ;

static void generateBigNum(buffer b) {
    for(int i = 1; i < BUFFER_SIZE; i++)
        b[i] = rand() % 10;
    b[0] = 1;
    b[BUFFER_SIZE] = -1;
}

static void initializeBigNum(buffer b) {
    for(int i = 0; i < BUFFER_SIZE; i++)
        b[i] = 0;
    b[BUFFER_SIZE] = -1;
}

void getOne(buffer b) {
    for(int i = 0; i < BUFFER_SIZE-1; i++) {
        b[i] = 0;
    } b[BUFFER_SIZE-1] = 1;
    b[BUFFER_SIZE] = -1;
}

static int isZeroBigNum(const buffer b) {
    for(int i = 0; i < BUFFER_SIZE; i++)
        if(b[i] != 0) return 0;
    return 1;
}

static void printBigNum(const buffer b) {
    for(size_t i = 0; i < BUFFER_SIZE; i++)
        printf("%d",b[i]);
    printf("\n");
}

static void copyBigNum(const buffer b, buffer res) {
    for(int i = 0; i < BUFFER_SIZE; i++)
        res[i] = b[i];
    res[BUFFER_SIZE] = -1;
}

static void reverseBigNum(buffer b) {
    for(int i = 0; i < BUFFER_SIZE/2; i++) {
        digit temp = b[i];
        b[i] = b[BUFFER_SIZE - i - 1];
        b[BUFFER_SIZE - i - 1] = temp;
    }
}

static int compareBigNum(const buffer a, const buffer b) {
    // a > b : 1 - a = b : 0 - a < b : -1
    int i = 0, res = 0;
    while((a[i] != END_BUFFER) && (b[i] != END_BUFFER)) {
        if(a[i] > b[i]) {
            res = 1;
            break;
        } else if(a[i] < b[i]) {
            res = -1;
            break;
        } i++;
    } return res;
}

static void subBigNum(const buffer a, const buffer b, buffer res) {
    int compare = compareBigNum(a,b);
    if(compare == -1) { // TODO = raise error
        return;
    } else if(compare == 0) {
        initializeBigNum(res);
        return;
    } for(int i = 0; i < BUFFER_SIZE; i++) {
        res[i] = a[i] - b[i];
    } for(int i = BUFFER_SIZE - 1; i >= 0; i--) {
        if(res[i] < 0) {
            res[i] += 10;
            res[i-1]--;
        }
    } res[BUFFER_SIZE] = -1;
}

static void modBigNum(const buffer a, const buffer mod, buffer res) {
    copyBigNum(a,res);
    while(compareBigNum(res,mod) == 1) {
        subBigNum(res,mod,res);
    }
}

static void addBigNumMod(const buffer a, const buffer b, const buffer mod, buffer res) {
    for(int i = 0; i < BUFFER_SIZE; i++) {
        res[i] = a[i] + b[i];
    } for(int i = BUFFER_SIZE-1; i >= 0; i--) {
        res[i-1] += res[i] / 10;
        if(i!=0) res[i] %= 10;
    } modBigNum(res, mod,res);
}

static void mulBigNumMod(const buffer a, const buffer b, const buffer mod, buffer res) {
    buffer one, m;
    getOne(one);
    copyBigNum(a,res);
    copyBigNum(b,m);
    subBigNum(m,one,m);
    while(!isZeroBigNum(m)) {
        addBigNumMod(a,res,prime,res);
        subBigNum(m,one,m);
    }
}

static void powBigNumMod(const buffer a, const buffer b, const buffer mod, buffer res) {
    buffer one, e,t;
    getOne(one);
    copyBigNum(b,e);
    copyBigNum(a,res);
    subBigNum(e,one,e);
    while(!isZeroBigNum(e)) {
        mulBigNumMod(a,res,prime,t);
        copyBigNum(t,res);
        subBigNum(e,one,e);
    }

}
