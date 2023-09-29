#include "gcd.h"

int Abs(int a) {
    return a > 0 ? a : -a;
}

int gcd(int a,int b) {
    a = Abs(a);
    b = Abs(b);
    while ((a != 0) && (b != 0)) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a + b;
}