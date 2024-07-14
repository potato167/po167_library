---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/sum_max_convolution.hpp
    title: algorithm/sum_max_convolution.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algorithm/sum_min_conv.test.cpp
    title: test/algorithm/sum_min_conv.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.github.io/Library/algorithm/smawk.cpp
  bundledCode: "#line 2 \"algorithm/smawk.hpp\"\n#include <vector>\n#include <numeric>\n\
    namespace po167{\n// return argmax\n// \n// https://noshi91.github.io/Library/algorithm/smawk.cpp\n\
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
    }\n}\n"
  code: "#pragma once\n#include <vector>\n#include <numeric>\nnamespace po167{\n//\
    \ return argmax\n// \n// https://noshi91.github.io/Library/algorithm/smawk.cpp\n\
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
    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: algorithm/smawk.hpp
  requiredBy:
  - algorithm/sum_max_convolution.hpp
  timestamp: '2024-07-15 01:01:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/algorithm/sum_min_conv.test.cpp
documentation_of: algorithm/smawk.hpp
layout: document
redirect_from:
- /library/algorithm/smawk.hpp
- /library/algorithm/smawk.hpp.html
title: algorithm/smawk.hpp
---
