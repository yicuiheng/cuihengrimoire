#ifndef CUIHENGRIMOIRE_MODINT_HPP
#define CUIHENGRIMOIRE_MODINT_HPP

#include <cstdint>
#include <type_traits>

namespace cuihengrimoire {

// assume MOD is a prime number
template<
    typename BaseT = std::int64_t,
    BaseT MOD = static_cast<BaseT>(1000000007),
    typename = typename std::enable_if_t<std::is_integral_v<BaseT>>,
    typename = typename std::enable_if_t<(MOD > 0)>
>
struct modint_t {
    using value_t = BaseT;
    using this_t = modint_t<value_t, MOD>;

    constexpr modint_t(value_t const& x = static_cast<value_t>(0)) noexcept
    {
        this->x = x % MOD;
        if (this->x < 0)
            this->x += MOD;
    }
    constexpr modint_t(this_t const& rhs) noexcept : x{rhs.x} {}

    constexpr this_t& operator=(value_t const& rhs) noexcept {
        *this = this_t{rhs};
        return *this;
    }
    constexpr this_t& operator=(this_t const& rhs) noexcept {
        this->x = rhs.x;
        return *this;
    }

    value_t x = static_cast<value_t>(0);

    template<typename T>
    constexpr this_t& operator+=(T const& rhs) noexcept {
        this->x += this_t{rhs}.x;
        if (this->x >= MOD)
            this->x -= MOD;
        return *this;
    }
    template<typename T>
    constexpr this_t& operator-=(T const& rhs) noexcept {
        if (this->x < this_t{rhs}.x)
            this->x += MOD;
        this->x -= this_t{rhs}.x;
        return *this;
    }
    template<typename T>
    constexpr this_t& operator*=(T const& rhs) noexcept {
        this->x = (this->x * this_t{rhs}.x) % MOD;
        return *this;
    }
    template<typename T>
    constexpr this_t& operator/=(T const& rhs) noexcept {
        this->x /= this_t{rhs}.x;
        return *this;
    }
    template<typename T>
    constexpr this_t& operator%=(T const& rhs) noexcept {
        this->x %= this_t{rhs}.x;
        return *this;
    }
    constexpr this_t& operator++() noexcept {
        this->x = (this->x+1) % MOD;
        return *this;
    }
    constexpr this_t& operator--() noexcept {
        if (this->x == 0)
            this->x += MOD;
        this.x--;
        return *this;
    }
};

template<typename BaseT, BaseT MOD, typename U>
inline static auto operator+(modint_t<BaseT, MOD> const& lhs, U const& rhs) -> modint_t<BaseT, MOD> {
    auto tmp{lhs};
    tmp += rhs;
    return tmp;
}

template<typename BaseT, BaseT MOD, typename U>
inline static auto operator-(modint_t<BaseT, MOD> const& lhs, U const& rhs) -> modint_t<BaseT, MOD> {
    auto tmp{lhs};
    tmp -= rhs;
    return tmp;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator*(modint_t<BaseT, MOD> const& lhs, U const& rhs) -> modint_t<BaseT, MOD> {
    auto tmp{lhs};
    tmp *= rhs;
    return tmp;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator/(modint_t<BaseT, MOD> const& lhs, U const& rhs) -> modint_t<BaseT, MOD> {
    auto tmp{lhs};
    tmp /= rhs;
    return tmp;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator%(modint_t<BaseT, MOD> const& lhs, U const& rhs) -> modint_t<BaseT, MOD> {
    auto tmp{lhs};
    tmp %= rhs;
    return tmp;
}

template<typename BaseT, BaseT MOD, typename U>
inline static auto operator<(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return lhs.x < modint_t<BaseT, MOD>{rhs}.x;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator<=(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return lhs.x <= modint_t<BaseT, MOD>{rhs}.x;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator>(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return lhs.x > modint_t<BaseT, MOD>{rhs}.x;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator>=(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return lhs.x >= modint_t<BaseT, MOD>{rhs}.x;
}

template<typename BaseT, BaseT MOD, typename U>
inline static auto operator==(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return lhs.x == modint_t<BaseT, MOD>{rhs}.x;
}
template<typename BaseT, BaseT MOD, typename U>
inline static auto operator!=(modint_t<BaseT, MOD> const& lhs, U const& rhs) {
    return !(lhs == rhs);
}

}

#endif
