#ifndef CUIHENGRIMOIRE_MATH_HPP
#define CUIHENGRIMOIRE_MATH_HPP
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include "modint.hpp"

namespace cuihengrimoire::math {

template<typename T, typename U>
inline static T power(T x, U n) {
    T result{1};
    while (n > static_cast<U>(0)) {
        if (n%2 == 1) {
            result *= x;
        }
        x *= x;
        n /= 2;
    }
    return result;
}

template<typename, long long> struct combination_t;

template<typename T, T MOD, long long MAX>
struct combination_t<modint_t<T, MOD>, MAX> {
    using value_t = modint_t<T, MOD>;
    std::vector<value_t> fact = std::vector<value_t>(MAX);
    std::vector<value_t> inv_fact = std::vector<value_t>(MAX);

    explicit combination_t() {
        std::vector<T> inv(MAX);
        inv[1] = 1;
        fact[0] = fact[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;
        for (long long i=2; i<MAX; i++) {
            fact[i] = fact[i-1] * i;
            inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
            inv_fact[i] = inv_fact[i-1] * inv[i];
        }
    }

    value_t operator()(value_t n, value_t k) {
        return fact[n.x] * inv_fact[k.x] * inv_fact[(n-k).x];
    }
};

template<typename T>
inline static std::vector<T> divisor(T n) {
    std::vector<T> ret;
    for (T i=1; i*i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i*i != n)
              ret.push_back(n/i);
        }
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

template<typename T, T MAX>
struct prime_table_t {
    using value_t = T;
    std::array<bool, MAX> table;

    explicit prime_table_t() noexcept {
        this->table.fill(true);
        if (MAX >= 0) table[0] = false;
        if (MAX >= 1) table[1] = false;
        for (value_t i=2; i*i <= MAX; i++) {
            if (!this->table[i]) continue;
            for (value_t j=2*i; j<=MAX; j+=i) {
                table[j] = false;
            }
        }
    }

    bool is_prime(value_t n) const {
        assert(0<= n && n < MAX);
        return this->table[n];
    }

    std::unordered_map<value_t, long long> prime_factorization(value_t n) const {
        std::unordered_map<value_t, long long> ret;
        for (value_t i{2}; i*i <= n; i++) {
            if (!is_prime(i)) continue;
            while (n % i == 0) {
                ret[i]++;
                n /= i;
            }
        }
        return ret;
    }
};

}
#endif