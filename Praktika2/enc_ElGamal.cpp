#include "Header.h"

void Read(string file_name, vector<int>& letters) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Не удалось открыть файл " << file_name << endl;
    }
    char letter;
    while (file.get(letter)) {
        unsigned char byte = static_cast<unsigned char>(letter);
        letters.push_back(static_cast<int>(byte));
    }

    file.close();
}

void Encryption_w(string file_name, vector<pair<mpz_class, mpz_class>>& letters) {
    ofstream file(file_name);
    if (!file) {
        cerr << "Не удалось открыть файл " << file_name << endl;
    }
    for (auto i : letters) {
        file << "(" << i.first << " " << i.second << ") ";
    }

    file.close();
}

void Decryption_w(string file_name, vector<char>& letters) {
    ofstream file(file_name);
    if (!file) {
        cerr << "Не удалось открыть файл " << file_name << endl;
    }
    for (auto i : letters) {
        file << i;
    }

    file.close();
}

mpz_class large_prime(unsigned int bits) {
    mpz_class prime;
    gmp_randstate_t state;

    gmp_randinit_default(state);
    unsigned long seed = static_cast<unsigned long>(time(nullptr));
    gmp_randseed_ui(state, seed);
    mpz_urandomb(prime.get_mpz_t(), state, bits);  
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());

    gmp_randclear(state);


    return prime;
}

mpz_class cool_pow(mpz_class base, mpz_class exp, mpz_class mod) {
    mpz_class result;
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
    return result;
}

set<mpz_class> get_prime_factors(mpz_class n) {
    set<mpz_class> factors;
    mpz_class i = 2;
    while (i * i <= n) {
        while (n % i == 0) {
            factors.insert(i);
            n /= i;
        }
        i++;
    }
    if (n > 1) factors.insert(n);
    return factors;
}

bool is_primitive_root(const mpz_class& g, const mpz_class& p, const set<mpz_class>& factors) {
    mpz_class phi = p - 1, res;
    for (const auto& q : factors) {
        mpz_class exp = phi / q;
        mpz_powm(res.get_mpz_t(), g.get_mpz_t(), exp.get_mpz_t(), p.get_mpz_t());
        if (res == 1) return false;
    }
    return true;
}

mpz_class primitive_root(const mpz_class& p) {
    mpz_class phi = p - 1;
    set<mpz_class> factors = get_prime_factors(phi);

    for (mpz_class g = 2; g < p; ++g) {
        if (is_primitive_root(g, p, factors)) {
            return g;
        }
    }

    throw runtime_error("Не удалось найти примитивный корень по модулю p");
}

mpz_class generate_x(const mpz_class& p) {
    gmp_randclass rand_gen(gmp_randinit_mt);
    rand_gen.seed(time(nullptr));

    mpz_class max = p - 2;
    mpz_class x;

    x = rand_gen.get_z_range(max);

    return x + 1;
}

tuple<vector<pair<mpz_class, mpz_class>>, mpz_class, vector<mpz_class>> encryption(vector<int>& letters) {
    unsigned int bits = 15;
    mpz_class p = large_prime(bits);
    mpz_class g = primitive_root(p);
    mpz_class x = generate_x(p);
    mpz_class y = cool_pow(g, x, p);
    vector<pair<mpz_class, mpz_class>> encryp_letters;
    mpz_class k = generate_x(p);
    for (auto m : letters) {
        mpz_class u = cool_pow(g, k, p);
        mpz_class v = cool_pow(y, k, p);
        v = (m * v) % p;
        encryp_letters.push_back(make_pair(u, v));
    }
    vector<mpz_class> par = { x, g, y };
    return make_tuple(encryp_letters, p, par);
}

vector<char> decryption(vector<pair<mpz_class, mpz_class>>& encryp_letters, mpz_class p, mpz_class x) {
    vector<char> decip_letters;
    mpz_class m;
    for (auto i : encryp_letters) {
        m = cool_pow(i.first, p - 1 - x, p);
        m = (i.second * m) % p;
        decip_letters.push_back(static_cast<char>(m.get_si()));
    }
    return decip_letters;
}
