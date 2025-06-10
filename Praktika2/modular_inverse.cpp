#include "Header.h"

mpz_class mod_inverse(mpz_class c, mpz_class m) {
    mpz_class gcd, x, y;
    tie(gcd, x, y) = extended_gcd(c, m);

    if (gcd != 1) {
        throw runtime_error("Обратного элемента не существует: c и m должны быть взаимно просты");
    }
    else {
        return (x % m + m) % m;
    }
}