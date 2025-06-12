#include "Header.h"

tuple<mpz_class, mpz_class, mpz_class> extended_gcd(mpz_class a, mpz_class b) {
    if (a == 0) {
        return make_tuple(b, 0, 1);
    }

    mpz_class gcd, u1, v1;
    tie(gcd, u1, v1) = extended_gcd(b % a, a);

    mpz_class u = v1 - (b / a) * u1;
    mpz_class v = u1;

    return make_tuple(gcd, u, v);
}

mpz_class find_d(mpz_class c, mpz_class m) {
    mpz_class gcd, u, v;
    tie(gcd, u, v) = extended_gcd(c, m);

    if (gcd != 1) {
        throw runtime_error("Решение не существует: c и m должны быть взаимно просты");
    }
    else {
        return (u % m + m) % m;
    }
}
