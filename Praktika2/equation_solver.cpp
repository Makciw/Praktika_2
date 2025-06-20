#include "Header.h"

int extended_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}