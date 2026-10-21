---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/larsch.hpp
    title: algorithm/larsch.hpp
  - icon: ':heavy_check_mark:'
    path: algorithm/monge_shortest_path.hpp
    title: algorithm/monge_shortest_path.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/705
    links:
    - https://yukicoder.me/problems/no/705
  bundledCode: "#line 1 \"test/algorithm/monge_3.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/705\"\
    \n\n#line 2 \"algorithm/monge_shortest_path.hpp\"\n// po167 Monge library v2:\
    \ predecessor support (2026-10-21)\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n#line 2 \"algorithm/larsch.hpp\"\n// po167 Monge library v2 (2026-10-21)\n\
    #line 6 \"algorithm/larsch.hpp\"\n\nnamespace po167 {\nnamespace detail {\n\n\
    // A[r][c] = value(r,c), 0 <= c <= r < n: Monge.\n// r-th next_argmin() = min\
    \ argmin_{0 <= c <= r} A[r][c].\n// O(n) total time, O(n) space.\n// https://noshi91.github.io/Library/algorithm/larsch.cpp.html\
    \ (CC0)\ntemplate <class F>\nclass Larsch {\n    struct Level {\n        int n,\
    \ row = 0, state = 0, size = 0;\n        std::vector<int> column;\n        Level(int\
    \ n_, bool base) : n(n_), column(base ? 0 : n_) {}\n    };\n    F value;\n   \
    \ std::vector<Level> levels;\n\n    int next_argmin(int depth) {\n        auto&\
    \ a = levels[depth];\n        int row = a.row++, r = ((row + 1) << depth) - 1;\n\
    \        auto column = [&](int j) { return depth ? a.column[j] : j; };\n     \
    \   int best = column(a.state);\n        if (row & 1) {\n            int last\
    \ = column(row);\n            return value(r, last) < value(r, best) ? last :\
    \ best;\n        }\n        int bound;\n        if (row + 1 == a.n) {\n      \
    \      bound = column(a.n - 1);\n        } else {\n            auto& b = levels[depth\
    \ + 1];\n            for (int j = (row ? row - 1 : 0); j <= row; ++j) {\n    \
    \            int c = column(j);\n                while (b.size > row / 2) {\n\
    \                    int q = (b.size << (depth + 1)) - 1;\n                  \
    \  if (!(value(q, c) < value(q, b.column[b.size - 1]))) break;\n             \
    \       --b.size;\n                }\n                if (b.size < b.n) b.column[b.size++]\
    \ = c;\n            }\n            bound = next_argmin(depth + 1);\n        }\n\
    \        if (best != bound) {\n            auto best_value = value(r, best);\n\
    \            do {\n                int c = column(++a.state);\n              \
    \  auto candidate = value(r, c);\n                if (candidate < best_value)\
    \ best_value = candidate, best = c;\n            } while (column(a.state) != bound);\n\
    \        }\n        return best;\n    }\n\npublic:\n    // A[r][c] = value_(r,c),\
    \ 0 <= c <= r < n; next row = 0.\n    Larsch(int n, F value_) : value(std::move(value_))\
    \ {\n        assert(n >= 0);\n        for (int size = n; size; size /= 2) levels.emplace_back(size,\
    \ levels.empty());\n    }\n\n    // return min argmin_{0 <= c <= r} A[r][c], then\
    \ r <- r+1.\n    int next_argmin() {\n        assert(!levels.empty() && levels[0].row\
    \ < levels[0].n);\n        return next_argmin(0);\n    }\n\n    // r <- 0; A may\
    \ be changed before the next sequence of queries.\n    void reset() {\n      \
    \  for (auto& a : levels) a.row = a.state = a.size = 0;\n    }\n};\n\n}  // namespace\
    \ detail\n}  // namespace po167\n#line 7 \"algorithm/monge_shortest_path.hpp\"\
    \n\nnamespace po167 {\n\n// f(a,c)+f(b,d) <= f(a,d)+f(b,c) (0 <= a < b < c < d\
    \ <= n).\n// return {dp, prev}: dp[0]=0, prev[0]=-1.\n// dp[j]=min_{0 <= i < j}(dp[i]+f(i,j))\
    \ (1 <= j <= n).\n// prev[j]=min argmin_{0 <= i < j}(dp[i]+f(i,j)).\n// n >= 0;\
    \ all costs and candidate sums must fit in T. Negative costs are allowed.\n//\
    \ O(n) time, O(n) space, assuming f is O(1).\ntemplate <class T = long long, class\
    \ F>\nstd::pair<std::vector<T>, std::vector<int>> monge_shortest_path(int n, const\
    \ F& f) {\n    assert(n >= 0);\n    std::vector<T> dp(n + 1);\n    std::vector<int>\
    \ prev(n + 1, -1);\n    auto value = [&](int row, int col) { return dp[col] +\
    \ T(f(col, row + 1)); };\n    detail::Larsch<decltype(value)> solver(n, value);\n\
    \    for (int v = 1; v <= n; ++v) {\n        int p = prev[v] = solver.next_argmin();\n\
    \        dp[v] = dp[p] + T(f(p, v));\n    }\n    return {std::move(dp), std::move(prev)};\n\
    }\n\n}  // namespace po167\n#line 4 \"test/algorithm/monge_3.test.cpp\"\n#include\
    \ <cstdlib>\n#include <iostream>\n#line 7 \"test/algorithm/monge_3.test.cpp\"\n\
    \nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<long long> A(N), X(N), Y(N);\n\
    \    for (auto &a : A) std::cin >> a;\n    for (auto &x : X) std::cin >> x;\n\
    \    for (auto &y : Y) std::cin >> y;\n\n    auto cost = [&](int i, int j){\n\
    \        long long dx = std::abs(A[j - 1] - X[i]);\n        return dx * dx * dx\
    \ + Y[i] * Y[i] * Y[i];\n    };\n\n    auto dp = po167::monge_shortest_path(N,\
    \ cost);\n    std::cout << dp.first[N] << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/705\"\n\n#include \"../../algorithm/monge_shortest_path.hpp\"\
    \n#include <cstdlib>\n#include <iostream>\n#include <vector>\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ N;\n    std::cin >> N;\n    std::vector<long long> A(N), X(N), Y(N);\n    for\
    \ (auto &a : A) std::cin >> a;\n    for (auto &x : X) std::cin >> x;\n    for\
    \ (auto &y : Y) std::cin >> y;\n\n    auto cost = [&](int i, int j){\n       \
    \ long long dx = std::abs(A[j - 1] - X[i]);\n        return dx * dx * dx + Y[i]\
    \ * Y[i] * Y[i];\n    };\n\n    auto dp = po167::monge_shortest_path(N, cost);\n\
    \    std::cout << dp.first[N] << \"\\n\";\n}\n"
  dependsOn:
  - algorithm/monge_shortest_path.hpp
  - algorithm/larsch.hpp
  isVerificationFile: true
  path: test/algorithm/monge_3.test.cpp
  requiredBy: []
  timestamp: '2026-10-21 23:29:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/algorithm/monge_3.test.cpp
layout: document
redirect_from:
- /verify/test/algorithm/monge_3.test.cpp
- /verify/test/algorithm/monge_3.test.cpp.html
title: test/algorithm/monge_3.test.cpp
---
