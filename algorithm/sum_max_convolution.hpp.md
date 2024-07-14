---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: algorithm/smawk.hpp
    title: algorithm/smawk.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/algorithm/sum_min_conv.test.cpp
    title: test/algorithm/sum_min_conv.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"algorithm/sum_max_convolution.hpp\"\n#include <vector>\n\
    #include <algorithm>\n#line 3 \"algorithm/smawk.hpp\"\n#include <numeric>\nnamespace\
    \ po167{\n// return argmax\n// \n// https://noshi91.github.io/Library/algorithm/smawk.cpp\n\
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
    }\n}\n#line 5 \"algorithm/sum_max_convolution.hpp\"\n\nnamespace po167{\n// X\
    \ is convex upward\ntemplate<class T>\nstd::vector<T> sum_max_convolution(std::vector<T>\
    \ X, std::vector<T> Y){\n    int n = X.size();\n    int m = Y.size();\n    std::vector<T>\
    \ ans(n + m - 1);\n    auto get = [&](int i, int j) -> T {\n        return X[i\
    \ - j] + Y[j];\n    };\n    auto select = [&](int i, int j1, int j2) -> bool {\n\
    \        if (i < j2) return false;\n        if (i - j1 >= n) return true;\n  \
    \      return get(i, j1) <= get(i, j2);\n    };\n    const int D = 10;\n    if\
    \ (std::min(n, m) <= D) {\n        for (int i = 0; i < n + m - 1; i++){\n    \
    \        int ind = std::max(0, i - n);\n            for (int j = ind + 1; j <\
    \ m && j <= i; j++){\n                if (select(i, ind, j)) ind = j;\n      \
    \      }\n            ans[i] = get(i, ind);\n        }\n        return ans;\n\
    \    }\n    std::vector<int> res = smawk(n + m - 1, m, select);\n    for (int\
    \ i = 0; i < n + m - 1; i++){\n        ans[i] = get(i, res[i]);\n    }\n    return\
    \ ans;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <algorithm>\n#include \"smawk.hpp\"\
    \n\nnamespace po167{\n// X is convex upward\ntemplate<class T>\nstd::vector<T>\
    \ sum_max_convolution(std::vector<T> X, std::vector<T> Y){\n    int n = X.size();\n\
    \    int m = Y.size();\n    std::vector<T> ans(n + m - 1);\n    auto get = [&](int\
    \ i, int j) -> T {\n        return X[i - j] + Y[j];\n    };\n    auto select =\
    \ [&](int i, int j1, int j2) -> bool {\n        if (i < j2) return false;\n  \
    \      if (i - j1 >= n) return true;\n        return get(i, j1) <= get(i, j2);\n\
    \    };\n    const int D = 10;\n    if (std::min(n, m) <= D) {\n        for (int\
    \ i = 0; i < n + m - 1; i++){\n            int ind = std::max(0, i - n);\n   \
    \         for (int j = ind + 1; j < m && j <= i; j++){\n                if (select(i,\
    \ ind, j)) ind = j;\n            }\n            ans[i] = get(i, ind);\n      \
    \  }\n        return ans;\n    }\n    std::vector<int> res = smawk(n + m - 1,\
    \ m, select);\n    for (int i = 0; i < n + m - 1; i++){\n        ans[i] = get(i,\
    \ res[i]);\n    }\n    return ans;\n}\n}"
  dependsOn:
  - algorithm/smawk.hpp
  isVerificationFile: false
  path: algorithm/sum_max_convolution.hpp
  requiredBy: []
  timestamp: '2024-07-15 01:01:03+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/algorithm/sum_min_conv.test.cpp
documentation_of: algorithm/sum_max_convolution.hpp
layout: document
redirect_from:
- /library/algorithm/sum_max_convolution.hpp
- /library/algorithm/sum_max_convolution.hpp.html
title: algorithm/sum_max_convolution.hpp
---
