---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/KValueMinCut.hpp
    title: "k \u5024\u71C3\u3084\u3059\u57CB\u3081\u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"test/graph/k_value_min_cut_unit.cpp\"\n// Standalone regression\
    \ test; run without judge input.\n#line 2 \"graph/KValueMinCut.hpp\"\n#include\
    \ <atcoder/maxflow>\n#include <vector>\n#include <tuple>\n#include <utility>\n\
    #include <cassert>\n#include <limits>\n#include <type_traits>\n\nnamespace po167\
    \ {\n\ntemplate<class T = long long>\nstruct KValueMinCut {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    int n, s, t;\n    std::vector<int> R, base;\n\
    \    std::vector<T> linear;\n    std::vector<std::tuple<int, int, T>> edges;\n\
    \    T constant = 0;\n\n    explicit KValueMinCut(const std::vector<int>& r)\n\
    \        : n(r.size()), R(r), base(n) {\n        int m = 0;\n        for (int\
    \ i = 0; i < n; i++) {\n            assert(R[i] >= 1);\n            base[i] =\
    \ m;\n            m += R[i] - 1;\n        }\n        s = m;\n        t = m + 1;\n\
    \        linear.resize(m + 2);\n    }\n\n    // x(i,a) = [v[i] >= a]\n    int\
    \ node(int i, int a) const {\n        assert(0 <= i && i < n);\n        assert(0\
    \ <= a && a <= R[i]);\n        if (a == 0) return s;\n        if (a == R[i]) return\
    \ t;\n        return base[i] + a - 1;\n    }\n\n    // c * x(i,a)\n    void add_linear(int\
    \ i, int a, T c) {\n        linear[node(i, a)] += c;\n    }\n\n    // c * [u is\
    \ S-side and v is T-side]\n    void add_edge(int u, int v, T c) {\n        assert(c\
    \ >= 0);\n        if (c == 0 || u == v || u == t || v == s) return;\n        if\
    \ (u == s && v == t) constant += c;\n        else edges.emplace_back(u, v, c);\n\
    \    }\n\n    // +c if v[i] == k\n    void add_eq(int i, int k, T c) {\n     \
    \   assert(0 <= k && k < R[i]);\n        add_linear(i, k, c);\n        add_linear(i,\
    \ k + 1, -c);\n    }\n\n    // +c if v[i] < a && v[j] >= b\n    void add_lt_ge(int\
    \ i, int a, int j, int b, T c) {\n        add_edge(node(j, b), node(i, a), c);\n\
    \    }\n\n    // -c if v[i] < a && v[j] < b\n    void add_lt_lt(int i, int a,\
    \ int j, int b, T c) {\n        assert(c >= 0);\n        constant -= c;\n    \
    \    add_linear(i, a, c);\n        add_lt_ge(i, a, j, b, c);\n    }\n\n    //\
    \ -c if v[i] >= a && v[j] >= b\n    void add_ge_ge(int i, int a, int j, int b,\
    \ T c) {\n        assert(c >= 0);\n        add_linear(i, a, -c);\n        add_edge(node(i,\
    \ a), node(j, b), c);\n    }\n\n    // +c if [v[i] >= a] != [v[j] >= b]\n    void\
    \ add_diff(int i, int a, int j, int b, T c) {\n        add_lt_ge(i, a, j, b, c);\n\
    \        add_lt_ge(j, b, i, a, c);\n    }\n\n    // return {minimum cost, optimal\
    \ v}\n    std::pair<T, std::vector<int>> run() const {\n        T sum = 0;\n \
    \       auto add_sum = [&](T c) {\n            assert(c >= 0 && c < std::numeric_limits<T>::max()\
    \ - sum);\n            sum += c;\n        };\n\n        for (auto [u, v, c] :\
    \ edges) add_sum(c);\n        for (int u = 0; u < s; u++) {\n            assert(linear[u]\
    \ != std::numeric_limits<T>::min());\n            add_sum(linear[u] < 0 ? -linear[u]\
    \ : linear[u]);\n        }\n\n        atcoder::mf_graph<T> graph(t + 1);\n   \
    \     for (auto [u, v, c] : edges) graph.add_edge(u, v, c);\n\n        T ans =\
    \ constant + linear[s];\n        for (int u = 0; u < s; u++) {\n            if\
    \ (linear[u] > 0) {\n                graph.add_edge(u, t, linear[u]);\n      \
    \      } else if (linear[u] < 0) {\n                graph.add_edge(s, u, -linear[u]);\n\
    \                ans += linear[u];\n            }\n        }\n\n        T inf\
    \ = sum + 1;\n        for (int i = 0; i < n; i++) {\n            for (int a =\
    \ 1; a + 1 < R[i]; a++) {\n                graph.add_edge(node(i, a + 1), node(i,\
    \ a), inf);\n            }\n        }\n\n        ans += graph.flow(s, t);\n  \
    \      auto side = graph.min_cut(s);\n\n        std::vector<int> v(n);\n     \
    \   for (int i = 0; i < n; i++) {\n            for (int a = 1; a < R[i]; a++)\
    \ {\n                if (side[node(i, a)]) v[i] = a;\n            }\n        }\n\
    \        return {ans, v};\n    }\n};\n\n}\n#line 3 \"test/graph/k_value_min_cut_unit.cpp\"\
    \n\n#include <algorithm>\n#line 6 \"test/graph/k_value_min_cut_unit.cpp\"\n#include\
    \ <functional>\n#include <iostream>\n#line 9 \"test/graph/k_value_min_cut_unit.cpp\"\
    \n#include <random>\n#line 11 \"test/graph/k_value_min_cut_unit.cpp\"\n\ntemplate<class\
    \ T>\nvoid test_random() {\n    std::mt19937 rng(167);\n    for (int iteration\
    \ = 0; iteration < 1500; iteration++) {\n        int n = 1 + rng() % 5;\n    \
    \    std::vector<int> r(n);\n        for (int& x : r) x = 1 + rng() % 4;\n   \
    \     po167::KValueMinCut<T> cut(r);\n        using Cost = std::function<T(const\
    \ std::vector<int>&)>;\n        std::vector<Cost> terms;\n\n        auto check\
    \ = [&]() {\n            auto evaluate = [&](const std::vector<int>& v) {\n  \
    \              T result = 0;\n                for (const auto& term : terms) result\
    \ += term(v);\n                return result;\n            };\n            T expected\
    \ = std::numeric_limits<T>::max();\n            std::vector<int> v(n);\n     \
    \       auto enumerate = [&](auto&& self, int i) -> void {\n                if\
    \ (i == n) {\n                    expected = std::min(expected, evaluate(v));\n\
    \                    return;\n                }\n                for (v[i] = 0;\
    \ v[i] < r[i]; v[i]++) self(self, i + 1);\n            };\n            enumerate(enumerate,\
    \ 0);\n            const auto result = cut.run();\n            assert(result.first\
    \ == expected);\n            assert(int(result.second.size()) == n);\n       \
    \     for (int i = 0; i < n; i++) {\n                assert(0 <= result.second[i]\
    \ && result.second[i] < r[i]);\n            }\n            assert(evaluate(result.second)\
    \ == expected);\n            assert(cut.run() == result);\n        };\n\n    \
    \    for (int step = 0; step < 40; step++) {\n            int i = rng() % n, j\
    \ = rng() % n;\n            int a = rng() % (r[i] + 1), b = rng() % (r[j] + 1);\n\
    \            T c = rng() % 11;\n            switch (rng() % 7) {\n           \
    \ case 0:\n                c -= 5;\n                cut.add_linear(i, a, c);\n\
    \                terms.emplace_back([=](const auto& v) { return c * (v[i] >= a);\
    \ });\n                break;\n            case 1: {\n                int k =\
    \ rng() % r[i];\n                c -= 5;\n                cut.add_eq(i, k, c);\n\
    \                terms.emplace_back([=](const auto& v) { return c * (v[i] == k);\
    \ });\n                break;\n            }\n            case 2:\n          \
    \      cut.add_lt_ge(i, a, j, b, c);\n                terms.emplace_back([=](const\
    \ auto& v) { return c * (v[i] < a && v[j] >= b); });\n                break;\n\
    \            case 3:\n                cut.add_lt_lt(i, a, j, b, c);\n        \
    \        terms.emplace_back([=](const auto& v) { return -c * (v[i] < a && v[j]\
    \ < b); });\n                break;\n            case 4:\n                cut.add_ge_ge(i,\
    \ a, j, b, c);\n                terms.emplace_back([=](const auto& v) { return\
    \ -c * (v[i] >= a && v[j] >= b); });\n                break;\n            case\
    \ 5:\n                cut.add_diff(i, a, j, b, c);\n                terms.emplace_back([=](const\
    \ auto& v) { return c * ((v[i] >= a) != (v[j] >= b)); });\n                break;\n\
    \            case 6:\n                cut.add_edge(cut.node(i, a), cut.node(j,\
    \ b), c);\n                terms.emplace_back([=](const auto& v) { return c *\
    \ (v[i] >= a && v[j] < b); });\n                break;\n            }\n      \
    \      // Also check adding terms after a previous run.\n            if (step\
    \ == 19 || step == 39) check();\n        }\n    }\n}\n\ntemplate<class T>\nvoid\
    \ test_boundaries() {\n    po167::KValueMinCut<T> empty({});\n    assert(empty.run()\
    \ == std::make_pair(T(0), std::vector<int>{}));\n\n    po167::KValueMinCut<T>\
    \ fixed({1, 1});\n    assert(fixed.node(0, 0) == fixed.s);\n    assert(fixed.node(0,\
    \ 1) == fixed.t);\n    fixed.add_eq(0, 0, -7);\n    fixed.add_linear(1, 0, 2);\n\
    \    fixed.add_linear(1, 1, 100);\n    fixed.add_edge(fixed.s, fixed.t, 3);\n\
    \    fixed.add_edge(fixed.t, fixed.s, 100);\n    fixed.add_lt_lt(0, 1, 1, 1, 4);\n\
    \    fixed.add_ge_ge(0, 0, 1, 0, 5);\n    fixed.add_diff(0, 0, 1, 1, 6);\n   \
    \ assert(fixed.run() == std::make_pair(T(-5), std::vector<int>{0, 0}));\n\n  \
    \  // The generated ordering capacity can equal T's maximum value.\n    po167::KValueMinCut<T>\
    \ large({3});\n    T c = std::numeric_limits<T>::max() - 1;\n    large.add_linear(0,\
    \ 2, -c);\n    assert(large.run() == std::make_pair(-c, std::vector<int>{2}));\n\
    }\n\nint main() {\n    test_boundaries<int>();\n    test_boundaries<long long>();\n\
    \    test_random<int>();\n    test_random<long long>();\n    std::cout << \"KValueMinCut:\
    \ all tests passed\\n\";\n}\n"
  code: "// Standalone regression test; run without judge input.\n#include \"graph/KValueMinCut.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <iostream>\n#include <limits>\n#include <random>\n#include <vector>\n\ntemplate<class\
    \ T>\nvoid test_random() {\n    std::mt19937 rng(167);\n    for (int iteration\
    \ = 0; iteration < 1500; iteration++) {\n        int n = 1 + rng() % 5;\n    \
    \    std::vector<int> r(n);\n        for (int& x : r) x = 1 + rng() % 4;\n   \
    \     po167::KValueMinCut<T> cut(r);\n        using Cost = std::function<T(const\
    \ std::vector<int>&)>;\n        std::vector<Cost> terms;\n\n        auto check\
    \ = [&]() {\n            auto evaluate = [&](const std::vector<int>& v) {\n  \
    \              T result = 0;\n                for (const auto& term : terms) result\
    \ += term(v);\n                return result;\n            };\n            T expected\
    \ = std::numeric_limits<T>::max();\n            std::vector<int> v(n);\n     \
    \       auto enumerate = [&](auto&& self, int i) -> void {\n                if\
    \ (i == n) {\n                    expected = std::min(expected, evaluate(v));\n\
    \                    return;\n                }\n                for (v[i] = 0;\
    \ v[i] < r[i]; v[i]++) self(self, i + 1);\n            };\n            enumerate(enumerate,\
    \ 0);\n            const auto result = cut.run();\n            assert(result.first\
    \ == expected);\n            assert(int(result.second.size()) == n);\n       \
    \     for (int i = 0; i < n; i++) {\n                assert(0 <= result.second[i]\
    \ && result.second[i] < r[i]);\n            }\n            assert(evaluate(result.second)\
    \ == expected);\n            assert(cut.run() == result);\n        };\n\n    \
    \    for (int step = 0; step < 40; step++) {\n            int i = rng() % n, j\
    \ = rng() % n;\n            int a = rng() % (r[i] + 1), b = rng() % (r[j] + 1);\n\
    \            T c = rng() % 11;\n            switch (rng() % 7) {\n           \
    \ case 0:\n                c -= 5;\n                cut.add_linear(i, a, c);\n\
    \                terms.emplace_back([=](const auto& v) { return c * (v[i] >= a);\
    \ });\n                break;\n            case 1: {\n                int k =\
    \ rng() % r[i];\n                c -= 5;\n                cut.add_eq(i, k, c);\n\
    \                terms.emplace_back([=](const auto& v) { return c * (v[i] == k);\
    \ });\n                break;\n            }\n            case 2:\n          \
    \      cut.add_lt_ge(i, a, j, b, c);\n                terms.emplace_back([=](const\
    \ auto& v) { return c * (v[i] < a && v[j] >= b); });\n                break;\n\
    \            case 3:\n                cut.add_lt_lt(i, a, j, b, c);\n        \
    \        terms.emplace_back([=](const auto& v) { return -c * (v[i] < a && v[j]\
    \ < b); });\n                break;\n            case 4:\n                cut.add_ge_ge(i,\
    \ a, j, b, c);\n                terms.emplace_back([=](const auto& v) { return\
    \ -c * (v[i] >= a && v[j] >= b); });\n                break;\n            case\
    \ 5:\n                cut.add_diff(i, a, j, b, c);\n                terms.emplace_back([=](const\
    \ auto& v) { return c * ((v[i] >= a) != (v[j] >= b)); });\n                break;\n\
    \            case 6:\n                cut.add_edge(cut.node(i, a), cut.node(j,\
    \ b), c);\n                terms.emplace_back([=](const auto& v) { return c *\
    \ (v[i] >= a && v[j] < b); });\n                break;\n            }\n      \
    \      // Also check adding terms after a previous run.\n            if (step\
    \ == 19 || step == 39) check();\n        }\n    }\n}\n\ntemplate<class T>\nvoid\
    \ test_boundaries() {\n    po167::KValueMinCut<T> empty({});\n    assert(empty.run()\
    \ == std::make_pair(T(0), std::vector<int>{}));\n\n    po167::KValueMinCut<T>\
    \ fixed({1, 1});\n    assert(fixed.node(0, 0) == fixed.s);\n    assert(fixed.node(0,\
    \ 1) == fixed.t);\n    fixed.add_eq(0, 0, -7);\n    fixed.add_linear(1, 0, 2);\n\
    \    fixed.add_linear(1, 1, 100);\n    fixed.add_edge(fixed.s, fixed.t, 3);\n\
    \    fixed.add_edge(fixed.t, fixed.s, 100);\n    fixed.add_lt_lt(0, 1, 1, 1, 4);\n\
    \    fixed.add_ge_ge(0, 0, 1, 0, 5);\n    fixed.add_diff(0, 0, 1, 1, 6);\n   \
    \ assert(fixed.run() == std::make_pair(T(-5), std::vector<int>{0, 0}));\n\n  \
    \  // The generated ordering capacity can equal T's maximum value.\n    po167::KValueMinCut<T>\
    \ large({3});\n    T c = std::numeric_limits<T>::max() - 1;\n    large.add_linear(0,\
    \ 2, -c);\n    assert(large.run() == std::make_pair(-c, std::vector<int>{2}));\n\
    }\n\nint main() {\n    test_boundaries<int>();\n    test_boundaries<long long>();\n\
    \    test_random<int>();\n    test_random<long long>();\n    std::cout << \"KValueMinCut:\
    \ all tests passed\\n\";\n}\n"
  dependsOn:
  - graph/KValueMinCut.hpp
  isVerificationFile: false
  path: test/graph/k_value_min_cut_unit.cpp
  requiredBy: []
  timestamp: '2026-11-20 21:17:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/graph/k_value_min_cut_unit.cpp
layout: document
redirect_from:
- /library/test/graph/k_value_min_cut_unit.cpp
- /library/test/graph/k_value_min_cut_unit.cpp.html
title: test/graph/k_value_min_cut_unit.cpp
---
