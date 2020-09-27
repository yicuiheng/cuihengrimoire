#ifndef CUIHENGRIMOIRE_MATH_HPP
#define CUIHENGRIMOIRE_MATH_HPP

namespace math {
    template<typename T, typename U>
    T power(T x, U n) {
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
}

#endif