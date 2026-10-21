---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/larsch.hpp
    title: algorithm/larsch.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algorithm/monge_1.test.cpp
    title: test/algorithm/monge_1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"algorithm/monge_d_edge_shortest_path.hpp\"\n// po167 Monge\
    \ library v2 (2026-10-21)\n#include <algorithm>\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n#line 2 \"algorithm/larsch.hpp\"\n// po167 Monge\
    \ library v2 (2026-10-21)\n#line 6 \"algorithm/larsch.hpp\"\n\nnamespace po167\
    \ {\nnamespace detail {\n\n// A[r][c] = value(r,c), 0 <= c <= r < n: Monge.\n\
    // r-th next_argmin() = min argmin_{0 <= c <= r} A[r][c].\n// O(n) total time,\
    \ O(n) space.\n// https://noshi91.github.io/Library/algorithm/larsch.cpp.html\
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
    \ detail\n}  // namespace po167\n#line 8 \"algorithm/monge_d_edge_shortest_path.hpp\"\
    \n\nnamespace po167 {\n\n// f(a,c)+f(b,d) <= f(a,d)+f(b,c) (0 <= a < b < c < d\
    \ <= n).\n// return min_{0=v_0 < v_1 < ... < v_d=n} sum_{t=1}^d f(v_{t-1},v_t).\n\
    // 1 <= d <= n; f(i,j) and the answer must fit in long long. Internal type: __int128_t.\n\
    // O(n log(W+2)) time, O(n) space; W is the internally computed penalty range.\n\
    template <class F>\nlong long monge_d_edge_shortest_path(int n, int d, const F&\
    \ f) {\n    using T = __int128_t;\n    const T inf = T(1) << 120;\n    assert(1\
    \ <= d && d <= n);\n    if (d == 1) return f(0, n);\n    if (d == n) {\n     \
    \   T total = 0;\n        for (int i = 0; i < n; ++i) total += T(f(i, i + 1));\n\
    \        return (long long)total;\n    }\n\n    // C[1], C[2], C[n], C[n]-C[n-1].\n\
    \    T one = f(0, n), two = inf, total = f(0, 1);\n    T previous = total, last_diff\
    \ = -inf;\n    for (int i = 1; i < n; ++i) {\n        T next = f(i, i + 1);\n\
    \        total += next;\n        two = std::min(two, T(f(0, i)) + T(f(i, n)));\n\
    \        last_diff = std::max(last_diff, previous + next - T(f(i - 1, i + 1)));\n\
    \        previous = next;\n    }\n    if (d == 2) return (long long)two;\n   \
    \ if (d == n - 1) return (long long)(total - last_diff);\n\n    std::vector<T>\
    \ dp(n + 1);\n    std::vector<int> parent(n + 1);\n    auto value = [&](int row,\
    \ int col) { return dp[col] + T(f(col, row + 1)); };\n    detail::Larsch<decltype(value)>\
    \ solver(n, value);\n    auto solve = [&](T penalty) {\n        solver.reset();\n\
    \        dp[0] = penalty;\n        for (int v = 1; v <= n; ++v) {\n          \
    \  int p = parent[v] = solver.next_argmin();\n            dp[v] = dp[p] + T(f(p,\
    \ v)) + penalty;\n        }\n        int count = 0;\n        for (int v = n; v;\
    \ v = parent[v]) ++count;\n        return std::pair<T, int>(dp[n] - penalty, count);\n\
    \    };\n\n    T lo = -last_diff, hi = one - two;\n    assert(lo <= hi);\n   \
    \ T answer = std::max(total + T(n - d) * lo, one + T(1 - d) * hi);\n    T left_cost\
    \ = total, right_cost = one;\n    int left_count = n, right_count = 1;\n    ++lo;\n\
    \    --hi;\n    bool bisect = false;\n    while (lo <= hi) {\n        T width\
    \ = hi - lo, x = lo + width / 2;\n        if (!bisect) {\n            // left_cost+left_count*x\
    \ = right_cost+right_count*x.\n            T a = right_cost - left_cost, b = left_count\
    \ - right_count;\n            x = std::clamp(a / b - (a % b < 0), lo, hi);\n \
    \       }\n        auto [cost, count] = solve(x);\n        answer = std::max(answer,\
    \ cost - T(d) * x);\n        if (count == d) break;\n        if (count > d) {\n\
    \            lo = x + 1;\n            left_cost = cost - T(count) * x;\n     \
    \       left_count = count;\n        } else {\n            hi = x - 1;\n     \
    \       right_cost = cost - T(count) * x;\n            right_count = count;\n\
    \        }\n        bisect = 2 * (hi - lo) > width;\n    }\n    return (long long)answer;\n\
    }\n\n// return monge_d_edge_shortest_path(n,d,f); upper is unused (compatibility\
    \ overload).\ntemplate <class F>\nlong long monge_d_edge_shortest_path(int n,\
    \ int d, long long, const F& f) {\n    return monge_d_edge_shortest_path(n, d,\
    \ f);\n}\n\n}  // namespace po167\n"
  code: "#pragma once\n// po167 Monge library v2 (2026-10-21)\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n#include \"larsch.hpp\"\
    \n\nnamespace po167 {\n\n// f(a,c)+f(b,d) <= f(a,d)+f(b,c) (0 <= a < b < c < d\
    \ <= n).\n// return min_{0=v_0 < v_1 < ... < v_d=n} sum_{t=1}^d f(v_{t-1},v_t).\n\
    // 1 <= d <= n; f(i,j) and the answer must fit in long long. Internal type: __int128_t.\n\
    // O(n log(W+2)) time, O(n) space; W is the internally computed penalty range.\n\
    template <class F>\nlong long monge_d_edge_shortest_path(int n, int d, const F&\
    \ f) {\n    using T = __int128_t;\n    const T inf = T(1) << 120;\n    assert(1\
    \ <= d && d <= n);\n    if (d == 1) return f(0, n);\n    if (d == n) {\n     \
    \   T total = 0;\n        for (int i = 0; i < n; ++i) total += T(f(i, i + 1));\n\
    \        return (long long)total;\n    }\n\n    // C[1], C[2], C[n], C[n]-C[n-1].\n\
    \    T one = f(0, n), two = inf, total = f(0, 1);\n    T previous = total, last_diff\
    \ = -inf;\n    for (int i = 1; i < n; ++i) {\n        T next = f(i, i + 1);\n\
    \        total += next;\n        two = std::min(two, T(f(0, i)) + T(f(i, n)));\n\
    \        last_diff = std::max(last_diff, previous + next - T(f(i - 1, i + 1)));\n\
    \        previous = next;\n    }\n    if (d == 2) return (long long)two;\n   \
    \ if (d == n - 1) return (long long)(total - last_diff);\n\n    std::vector<T>\
    \ dp(n + 1);\n    std::vector<int> parent(n + 1);\n    auto value = [&](int row,\
    \ int col) { return dp[col] + T(f(col, row + 1)); };\n    detail::Larsch<decltype(value)>\
    \ solver(n, value);\n    auto solve = [&](T penalty) {\n        solver.reset();\n\
    \        dp[0] = penalty;\n        for (int v = 1; v <= n; ++v) {\n          \
    \  int p = parent[v] = solver.next_argmin();\n            dp[v] = dp[p] + T(f(p,\
    \ v)) + penalty;\n        }\n        int count = 0;\n        for (int v = n; v;\
    \ v = parent[v]) ++count;\n        return std::pair<T, int>(dp[n] - penalty, count);\n\
    \    };\n\n    T lo = -last_diff, hi = one - two;\n    assert(lo <= hi);\n   \
    \ T answer = std::max(total + T(n - d) * lo, one + T(1 - d) * hi);\n    T left_cost\
    \ = total, right_cost = one;\n    int left_count = n, right_count = 1;\n    ++lo;\n\
    \    --hi;\n    bool bisect = false;\n    while (lo <= hi) {\n        T width\
    \ = hi - lo, x = lo + width / 2;\n        if (!bisect) {\n            // left_cost+left_count*x\
    \ = right_cost+right_count*x.\n            T a = right_cost - left_cost, b = left_count\
    \ - right_count;\n            x = std::clamp(a / b - (a % b < 0), lo, hi);\n \
    \       }\n        auto [cost, count] = solve(x);\n        answer = std::max(answer,\
    \ cost - T(d) * x);\n        if (count == d) break;\n        if (count > d) {\n\
    \            lo = x + 1;\n            left_cost = cost - T(count) * x;\n     \
    \       left_count = count;\n        } else {\n            hi = x - 1;\n     \
    \       right_cost = cost - T(count) * x;\n            right_count = count;\n\
    \        }\n        bisect = 2 * (hi - lo) > width;\n    }\n    return (long long)answer;\n\
    }\n\n// return monge_d_edge_shortest_path(n,d,f); upper is unused (compatibility\
    \ overload).\ntemplate <class F>\nlong long monge_d_edge_shortest_path(int n,\
    \ int d, long long, const F& f) {\n    return monge_d_edge_shortest_path(n, d,\
    \ f);\n}\n\n}  // namespace po167\n"
  dependsOn:
  - algorithm/larsch.hpp
  isVerificationFile: false
  path: algorithm/monge_d_edge_shortest_path.hpp
  requiredBy: []
  timestamp: '2026-10-21 23:29:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/algorithm/monge_1.test.cpp
documentation_of: algorithm/monge_d_edge_shortest_path.hpp
layout: document
redirect_from:
- /library/algorithm/monge_d_edge_shortest_path.hpp
- /library/algorithm/monge_d_edge_shortest_path.hpp.html
title: algorithm/monge_d_edge_shortest_path.hpp
---
