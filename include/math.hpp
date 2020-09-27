#ifndef CUIHENGRIMOIRE_MATH_HPP
#define CUIHENGRIMOIRE_MATH_HPP
#include <iostream>
#include <vector>
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

}
#endif