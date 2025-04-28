---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/Binomial.hpp
    title: "\u4E8C\u9805\u4FC2\u6570\u95A2\u9023"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/q_Binomial.test.cpp
    title: test/math/q_Binomial.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/q_Binomial.hpp\"\n\n#line 2 \"math/Binomial.hpp\"\n\
    \n#include<vector>\n#include<assert.h>\n\nnamespace po167{\ntemplate<class T>\n\
    struct Binomial{\n    std::vector<T> fact_vec, fact_inv_vec;\n    void extend(int\
    \ m = -1){\n        int n = fact_vec.size();\n        if (m == -1) m = n * 2;\n\
    \        if (n >= m) return;\n        fact_vec.resize(m);\n        fact_inv_vec.resize(m);\n\
    \        for (int i = n; i < m; i++){\n            fact_vec[i] = fact_vec[i -\
    \ 1] * T(i);\n        }\n        fact_inv_vec[m - 1] = T(1) / fact_vec[m - 1];\n\
    \        for (int i = m - 1; i > n; i--){\n            fact_inv_vec[i - 1] = fact_inv_vec[i]\
    \ * T(i);\n        }\n    }\n    Binomial(int MAX = 0){\n        fact_vec.resize(1,\
    \ T(1));\n        fact_inv_vec.resize(1, T(1));\n        extend(MAX + 1);\n  \
    \  }\n\n    T fact(int i){\n        if (i < 0) return 0;\n        while (int(fact_vec.size())\
    \ <= i) extend();\n        return fact_vec[i];\n    }\n    T invfact(int i){\n\
    \        if (i < 0) return 0;\n        while (int(fact_inv_vec.size()) <= i) extend();\n\
    \        return fact_inv_vec[i];\n    }\n    T C(int a, int b){\n        if (a\
    \ < b || b < 0) return 0;\n        return fact(a) * invfact(b) * invfact(a - b);\n\
    \    }\n    T invC(int a, int b){\n        if (a < b || b < 0) return 0;\n   \
    \     return fact(b) * fact(a - b) *invfact(a);\n    }\n    T P(int a, int b){\n\
    \        if (a < b || b < 0) return 0;\n        return fact(a) * invfact(a - b);\n\
    \    }\n    T inv(int a){\n        if (a < 0) return inv(-a) * T(-1);\n      \
    \  if (a == 0) return 1;\n        return fact(a - 1) * invfact(a);\n    }\n  \
    \  T Catalan(int n){\n        if (n < 0) return 0;\n        return fact(2 * n)\
    \ * invfact(n + 1) * invfact(n);\n    }\n    T narayana(int n, int k){\n     \
    \   if (n <= 0 || n < k || k < 1) return 0;\n        return C(n, k) *  C(n, k\
    \ - 1) * inv(n);\n    }\n    T Catalan_pow(int n,int d){\n        if (n < 0 ||\
    \ d < 0) return 0;\n        if (d == 0){\n            if (n == 0) return 1;\n\
    \            return 0;\n        }\n        return T(d) * inv(d + n) * C(2 * n\
    \ + d - 1, n);\n    }\n    // retrun [x^a] 1/(1-x)^b\n    T ruiseki(int a,int\
    \ b){\n        if (a < 0 || b < 0) return 0;\n        if (a == 0){\n         \
    \   return 1;\n        }\n        return C(a + b - 1, b - 1);\n    }\n    // (a,\
    \ b) -> (c, d)\n    // always x + e >= y\n    T mirror(int a, int b, int c, int\
    \ d, int e = 0){\n        if (a + e < b || c + e < d) return 0;\n        if (a\
    \ > c || b > d) return 0;\n        a += e;\n        c += e;\n        return C(c\
    \ + d - a - b, c - a) - C(c + d - a - b, c - b + 1); \n    }\n    // return sum_{i\
    \ = 0, ... , a} sum_{j = 0, ... , b} C(i + j, i)\n    // return C(a + b + 2, a\
    \ + 1) - 1;\n    T gird_sum(int a, int b){\n        if (a < 0 || b < 0) return\
    \ 0;\n        return C(a + b + 2, a + 1) - 1;\n    }\n    // return sum_{i = a,\
    \ ..., b - 1} sum_{j = c, ... , d - 1} C(i + j, i)\n    // AGC 018 E\n    T gird_sum_2(int\
    \ a, int b, int c, int d){\n        if (a >= b || c >= d) return 0;\n        a--,\
    \ b--, c--, d--;\n        return gird_sum(a, c) - gird_sum(a, d) - gird_sum(b,\
    \ c) + gird_sum(b, d);\n    }\n\n    // the number of diagonal dissections of\
    \ a convex n-gon into k+1 regions.\n    // OEIS A033282\n    // AGC065D\n    T\
    \ diagonal(int n, int k){\n        if (n <= 2 || n - 3 < k || k < 0) return 0;\n\
    \        return C(n - 3, k) * C(n + k - 1, k) * inv(k + 1);\n    }\n};\n}\n#line\
    \ 4 \"math/q_Binomial.hpp\"\n\nnamespace po167{\ntemplate<class T>\nstruct q_Binomial{\n\
    \    std::vector<T> q_pow, q_sum, fact_vec, fact_inv_vec;\n    T q;\n    int lim;\n\
    \    int mod;\n    Binomial<T> table;\n    q_Binomial(int q_, int mod_, int lim_\
    \ = 10'000'100){\n        q = q_;\n        mod = mod_;\n        lim = lim_;\n\
    \        table.extend(std::min(lim + 1, mod));\n        q_pow.resize(lim, T(1));\n\
    \        q_sum.resize(lim, T(0));\n        for (int i = 1; i < lim; i++){\n  \
    \          q_pow[i] = q_pow[i - 1] * q;\n            q_sum[i] = q_sum[i - 1] +\
    \ q_pow[i - 1];\n            if (q_pow[i] == 1){\n                lim = i;\n \
    \               q_pow.resize(lim);\n                q_sum.resize(lim);\n     \
    \           break;\n            }\n        }\n        fact_vec.resize(lim, T(1));\n\
    \        fact_inv_vec.resize(lim, T(1));\n        for (int i = 1; i < lim; i++){\n\
    \            fact_vec[i] = fact_vec[i - 1] * q_sum[i];\n        }\n        fact_inv_vec.back()\
    \ = (T)(1) / (T)(fact_vec.back());\n        for (int i = lim - 1; i > 0; i--){\n\
    \            fact_inv_vec[i - 1] = fact_inv_vec[i] * q_sum[i];\n        }\n  \
    \  }\n    T fact(long long i){\n        if (i < 0 || lim <= i) return 0;\n   \
    \     return fact_vec[i];\n    }\n    T invfact(long long i){\n        if (i <\
    \ 0 || lim <= i) return 0;\n        return fact_inv_vec[i];\n    }\n    T aCb(long\
    \ long a, long long b){\n        if (a < b || b < 0) return 0;\n        if (a\
    \ < mod) return table.C(a, b);\n        return table.C(a % mod, b % mod) * aCb(a\
    \ / mod, b / mod);\n    }\n    T C(long long a, long long b){\n        if (a <\
    \ b || b < 0) return 0;\n        if (a < lim) return fact(a) * invfact(b) * invfact(a\
    \ - b);\n        return C(a % lim, b % lim) * aCb(a / lim, b / lim);\n    }\n\
    };\n}\n"
  code: "#pragma once\n\n#include \"Binomial.hpp\"\n\nnamespace po167{\ntemplate<class\
    \ T>\nstruct q_Binomial{\n    std::vector<T> q_pow, q_sum, fact_vec, fact_inv_vec;\n\
    \    T q;\n    int lim;\n    int mod;\n    Binomial<T> table;\n    q_Binomial(int\
    \ q_, int mod_, int lim_ = 10'000'100){\n        q = q_;\n        mod = mod_;\n\
    \        lim = lim_;\n        table.extend(std::min(lim + 1, mod));\n        q_pow.resize(lim,\
    \ T(1));\n        q_sum.resize(lim, T(0));\n        for (int i = 1; i < lim; i++){\n\
    \            q_pow[i] = q_pow[i - 1] * q;\n            q_sum[i] = q_sum[i - 1]\
    \ + q_pow[i - 1];\n            if (q_pow[i] == 1){\n                lim = i;\n\
    \                q_pow.resize(lim);\n                q_sum.resize(lim);\n    \
    \            break;\n            }\n        }\n        fact_vec.resize(lim, T(1));\n\
    \        fact_inv_vec.resize(lim, T(1));\n        for (int i = 1; i < lim; i++){\n\
    \            fact_vec[i] = fact_vec[i - 1] * q_sum[i];\n        }\n        fact_inv_vec.back()\
    \ = (T)(1) / (T)(fact_vec.back());\n        for (int i = lim - 1; i > 0; i--){\n\
    \            fact_inv_vec[i - 1] = fact_inv_vec[i] * q_sum[i];\n        }\n  \
    \  }\n    T fact(long long i){\n        if (i < 0 || lim <= i) return 0;\n   \
    \     return fact_vec[i];\n    }\n    T invfact(long long i){\n        if (i <\
    \ 0 || lim <= i) return 0;\n        return fact_inv_vec[i];\n    }\n    T aCb(long\
    \ long a, long long b){\n        if (a < b || b < 0) return 0;\n        if (a\
    \ < mod) return table.C(a, b);\n        return table.C(a % mod, b % mod) * aCb(a\
    \ / mod, b / mod);\n    }\n    T C(long long a, long long b){\n        if (a <\
    \ b || b < 0) return 0;\n        if (a < lim) return fact(a) * invfact(b) * invfact(a\
    \ - b);\n        return C(a % lim, b % lim) * aCb(a / lim, b / lim);\n    }\n\
    };\n}\n"
  dependsOn:
  - math/Binomial.hpp
  isVerificationFile: false
  path: math/q_Binomial.hpp
  requiredBy: []
  timestamp: '2024-11-28 11:40:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/q_Binomial.test.cpp
documentation_of: math/q_Binomial.hpp
layout: document
redirect_from:
- /library/math/q_Binomial.hpp
- /library/math/q_Binomial.hpp.html
title: math/q_Binomial.hpp
---
