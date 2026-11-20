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
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/119
    links:
    - https://yukicoder.me/problems/no/119
  bundledCode: "#line 1 \"test/graph/k_value_min_cut_yukicoder.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/119\"\n\n#line 2 \"graph/KValueMinCut.hpp\"\
    \n#include <atcoder/maxflow>\n#include <vector>\n#include <tuple>\n#include <utility>\n\
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
    \ -c if v[i] < a for every (i, a) in conditions\n    void add_lt_lt(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        constant -= c;\n        if (conditions.empty()) return;\n        int\
    \ u = int(linear.size());\n        linear.push_back(c);\n        for (auto [i,\
    \ a] : conditions) {\n            add_edge(node(i, a), u, c);\n        }\n   \
    \ }\n\n    // -c if v[i] >= a && v[j] >= b\n    void add_ge_ge(int i, int a, int\
    \ j, int b, T c) {\n        assert(c >= 0);\n        add_linear(i, a, -c);\n \
    \       add_edge(node(i, a), node(j, b), c);\n    }\n\n    // -c if v[i] >= a\
    \ for every (i, a) in conditions\n    void add_ge_ge(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        if (conditions.empty()) {\n            constant -= c;\n            return;\n\
    \        }\n        int u = int(linear.size());\n        linear.push_back(-c);\n\
    \        for (auto [i, a] : conditions) {\n            add_edge(u, node(i, a),\
    \ c);\n        }\n    }\n\n    // +c if [v[i] >= a] != [v[j] >= b]\n    void add_diff(int\
    \ i, int a, int j, int b, T c) {\n        add_lt_ge(i, a, j, b, c);\n        add_lt_ge(j,\
    \ b, i, a, c);\n    }\n\n    // return {minimum cost, optimal v}\n    std::pair<T,\
    \ std::vector<int>> run() const {\n        int vertices = int(linear.size());\n\
    \        T sum = 0;\n        auto add_sum = [&](T c) {\n            assert(c >=\
    \ 0 && c < std::numeric_limits<T>::max() - sum);\n            sum += c;\n    \
    \    };\n\n        for (auto [u, v, c] : edges) add_sum(c);\n        for (int\
    \ u = 0; u < vertices; u++) {\n            if (u == s || u == t) continue;\n \
    \           assert(linear[u] != std::numeric_limits<T>::min());\n            add_sum(linear[u]\
    \ < 0 ? -linear[u] : linear[u]);\n        }\n\n        atcoder::mf_graph<T> graph(vertices);\n\
    \        for (auto [u, v, c] : edges) graph.add_edge(u, v, c);\n\n        T ans\
    \ = constant + linear[s];\n        for (int u = 0; u < vertices; u++) {\n    \
    \        if (u == s || u == t) continue;\n            if (linear[u] > 0) {\n \
    \               graph.add_edge(u, t, linear[u]);\n            } else if (linear[u]\
    \ < 0) {\n                graph.add_edge(s, u, -linear[u]);\n                ans\
    \ += linear[u];\n            }\n        }\n\n        T inf = sum + 1;\n      \
    \  for (int i = 0; i < n; i++) {\n            for (int a = 1; a + 1 < R[i]; a++)\
    \ {\n                graph.add_edge(node(i, a + 1), node(i, a), inf);\n      \
    \      }\n        }\n\n        ans += graph.flow(s, t);\n        auto side = graph.min_cut(s);\n\
    \n        std::vector<int> v(n);\n        for (int i = 0; i < n; i++) {\n    \
    \        for (int a = 1; a < R[i]; a++) {\n                if (side[node(i, a)])\
    \ v[i] = a;\n            }\n        }\n        return {ans, v};\n    }\n};\n\n\
    }\n#line 4 \"test/graph/k_value_min_cut_yukicoder.test.cpp\"\n\n#include <algorithm>\n\
    #include <iostream>\n#line 8 \"test/graph/k_value_min_cut_yukicoder.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    po167::KValueMinCut<long long> cut(std::vector<int>(n,\
    \ 3));\n    long long inf = 1;\n    for (int i = 0; i < n; i++) {\n        long\
    \ long b, c;\n        std::cin >> b >> c;\n        // 0: visit without a tour,\
    \ 1: do not visit, 2: join the tour.\n        cut.add_eq(i, 0, -c);\n        cut.add_eq(i,\
    \ 2, -b);\n        inf += std::max(b, c);\n    }\n    int m;\n    std::cin >>\
    \ m;\n    for (int i = 0; i < m; i++) {\n        int d, e;\n        std::cin >>\
    \ d >> e;\n        // Joining d's tour forbids visiting e without joining its\
    \ tour.\n        cut.add_lt_ge(e, 1, d, 2, inf);\n    }\n    std::cout << -cut.run().first\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/119\"\n\n#include \"graph/KValueMinCut.hpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <vector>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n    po167::KValueMinCut<long long> cut(std::vector<int>(n,\
    \ 3));\n    long long inf = 1;\n    for (int i = 0; i < n; i++) {\n        long\
    \ long b, c;\n        std::cin >> b >> c;\n        // 0: visit without a tour,\
    \ 1: do not visit, 2: join the tour.\n        cut.add_eq(i, 0, -c);\n        cut.add_eq(i,\
    \ 2, -b);\n        inf += std::max(b, c);\n    }\n    int m;\n    std::cin >>\
    \ m;\n    for (int i = 0; i < m; i++) {\n        int d, e;\n        std::cin >>\
    \ d >> e;\n        // Joining d's tour forbids visiting e without joining its\
    \ tour.\n        cut.add_lt_ge(e, 1, d, 2, inf);\n    }\n    std::cout << -cut.run().first\
    \ << '\\n';\n}\n"
  dependsOn:
  - graph/KValueMinCut.hpp
  isVerificationFile: true
  path: test/graph/k_value_min_cut_yukicoder.test.cpp
  requiredBy: []
  timestamp: '2026-11-21 02:09:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/k_value_min_cut_yukicoder.test.cpp
layout: document
redirect_from:
- /verify/test/graph/k_value_min_cut_yukicoder.test.cpp
- /verify/test/graph/k_value_min_cut_yukicoder.test.cpp.html
title: test/graph/k_value_min_cut_yukicoder.test.cpp
---
