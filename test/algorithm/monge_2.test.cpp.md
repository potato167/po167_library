---
data:
  _extendedDependsOn:
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
  bundledCode: "#line 1 \"test/algorithm/monge_2.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/952\"\
    \n\n#line 2 \"algorithm/monge_k_edge_shortest_path.hpp\"\n// po167 Monge library\
    \ v2 (2026-10-21)\n#include <cassert>\n#include <vector>\n#line 3 \"algorithm/smawk.hpp\"\
    \n#include <numeric>\nnamespace po167{\n// return argmax\n// \n// https://noshi91.github.io/Library/algorithm/smawk.cpp\n\
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
    #line 4 \"test/algorithm/monge_2.test.cpp\"\n#include <iostream>\n#line 6 \"test/algorithm/monge_2.test.cpp\"\
    \n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<long long> S(N + 1);\n    for\
    \ (int i = 0; i < N; ++i){\n        std::cin >> S[i + 1];\n        S[i + 1] +=\
    \ S[i];\n    }\n\n    auto cost = [&](int i, int j){\n        long long sum =\
    \ S[j - 1] - S[i];\n        return sum * sum;\n    };\n\n    auto ans = po167::monge_k_edge_shortest_path<long\
    \ long>(N + 1, N, cost);\n    for (int k = 1; k <= N; ++k){\n        std::cout\
    \ << ans[N - k + 1] << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/952\"\n\n#include \"../../algorithm/monge_k_edge_shortest_path.hpp\"\
    \n#include <iostream>\n#include <vector>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int N;\n    std::cin >> N;\n    std::vector<long\
    \ long> S(N + 1);\n    for (int i = 0; i < N; ++i){\n        std::cin >> S[i +\
    \ 1];\n        S[i + 1] += S[i];\n    }\n\n    auto cost = [&](int i, int j){\n\
    \        long long sum = S[j - 1] - S[i];\n        return sum * sum;\n    };\n\
    \n    auto ans = po167::monge_k_edge_shortest_path<long long>(N + 1, N, cost);\n\
    \    for (int k = 1; k <= N; ++k){\n        std::cout << ans[N - k + 1] << \"\\\
    n\";\n    }\n}\n"
  dependsOn:
  - algorithm/monge_k_edge_shortest_path.hpp
  - algorithm/smawk.hpp
  isVerificationFile: true
  path: test/algorithm/monge_2.test.cpp
  requiredBy: []
  timestamp: '2026-10-21 23:29:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/algorithm/monge_2.test.cpp
layout: document
redirect_from:
- /verify/test/algorithm/monge_2.test.cpp
- /verify/test/algorithm/monge_2.test.cpp.html
title: test/algorithm/monge_2.test.cpp
---
