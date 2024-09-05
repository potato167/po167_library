---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/Taylor_Shift.hpp
    title: fps/Taylor_Shift.hpp
  - icon: ':heavy_check_mark:'
    path: math/Binomial.hpp
    title: "\u4E8C\u9805\u4FC2\u6570\u95A2\u9023"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/polynomial_taylor_shift
    links:
    - https://judge.yosupo.jp/problem/polynomial_taylor_shift
  bundledCode: "#line 1 \"test/fps/taylor_shift.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\
    \n\n#line 2 \"fps/Taylor_Shift.hpp\"\n\n#include <atcoder/convolution>\n#line\
    \ 2 \"math/Binomial.hpp\"\n\n#include<vector>\n#include<assert.h>\n\nnamespace\
    \ po167{\ntemplate<class T>\nstruct Binomial{\n    std::vector<T> fact_vec, fact_inv_vec;\n\
    \    void extend(int m = -1){\n        int n = fact_vec.size();\n        if (m\
    \ == -1) m = n * 2;\n        if (n >= m) return;\n        fact_vec.resize(m);\n\
    \        fact_inv_vec.resize(m);\n        for (int i = n; i < m; i++){\n     \
    \       fact_vec[i] = fact_vec[i - 1] * T(i);\n        }\n        fact_inv_vec[m\
    \ - 1] = T(1) / fact_vec[m - 1];\n        for (int i = m - 1; i > n; i--){\n \
    \           fact_inv_vec[i - 1] = fact_inv_vec[i] * T(i);\n        }\n    }\n\
    \    Binomial(int MAX = 0){\n        fact_vec.resize(1, T(1));\n        fact_inv_vec.resize(1,\
    \ T(1));\n        extend(MAX + 1);\n    }\n\n    T fact(int i){\n        if (i\
    \ < 0) return 0;\n        while (int(fact_vec.size()) <= i) extend();\n      \
    \  return fact_vec[i];\n    }\n    T invfact(int i){\n        if (i < 0) return\
    \ 0;\n        while (int(fact_inv_vec.size()) <= i) extend();\n        return\
    \ fact_inv_vec[i];\n    }\n    T C(int a, int b){\n        if (a < b || b < 0)\
    \ return 0;\n        return fact(a) * invfact(b) * invfact(a - b);\n    }\n  \
    \  T invC(int a, int b){\n        if (a < b || b < 0) return 0;\n        return\
    \ fact(b) * fact(a - b) *invfact(a);\n    }\n    T P(int a, int b){\n        if\
    \ (a < b || b < 0) return 0;\n        return fact(a) * invfact(a - b);\n    }\n\
    \    T inv(int a){\n        if (a < 0) return inv(-a) * T(-1);\n        if (a\
    \ == 0) return 1;\n        return fact(a - 1) * invfact(a);\n    }\n    T Catalan(int\
    \ n){\n        if (n < 0) return 0;\n        return fact(2 * n) * invfact(n +\
    \ 1) * invfact(n);\n    }\n    T narayana(int n, int k){\n        if (n <= 0 ||\
    \ n < k || k < 1) return 0;\n        return C(n, k) *  C(n, k - 1) * inv(n);\n\
    \    }\n    T Catalan_pow(int n,int d){\n        if (n < 0 || d < 0) return 0;\n\
    \        if (d == 0){\n            if (n == 0) return 1;\n            return 0;\n\
    \        }\n        return T(d) * inv(d + n) * C(2 * n + d - 1, n);\n    }\n \
    \   // retrun [x^a] 1/(1-x)^b\n    T ruiseki(int a,int b){\n        if (a < 0\
    \ || b < 0) return 0;\n        if (a == 0){\n            return 1;\n        }\n\
    \        return C(a + b - 1, b - 1);\n    }\n    // (a, b) -> (c, d)\n    // always\
    \ x + e >= y\n    T mirror(int a, int b, int c, int d, int e = 0){\n        if\
    \ (a + e < b || c + e < d) return 0;\n        if (a > c || b > d) return 0;\n\
    \        a += e;\n        c += e;\n        return C(c + d - a - b, c - a) - C(c\
    \ + d - a - b, c - b + 1); \n    }\n    // return sum_{i = 0, ... , a} sum_{j\
    \ = 0, ... , b} C(i + j, i)\n    // return C(a + b + 2, a + 1) - 1;\n    T gird_sum(int\
    \ a, int b){\n        if (a < 0 || b < 0) return 0;\n        return C(a + b +\
    \ 2, a + 1) - 1;\n    }\n    // return sum_{i = a, ..., b - 1} sum_{j = c, ...\
    \ , d - 1} C(i + j, i)\n    // AGC 018 E\n    T gird_sum_2(int a, int b, int c,\
    \ int d){\n        if (a >= b || c >= d) return 0;\n        a--, b--, c--, d--;\n\
    \        return gird_sum(a, c) - gird_sum(a, d) - gird_sum(b, c) + gird_sum(b,\
    \ d);\n    }\n};\n}\n#line 5 \"fps/Taylor_Shift.hpp\"\n\nnamespace po167{\n//\
    \ return f(x + c)\ntemplate<class T>\nstd::vector<T> Taylor_Shift(\n    std::vector<T>\
    \ f, T c\n){\n    int n = f.size();\n    Binomial<T> table(n);\n    std::vector<T>\
    \ g(n);\n    T tmp = 1;\n    for (int i = 0; i < n; i++){\n        g[n - 1 - i]\
    \ = table.invfact(i) * tmp;\n        tmp *= c;\n        f[i] *= table.fact(i);\n\
    \    }\n    // using cyclic convolution is faster ? \n    g = atcoder::convolution(f,\
    \ g);\n    std::vector<T> res(n);\n    for (int i = 0; i < n; i++){\n        res[i]\
    \ = table.invfact(i) * g[n + i - 1];\n    }\n    return res;\n}\n}\n#line 4 \"\
    test/fps/taylor_shift.test.cpp\"\n\n#include <iostream>\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = atcoder::modint998244353;\n\n  \
    \  int N, c, a;\n    std::cin >> N >> c;\n    std::vector<mint> f(N);\n    for\
    \ (auto &x : f){\n        std::cin >> a;\n        x = a;\n    }\n    f = po167::Taylor_Shift(f,\
    \ (mint)(c));\n    for (int i = 0; i < N; i++){\n        std::cout << f[i].val()\
    \ << (i + 1 == N ? \"\\n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\
    \n\n#include \"../../fps/Taylor_Shift.hpp\"\n\n#include <iostream>\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    using\
    \ mint = atcoder::modint998244353;\n\n    int N, c, a;\n    std::cin >> N >> c;\n\
    \    std::vector<mint> f(N);\n    for (auto &x : f){\n        std::cin >> a;\n\
    \        x = a;\n    }\n    f = po167::Taylor_Shift(f, (mint)(c));\n    for (int\
    \ i = 0; i < N; i++){\n        std::cout << f[i].val() << (i + 1 == N ? \"\\n\"\
    \ : \" \");\n    }\n}"
  dependsOn:
  - fps/Taylor_Shift.hpp
  - math/Binomial.hpp
  isVerificationFile: true
  path: test/fps/taylor_shift.test.cpp
  requiredBy: []
  timestamp: '2024-09-05 20:21:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/taylor_shift.test.cpp
layout: document
redirect_from:
- /verify/test/fps/taylor_shift.test.cpp
- /verify/test/fps/taylor_shift.test.cpp.html
title: test/fps/taylor_shift.test.cpp
---
