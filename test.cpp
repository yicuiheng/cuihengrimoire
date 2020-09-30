#include <iostream>
#include <cassert>
#include "math.hpp"
#include "modint.hpp"
#include "graph.hpp"
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

    // 5C2 = 10
    math::combination_t<mod31_t, 100> comb;
    assert(comb(5, 3) == 10);

    std::vector<long long> expected1{{1, 7, 49}};
    assert(math::divisor(49ll) == expected1);

    auto prime_table = math::prime_table_t<long long, 100>{};
    assert(prime_table.is_prime(31));
    std::unordered_map<long long, long long> expected2{{7, 2}};
    assert(prime_table.prime_factorization(49) == expected2);

    // graph
    // 0-----1-----2-----3
    //  \--4---5--/
    graph_t<int> g{};
    g.add_node(0);
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);
    g.add_node(4);
    g.add_node(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(0, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 2);
    auto shortest_pathes = g.search_shortest_path_from(0);
    std::vector<graph_t<int>::path_t> expected3{{
        graph_t<int>::path_t{},
        graph_t<int>::path_t{{0}},
        graph_t<int>::path_t{{0, 1}},
        graph_t<int>::path_t{{0, 1, 2}},
        graph_t<int>::path_t{{0}},
        graph_t<int>::path_t{{0, 4}}
    }};
    assert(shortest_pathes.size() == expected3.size());
    assert(std::equal(
        shortest_pathes.begin(), shortest_pathes.end(),
        expected3.begin(), expected3.end()));
}
