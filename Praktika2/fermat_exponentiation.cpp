#include "Header.h"

set<mpz_class> canonical_dec(mpz_class p_num) {
    set<mpz_class> divisors;
    if (p_num == 1) return divisors;

    mpz_class prime_num = p_num;
    mpz_class i = 2;
    while (i * i <= prime_num) {
        if (prime_num % i == 0) {
            divisors.insert(i);
            while (prime_num % i == 0) prime_num /= i;
        }
        i++;
    }
    if (prime_num > 1) divisors.insert(prime_num);
    return divisors;
}

bool is_prime(mpz_class prime_num, int t = 6) {
    if (prime_num == 2) return true;
    if (prime_num < 2 || prime_num % 2 == 0) return false;

    uniform_int_distribution<int> aj(2, prime_num.get_ui() - 1);

    vector<int> a;
    set<mpz_class> prime_nums = canonical_dec(prime_num - 1);

    while (a.size() < t) {
        int a_n = aj(gen);
        if (count(a.begin(), a.end(), a_n) == 0) {
            a.push_back(a_n);
            if (cool_pow(a_n, prime_num - 1, prime_num) != 1) {
                return false;
            }
        }
    }

    for (auto q : prime_nums) {
        bool found = false;
        for (auto i : a) {
            if (cool_pow(i, (prime_num - 1) / q, prime_num) != 1) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

bool Fermat_cond(mpz_class a, mpz_class& p) {
    return is_prime(p) && (a % p != 0);
}

mpz_class Fermat(mpz_class x, mpz_class a, mpz_class p) {
	if (!Fermat_cond(a, p)) throw runtime_error("Ошибка: нарушение условий теоремы Ферма (a и p должны быть взаимно просты)");
	mpz_class result;
	x %= (p - 1);
	mpz_powm_sec(result.get_mpz_t(), a.get_mpz_t(), x.get_mpz_t(), p.get_mpz_t());
	return result;
}

vector<int> to_2(mpz_class x) {
	vector<int> binary;
	mpz_class n = x;

	while (n > 0) {
		binary.push_back(mpz_odd_p(n.get_mpz_t()) ? 1 : 0);
		n /= 2;
	}
	return binary;
}

mpz_class decomposition(vector<int> binary, mpz_class a, mpz_class p) {
	mpz_class result = 1;
	mpz_class base = a % p;

	for (int bit : binary) {
		if (bit == 1) {
			result = (result * base) % p;
		}
		base = (base * base) % p;
	}
	return result;
}

void checkInput(mpz_class a, mpz_class x, mpz_class p) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw runtime_error("Ошибка: введены некорректные данные (ожидаются целые числа)");
	}
	if (p <= 1 || !is_prime(p)) {
		throw runtime_error("Ошибка: p должно быть простым числом > 1");
	}
	if (a % p == 0) {
		throw runtime_error("Ошибка: a не должно делиться на p (условие теоремы Ферма)");
	}
	if (x < 0) {
		throw runtime_error("Ошибка: степень x не может быть отрицательной");
	}
}
