#include "bigNum.c"

int main() {
    srand(time(0));
    buffer a, b, p;
    generateBigNum(a);
    generateBigNum(b);
    printBigNum(a);
    printBigNum(b);
    powBigNumMod(a,b,prime,p);
    printBigNum(p);

    return 0;
}