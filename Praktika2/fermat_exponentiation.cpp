#include "Header.h"

bool is_prime(mpz_class p) {
	if (p <= 1) return false;
	if (p == 2) return true;
	for (mpz_class i = 2; i < sqrt(p) + 1; i++) {
		if (p % i == 0) return false;
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
