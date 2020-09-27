#include <iostream>
#include <cassert>
#include "math.hpp"
#include "modint.hpp"
using namespace cuihengrimoire;

int main() {
    using mod31_t = modint_t<std::int64_t, 31>;
    mod31_t a{42};
    assert(a == 11);
    a = a + 50;
    assert(a == 30);
    a = a - 62;
    assert(a == 30);
    a = a - a;
    assert(a == 0);
    a = 2;
    assert(math::power(a, 5) == 1);
}
