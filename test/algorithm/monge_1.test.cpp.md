---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/larsch.hpp
    title: algorithm/larsch.hpp
  - icon: ':heavy_check_mark:'
    path: algorithm/monge_d_edge_shortest_path.hpp
    title: algorithm/monge_d_edge_shortest_path.hpp
  - icon: ':heavy_check_mark:'
    path: algorithm/monge_k_edge_shortest_path.hpp
    title: algorithm/monge_k_edge_shortest_path.hpp
  - icon: ':heavy_check_mark:'
    path: algorithm/smawk.hpp
    title: algorithm/smawk.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/952
    links:
    - https://yukicoder.me/problems/no/952
  bundledCode: "#line 1 \"test/algorithm/monge_1.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/952\"\
    \n\n#line 2 \"algorithm/monge_d_edge_shortest_path.hpp\"\n// po167 Monge library\
    \ v2 (2026-10-21)\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n#line 2 \"algorithm/larsch.hpp\"\n// po167 Monge library v2\
    \ (2026-10-21)\n#line 6 \"algorithm/larsch.hpp\"\n\nnamespace po167 {\nnamespace\
    \ detail {\n\n// A[r][c] = value(r,c), 0 <= c <= r < n: Monge.\n// r-th next_argmin()\
    \ = min argmin_{0 <= c <= r} A[r][c].\n// O(n) total time, O(n) space.\n// https://noshi91.github.io/Library/algorithm/larsch.cpp.html\
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
    \ f);\n}\n\n}  // namespace po167\n#line 2 \"algorithm/monge_k_edge_shortest_path.hpp\"\
    \n// po167 Monge library v2 (2026-10-21)\n#line 3 \"algorithm/smawk.hpp\"\n#include\
    \ <numeric>\nnamespace po167{\n// return argmax\n// \n// https://noshi91.github.io/Library/algorithm/smawk.cpp\n\
    template<class S> std::vector<int> smawk(int N, int M, S select){\n    auto f\
    \ = [&](auto self, std::vector<int> p,std::vector<int> q) -> std::vector<int>\
    \ {\n        // reduce\n        std::vector<int> n_q;\n        n_q.reserve(p.size());\n\
    \        int k = -1;\n        for(auto x:q){\n            while(!n_q.empty()){\n\
    \                if(!select(p[k], n_q.back(), x)) break;\n                n_q.pop_back();\n\
    \                k--;\n            }\n            if (k + 1 != (int)p.size()){\n\
    \                n_q.push_back(x);\n                k++;\n            }\n    \
    \    }\n        std::swap(n_q, q);\n\n        int n = p.size();\n        int m\
    \ = q.size();\n        \n        // recursive\n        if (n == 1){\n        \
    \    return q;\n        }\n        std::vector<int> n_p;\n        n_p.reserve(n\
    \ / 2);\n\n        for (int i = 1; i < n; i += 2){\n            n_p.push_back(p[i]);\n\
    \        }\n        \n        auto fr = self(self, n_p, q);\n        // interpolate\n\
    \        std::vector<int> ans(n);\n        int l = 0, r = 0;\n        \n     \
    \   for (int i = 0; i < n; i++){\n            if(i & 1){\n                ans[i]\
    \ = fr[i / 2];\n                l = r;\n            } else {\n               \
    \ if (i + 1 != n) {\n                    while (q[r] != fr[i / 2]) r++;\n    \
    \            } else {\n                    r = m - 1;\n                }\n   \
    \             ans[i] = q[l];\n                for (int j = l + 1; j <= r; j++){\n\
    \                    if(select(p[i], ans[i], q[j])){\n                       \
    \ ans[i] = q[j];\n                    }\n                }\n            }\n  \
    \      }\n        return ans;\n    };\n    std::vector<int> P(N), Q(M);\n    std::iota(P.begin(),\
    \ P.end(), 0);\n    std::iota(Q.begin(), Q.end(), 0);\n    return f(f, P, Q);\n\
    }\n}\n#line 6 \"algorithm/monge_k_edge_shortest_path.hpp\"\n\nnamespace po167\
    \ {\n\n// f: {(i,j) | 0 <= i < j <= n} -> long long, 0 <= k <= n.\n// f(a,c) +\
    \ f(b,d) <= f(a,d) + f(b,c)  (a < b < c < d).\n// ans[d] = min_{0 = v_0 < ...\
    \ < v_d = n} sum_{t=1}^d f(v_{t-1},v_t), 1 <= d <= k.\n// ans[0] \u306F\u672A\u4F7F\
    \u7528\u3002\u5404 ans[d] \u306F long long\u3001\u5168 DP \u5024\u30FB\u5019\u88DC\
    \u5024\u306F T \u306B\u53CE\u307E\u308B\u3053\u3068\u3002\n// f \u304C O(1) \u306E\
    \u3068\u304D\u3001\u6642\u9593 O(nk)\u3001\u8FFD\u52A0\u30E1\u30E2\u30EA O(n)\u3002\
    \ntemplate <class T = __int128_t, class F>\nstd::vector<long long> monge_k_edge_shortest_path(int\
    \ n, int k, const F& f) {\n    assert(0 <= k && k <= n);\n    std::vector<long\
    \ long> answer(k + 1);\n    if (k == 0) return answer;\n    answer[1] = f(0, n);\n\
    \    if (k == 1) return answer;\n\n    std::vector<T> prev(n + 1), next(n + 1);\n\
    \    for (int j = 1; j < n; ++j) prev[j] = T(f(0, j));\n    prev[n] = T(answer[1]);\n\
    \    for (int d = 2; d <= k; ++d) {\n        int size = n - d + 1;\n        auto\
    \ argmin = po167::smawk(size, size, [&](int r, int a, int b) {\n            int\
    \ j = r + d, i = a + d - 1, h = b + d - 1;\n            return h < j && prev[h]\
    \ + T(f(h, j)) < prev[i] + T(f(i, j));\n        });\n        for (int j = d; j\
    \ <= n; ++j) {\n            int i = argmin[j - d] + d - 1;\n            next[j]\
    \ = prev[i] + T(f(i, j));\n        }\n        answer[d] = (long long)next[n];\n\
    \        prev.swap(next);\n    }\n    return answer;\n}\n\n}  // namespace po167\n\
    #line 5 \"test/algorithm/monge_1.test.cpp\"\n#include <iostream>\n#line 7 \"test/algorithm/monge_1.test.cpp\"\
    \n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<long long> S(N + 1);\n    for\
    \ (int i = 0; i < N; i++){\n        std::cin >> S[i + 1];\n        S[i + 1] +=\
    \ S[i];\n    }\n\n    auto cost = [&](int i, int j){\n        long long s = S[j\
    \ - 1] - S[i];\n        return s * s;\n    };\n    auto ans = po167::monge_k_edge_shortest_path<long\
    \ long>(N + 1, N, cost);\n\n    // Selected edge counts are computed by the fixed-D\
    \ function.\n    std::vector<bool> check(N + 1);\n    for (int t = 0; t < 32;\
    \ t++) check[1 + (N - 1) * t / 31] = true;\n    if (N >= 2) check[2] = check[N\
    \ - 1] = true;\n    for (int d = 1; d <= N; d++){\n        if (check[d]) ans[d]\
    \ = po167::monge_d_edge_shortest_path(N + 1, d, cost);\n    }\n    for (int k\
    \ = 1; k <= N; k++){\n        std::cout << ans[N + 1 - k] << \"\\n\";\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/952\"\n\n#include \"../../algorithm/monge_d_edge_shortest_path.hpp\"\
    \n#include \"../../algorithm/monge_k_edge_shortest_path.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<long long> S(N + 1);\n    for\
    \ (int i = 0; i < N; i++){\n        std::cin >> S[i + 1];\n        S[i + 1] +=\
    \ S[i];\n    }\n\n    auto cost = [&](int i, int j){\n        long long s = S[j\
    \ - 1] - S[i];\n        return s * s;\n    };\n    auto ans = po167::monge_k_edge_shortest_path<long\
    \ long>(N + 1, N, cost);\n\n    // Selected edge counts are computed by the fixed-D\
    \ function.\n    std::vector<bool> check(N + 1);\n    for (int t = 0; t < 32;\
    \ t++) check[1 + (N - 1) * t / 31] = true;\n    if (N >= 2) check[2] = check[N\
    \ - 1] = true;\n    for (int d = 1; d <= N; d++){\n        if (check[d]) ans[d]\
    \ = po167::monge_d_edge_shortest_path(N + 1, d, cost);\n    }\n    for (int k\
    \ = 1; k <= N; k++){\n        std::cout << ans[N + 1 - k] << \"\\n\";\n    }\n\
    }\n"
  dependsOn:
  - algorithm/monge_d_edge_shortest_path.hpp
  - algorithm/larsch.hpp
  - algorithm/monge_k_edge_shortest_path.hpp
  - algorithm/smawk.hpp
  isVerificationFile: true
  path: test/algorithm/monge_1.test.cpp
  requiredBy: []
  timestamp: '2026-10-21 23:29:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/algorithm/monge_1.test.cpp
layout: document
redirect_from:
- /verify/test/algorithm/monge_1.test.cpp
- /verify/test/algorithm/monge_1.test.cpp.html
title: test/algorithm/monge_1.test.cpp
---
