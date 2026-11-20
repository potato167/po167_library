// Standalone regression test; run without judge input.
#include "graph/KValueMinCut.hpp"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

template<class T>
void test_random() {
    std::mt19937 rng(167);
    for (int iteration = 0; iteration < 1500; iteration++) {
        int n = 1 + rng() % 5;
        std::vector<int> r(n);
        for (int& x : r) x = 1 + rng() % 4;
        po167::KValueMinCut<T> cut(r);
        using Cost = std::function<T(const std::vector<int>&)>;
        std::vector<Cost> terms;

        auto check = [&]() {
            auto evaluate = [&](const std::vector<int>& v) {
                T result = 0;
                for (const auto& term : terms) result += term(v);
                return result;
            };
            T expected = std::numeric_limits<T>::max();
            std::vector<int> v(n);
            auto enumerate = [&](auto&& self, int i) -> void {
                if (i == n) {
                    expected = std::min(expected, evaluate(v));
                    return;
                }
                for (v[i] = 0; v[i] < r[i]; v[i]++) self(self, i + 1);
            };
            enumerate(enumerate, 0);
            const auto result = cut.run();
            assert(result.first == expected);
            assert(int(result.second.size()) == n);
            for (int i = 0; i < n; i++) {
                assert(0 <= result.second[i] && result.second[i] < r[i]);
            }
            assert(evaluate(result.second) == expected);
            assert(cut.run() == result);
        };

        for (int step = 0; step < 40; step++) {
            int i = rng() % n, j = rng() % n;
            int a = rng() % (r[i] + 1), b = rng() % (r[j] + 1);
            T c = rng() % 11;
            switch (rng() % 7) {
            case 0:
                c -= 5;
                cut.add_linear(i, a, c);
                terms.emplace_back([=](const auto& v) { return c * (v[i] >= a); });
                break;
            case 1: {
                int k = rng() % r[i];
                c -= 5;
                cut.add_eq(i, k, c);
                terms.emplace_back([=](const auto& v) { return c * (v[i] == k); });
                break;
            }
            case 2:
                cut.add_lt_ge(i, a, j, b, c);
                terms.emplace_back([=](const auto& v) { return c * (v[i] < a && v[j] >= b); });
                break;
            case 3:
                cut.add_lt_lt(i, a, j, b, c);
                terms.emplace_back([=](const auto& v) { return -c * (v[i] < a && v[j] < b); });
                break;
            case 4:
                cut.add_ge_ge(i, a, j, b, c);
                terms.emplace_back([=](const auto& v) { return -c * (v[i] >= a && v[j] >= b); });
                break;
            case 5:
                cut.add_diff(i, a, j, b, c);
                terms.emplace_back([=](const auto& v) { return c * ((v[i] >= a) != (v[j] >= b)); });
                break;
            case 6:
                cut.add_edge(cut.node(i, a), cut.node(j, b), c);
                terms.emplace_back([=](const auto& v) { return c * (v[i] >= a && v[j] < b); });
                break;
            }
            // Also check adding terms after a previous run.
            if (step == 19 || step == 39) check();
        }
    }
}

template<class T>
void test_boundaries() {
    po167::KValueMinCut<T> empty({});
    assert(empty.run() == std::make_pair(T(0), std::vector<int>{}));

    po167::KValueMinCut<T> fixed({1, 1});
    assert(fixed.node(0, 0) == fixed.s);
    assert(fixed.node(0, 1) == fixed.t);
    fixed.add_eq(0, 0, -7);
    fixed.add_linear(1, 0, 2);
    fixed.add_linear(1, 1, 100);
    fixed.add_edge(fixed.s, fixed.t, 3);
    fixed.add_edge(fixed.t, fixed.s, 100);
    fixed.add_lt_lt(0, 1, 1, 1, 4);
    fixed.add_ge_ge(0, 0, 1, 0, 5);
    fixed.add_diff(0, 0, 1, 1, 6);
    assert(fixed.run() == std::make_pair(T(-5), std::vector<int>{0, 0}));

    // The generated ordering capacity can equal T's maximum value.
    po167::KValueMinCut<T> large({3});
    T c = std::numeric_limits<T>::max() - 1;
    large.add_linear(0, 2, -c);
    assert(large.run() == std::make_pair(-c, std::vector<int>{2}));
}

int main() {
    test_boundaries<int>();
    test_boundaries<long long>();
    test_random<int>();
    test_random<long long>();
    std::cout << "KValueMinCut: all tests passed\n";
}
