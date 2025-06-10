#ifndef HEADER_H  
#define HEADER_H

#pragma warning(disable:4146)
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <locale.h>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <fstream>
#include <stdexcept>
#include <map>

using namespace std;
//1
mpz_class Fermat(mpz_class x, mpz_class a, mpz_class p);
mpz_class decomposition(vector<int> binary, mpz_class a, mpz_class p);
vector<int> to_2(mpz_class x);
void checkInput(mpz_class a, mpz_class x, mpz_class p);

//2
mpz_class find_d(mpz_class c, mpz_class m);
tuple<mpz_class, mpz_class, mpz_class> extended_gcd(mpz_class a, mpz_class b);

//3
mpz_class mod_inverse(mpz_class c, mpz_class m);

//4
void Read(string filee, vector<int>& elem);
void Encryption_w(string filee, vector<pair<mpz_class, mpz_class>>& elem);
void Decryption_w(string filee, vector<char>& elem);
tuple<vector<pair<mpz_class, mpz_class>>, mpz_class, vector<mpz_class>> encryption(vector<int>& letters);
vector<char> decryption(vector<pair<mpz_class, mpz_class>>& encryp_letters, mpz_class p, mpz_class x);

//5
int extended_gcd(int a, int b, int& x, int& y);

//6
mpz_class elgamal_attack(const vector<pair<mpz_class, mpz_class>>& ciphertexts,
    const vector<int>& known_plaintexts,
    const mpz_class& p,
    const mpz_class& g);
mpz_class cool_pow(mpz_class base, mpz_class exp, mpz_class mod);
#endif