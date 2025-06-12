#include "Header.h"

using namespace std;

mpz_class discrete_log(const mpz_class& g, const mpz_class& h, const mpz_class& p) {
    mpz_class result = 0;
    mpz_class current = 1;

    mpz_class max_tries = 1000000;

    for (result = 0; result < max_tries; ++result) {
        if (current == h) {
            return result;
        }
        current = (current * g) % p;
    }

    throw runtime_error("Дискретный логарифм не найден");
}

mpz_class elgamal_attack(const vector<pair<mpz_class, mpz_class>>& ciphertexts,
    const vector<int>& known_plaintexts,
    const mpz_class& p,
    const mpz_class& g) {
    if (ciphertexts.size() != known_plaintexts.size() || ciphertexts.empty()) {
        throw invalid_argument("Неверные данные для атаки");
    }

    size_t idx = 0;
    for (; idx < known_plaintexts.size(); ++idx) {
        if (known_plaintexts[idx] != 0) break;
    }

    if (idx == known_plaintexts.size()) {
        throw runtime_error("в тексте нет данных");
    }

    mpz_class u = ciphertexts[idx].first;
    mpz_class v = ciphertexts[idx].second;
    mpz_class m = known_plaintexts[idx];

    mpz_class m_inv;
    if (!mpz_invert(m_inv.get_mpz_t(), m.get_mpz_t(), p.get_mpz_t())) {
        throw runtime_error("Не удалось найти обратный элемент для m");
    }
    mpz_class yk = (v * m_inv) % p;

    mpz_class k;
    try {
        k = discrete_log(g, u, p);
        cout << "Найдено k: " << k << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка при нахождении k: " << e.what() << endl;
        throw;
    }

    mpz_class phi = p - 1;
    mpz_class k_inv;

    if (!mpz_invert(k_inv.get_mpz_t(), k.get_mpz_t(), phi.get_mpz_t())) {
        throw runtime_error("k и g(p) не взаимно просты");
    }

    mpz_class y = cool_pow(yk, k_inv, p);

    mpz_class x;
    try {
        x = discrete_log(g, y, p);
        cout << "Найдено x: " << x << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка при нахождении x: " << e.what() << endl;
    }

    return x;
}
