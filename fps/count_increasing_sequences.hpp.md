---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: math/Binomial.hpp
    title: "\u4E8C\u9805\u4FC2\u6570\u95A2\u9023"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/count_increasing_sequences.test.cpp
    title: test/fps/count_increasing_sequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/count_increasing_sequences.hpp\"\n#include <atcoder/convolution>\n\
    #line 2 \"math/Binomial.hpp\"\n\n#include<vector>\n#include<assert.h>\n\nnamespace\
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
    \ d);\n    }\n\n    // the number of diagonal dissections of a convex n-gon into\
    \ k+1 regions.\n    // OEIS A033282\n    // AGC065D\n    T diagonal(int n, int\
    \ k){\n        if (n <= 2 || n - 3 < k || k < 0) return 0;\n        return C(n\
    \ - 3, k) * C(n + k - 1, k) * inv(k + 1);\n    }\n};\n}\n#line 4 \"fps/FPS_cyclic_convolution.hpp\"\
    \n\nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class T>\nstd::vector<T>\
    \ FPS_cyclic_convolution(std::vector<T> f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n\
    \    atcoder::internal::butterfly(g);\n    for (int i = 0; i < (int)f.size();\
    \ i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n    T iz = (T)(1)\
    \ / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++) f[i] *= iz;\n\
    \    return f;\n}\n}\n#line 5 \"fps/count_increasing_sequences.hpp\"\nnamespace\
    \ po167{\ntemplate<class T>\nstd::pair<std::vector<T>, std::vector<T>> count_square(std::vector<T>\
    \ L, std::vector<T> D){\n    assert(!L.empty() && !D.empty());\n    int N = L.size();\n\
    \    int M = D.size();\n    if (std::min(N, M) <= 60){\n        int sw = 0;\n\
    \        if (N > M) std::swap(N, M), std::swap(L, D), sw = 1;\n        std::vector<T>\
    \ R(N);\n        for (int i = 0; i < N; i++){\n            D[0] += L[i];\n   \
    \         for (int j = 1; j < M; j++) D[j] += D[j - 1];\n            R[i] = D.back();\n\
    \        }\n        if (sw) std::swap(R, D);\n        return {R, D};\n    }\n\
    \    po167::Binomial<T> table(N + M);\n    std::vector<T> R(N), U(M);\n    int\
    \ z = 0;\n    while ((1 << z) < (N + M - 1)) z++;\n    // \u5DE6\u304B\u3089\u53F3\
    \n    {\n        std::vector<T> tmp(N);\n        for (int i = 0; i < N; i++) tmp[i]\
    \ = table.C(M - 1 + i, i);\n        tmp = atcoder::convolution(tmp, L);\n    \
    \    for (int i = 0; i < N; i++) R[i] += tmp[i];\n    }\n    // \u5DE6\u304B\u3089\
    \u4E0A\n    {\n        std::vector<T> tmp(1 << z);\n        for (int i = 0; i\
    \ < N; i++) L[i] *= table.invfact(N - 1 - i);\n        for (int i = 0; i < N +\
    \ M - 1; i++) tmp[i] = table.fact(i);\n        L.resize(1 << z, 0);\n        tmp\
    \ = po167::FPS_cyclic_convolution(tmp, L);\n        for (int i = 0; i < M; i++)\
    \ U[i] += tmp[N - 1 + i] * table.invfact(i);\n    }\n    // \u4E0B\u304B\u3089\
    \u4E0A\n    {\n        std::vector<T> tmp(M);\n        for (int i = 0; i < M;\
    \ i++) tmp[i] = table.C(N - 1 + i, i);\n        tmp = atcoder::convolution(tmp,\
    \ D);\n        for (int i = 0; i < M; i++) U[i] += tmp[i];\n    }\n    // \u4E0B\
    \u304B\u3089\u53F3\n    {\n        std::vector<T> tmp(1 << z);\n        for (int\
    \ i = 0; i < M; i++) D[i] *= table.invfact(M - i - 1);\n        for (int i = 0;\
    \ i < N + M - 1; i++) tmp[i] = table.fact(i);\n        D.resize(1 << z, 0);\n\
    \        tmp = po167::FPS_cyclic_convolution(tmp, D);\n        for (int i = 0;\
    \ i < N; i++) R[i] += tmp[M - 1 + i] * table.invfact(i);\n    }\n    return {R,\
    \ U};\n}\ntemplate<class T>\n/*\n * g(A, x) \u3092\n * 0 <= B[i] < A[i] \u304B\
    \u3064 B[i] = x \u3092\u6E80\u305F\u3059\n * \u5E83\u7FA9\u5358\u8ABF\u5897\u52A0\
    \u5217 B \u306E\u6570\u3068\u3059\u308B\n * res[x] = sum C[i] * g(A[i:N], x)\n\
    \ * \u3092\u8FD4\u3059\n */\nstd::vector<T> count_increase_sequences_with_upper_bounds(std::vector<int>\
    \ A, std::vector<T> C){\n    int N = A.size();\n    assert((int)C.size() == N);\n\
    \    assert(N);\n    for (int i = (int)(A.size()) - 1; i > 0; i--) A[i - 1] =\
    \ std::min(A[i - 1], A[i]);\n    if (A.back() == 0) return {};\n    if (N == 1){\n\
    \        std::vector<T> res(A[0]);\n        for (int i = 0; i < A[0]; i++) res[i]\
    \ = C[0];\n        return res;\n    }\n    int m = N / 2;\n    std::vector<int>\
    \ LA(m), RA(N - m);\n    std::vector<T> LC(m), RC(N - m);\n    for (int i = 0;\
    \ i < m; i++){\n        LA[i] = A[i];\n        LC[i] = C[i];\n    }\n    for (int\
    \ i = 0; i < N - m; i++){\n        RA[i] = A[i + m] - A[m - 1];\n        RC[i]\
    \ = C[i + m];\n    }\n    std::vector<T> res;\n    res.reserve(A.back());\n  \
    \  auto L = count_increase_sequences_with_upper_bounds(LA, LC);\n    if (!L.empty()){\n\
    \        auto [R, U] = count_square(L, RC);\n        for (int i = 0; i < (int)R.size();\
    \ i++) res.push_back(R[i]);\n        std::swap(U, RC);\n    }\n    auto R = count_increase_sequences_with_upper_bounds(RA,\
    \ RC);\n    for (auto x : R) res.push_back(x);\n    return res;\n}\ntemplate<class\
    \ T>\nstd::vector<T> NAIVE_count_increase_sequences_with_upper_lower_bounds(std::vector<int>\
    \ A, std::vector<int> B, std::vector<T> C = {}){\n    std::vector<T> tmp(B.back()\
    \ - A[0]);\n    if (C.empty()){\n        int b = B[0];\n        for (int i = 1;\
    \ i < (int)B.size(); i++) b = std::min(b, B[i]);\n        for (int i = 0; i <\
    \ b - A[0]; i++) tmp[i] = 1;\n    }\n    else for (int i = 0; i < (int)std::min(tmp.size(),\
    \ C.size()); i++) tmp[i] = C[i];\n    int N = A.size();\n    for (int i = 1; i\
    \ < N; i++){\n        for (int j = 1; j < (int)tmp.size(); j++){\n           \
    \ tmp[j] += tmp[j - 1];\n        }\n        for (int j = 0; j < (int)tmp.size();\
    \ j++){\n            if (j < A[i] - A[0] || B[i] - A[0] <= j) tmp[j] = 0;\n  \
    \      }\n    }\n    std::vector<T> res(B.back() - A.back());\n    for (int i\
    \ = 0; i < B.back() - A.back(); i++){\n        res[i] = tmp[A.back() - A[0] +\
    \ i];\n    }\n    return res;\n}\n\ntemplate<class T>\n/*\n * f(a, b) \u3092 X[0]\
    \ = a, X[N - 1] = b \u3067\u3042\u308B\u3088\u3046\u306A\u3001A, B \u306B\u631F\
    \u307E\u308C\u305F\u3082\u306E\u3068\u3059\u308B\n * \u9577\u3055 B[N - 1] - A[N\
    \ - 1] \u3092\u8FD4\u3059\n * res[b - A.back()] = sum C[a - A[0]] * f(a, b)\n\
    \ * A, B \u306F\u5E83\u7FA9\u5358\u8ABF\u5897\u52A0\u304C\u5B09\u3057\u3044\n\
    \ */\nstd::vector<T> count_increase_sequences_with_upper_lower_bounds(std::vector<int>\
    \ A, std::vector<int> B, std::vector<T> C = {}){\n    int N = A.size();\n    assert(A.size()\
    \ == B.size());\n    for (int i = 0; i < N - 1; i++){\n        A[i + 1] = std::max(A[i],\
    \ A[i + 1]);\n    }\n    for (int i = N - 1; i > 0; i--){\n        B[i - 1] =\
    \ std::min(B[i], B[i - 1]);\n    }\n    if (A.back() >= B.back()) return {};\n\
    \    // A[0] == 0 \u306B\u3059\u308B\n    std::vector<T> res(B.back() - A.back(),\
    \ 0);\n    {\n        int tmp = A[0];\n        for (int i = 0; i < N; i++){\n\
    \            A[i] -= tmp;\n            B[i] -= tmp;\n            if (A[i] >= B[i])\
    \ return res;\n        }\n    }\n    if (C.empty()){\n        C.resize(B[0] -\
    \ A[0], 1);\n    }\n    else assert((int)(C.size()) == B[0] - A[0]);\n    int\
    \ l = 0;\n    while (B[l] <= A.back()){\n        for (int i = (int)(C.size())\
    \ - 1; i > 0; i--) C[i] -= C[i - 1];\n        int nl = l;\n        while (A[nl]\
    \ < B[l]) nl++;\n        std::vector<int> tmp(B[l] - A[l]);\n        tmp[0] =\
    \ 1;\n        for (int i = l; i < nl; i++){\n            tmp[A[i] - A[l]]++;\n\
    \        }\n        for (int i = 1; i < B[l] - A[l]; i++) tmp[i] += tmp[i - 1];\n\
    \        auto X = count_increase_sequences_with_upper_bounds(tmp, C);\n      \
    \  std::vector<int> nB(nl - l + 1);\n        for (int i = l; i <= nl; i++){\n\
    \            nB[i - l] = B[i] - B[l];\n        }\n        auto Y = count_increase_sequences_with_upper_bounds(nB,\
    \ X);\n        C.resize(B[nl] - A[nl]);\n        for (int i = 0; i < B[nl] - A[nl];\
    \ i++){\n            C[i] = Y[i + A[nl] - B[l]];\n        }\n        l = nl;\n\
    \    }\n    // A \u3092\u63C3\u3048\u3066\u3057\u307E\u3048\n    {\n        int\
    \ a = A[l];\n        for (int i = l; i < N; i++){\n            A[i] -= a;\n  \
    \          B[i] -= a;\n        }\n    }\n    for (int i = (int)(C.size()) - 1;\
    \ i > 0; i--) C[i] -= C[i - 1];\n    std::vector<T> D(N - l, 0);\n    if (A.back()\
    \ != 0){\n        std::vector<T> L(A.back());\n        for (int i = 0; i < (int)L.size();\
    \ i++) L[i] = C[i];\n        std::vector<int> tmp(L.size());\n        tmp[0] =\
    \ 1;\n        for (int i = l; i < N; i++){\n            if (A[i] < (int)tmp.size())\
    \ tmp[A[i]]++;\n        }\n        for (int i = 1; i < (int)tmp.size(); i++){\n\
    \            tmp[i] += tmp[i - 1];\n        }\n        auto nD = count_increase_sequences_with_upper_bounds(tmp,\
    \ L);\n        for (int i = 0; i < (int)nD.size(); i++) D[i] = nD[i];\n    }\n\
    \    for (int i = A.back(); i < B[l]; i++) C[i - A.back()] = C[i];\n    C.resize(B[l]\
    \ - A.back());\n    auto [R, U] = count_square(C, D);\n    res = R;\n    std::vector<int>\
    \ nB(N - l);\n    for (int i = 0; i < N - l; i++) nB[i] = B[i + l] - B[l];\n \
    \   R = count_increase_sequences_with_upper_bounds(nB, U);\n    for (auto x :\
    \ R) res.push_back(x);\n    return res;\n}\n}\n"
  code: "#pragma once\n#include <atcoder/convolution>\n#include \"../math/Binomial.hpp\"\
    \n#include \"FPS_cyclic_convolution.hpp\"\nnamespace po167{\ntemplate<class T>\n\
    std::pair<std::vector<T>, std::vector<T>> count_square(std::vector<T> L, std::vector<T>\
    \ D){\n    assert(!L.empty() && !D.empty());\n    int N = L.size();\n    int M\
    \ = D.size();\n    if (std::min(N, M) <= 60){\n        int sw = 0;\n        if\
    \ (N > M) std::swap(N, M), std::swap(L, D), sw = 1;\n        std::vector<T> R(N);\n\
    \        for (int i = 0; i < N; i++){\n            D[0] += L[i];\n           \
    \ for (int j = 1; j < M; j++) D[j] += D[j - 1];\n            R[i] = D.back();\n\
    \        }\n        if (sw) std::swap(R, D);\n        return {R, D};\n    }\n\
    \    po167::Binomial<T> table(N + M);\n    std::vector<T> R(N), U(M);\n    int\
    \ z = 0;\n    while ((1 << z) < (N + M - 1)) z++;\n    // \u5DE6\u304B\u3089\u53F3\
    \n    {\n        std::vector<T> tmp(N);\n        for (int i = 0; i < N; i++) tmp[i]\
    \ = table.C(M - 1 + i, i);\n        tmp = atcoder::convolution(tmp, L);\n    \
    \    for (int i = 0; i < N; i++) R[i] += tmp[i];\n    }\n    // \u5DE6\u304B\u3089\
    \u4E0A\n    {\n        std::vector<T> tmp(1 << z);\n        for (int i = 0; i\
    \ < N; i++) L[i] *= table.invfact(N - 1 - i);\n        for (int i = 0; i < N +\
    \ M - 1; i++) tmp[i] = table.fact(i);\n        L.resize(1 << z, 0);\n        tmp\
    \ = po167::FPS_cyclic_convolution(tmp, L);\n        for (int i = 0; i < M; i++)\
    \ U[i] += tmp[N - 1 + i] * table.invfact(i);\n    }\n    // \u4E0B\u304B\u3089\
    \u4E0A\n    {\n        std::vector<T> tmp(M);\n        for (int i = 0; i < M;\
    \ i++) tmp[i] = table.C(N - 1 + i, i);\n        tmp = atcoder::convolution(tmp,\
    \ D);\n        for (int i = 0; i < M; i++) U[i] += tmp[i];\n    }\n    // \u4E0B\
    \u304B\u3089\u53F3\n    {\n        std::vector<T> tmp(1 << z);\n        for (int\
    \ i = 0; i < M; i++) D[i] *= table.invfact(M - i - 1);\n        for (int i = 0;\
    \ i < N + M - 1; i++) tmp[i] = table.fact(i);\n        D.resize(1 << z, 0);\n\
    \        tmp = po167::FPS_cyclic_convolution(tmp, D);\n        for (int i = 0;\
    \ i < N; i++) R[i] += tmp[M - 1 + i] * table.invfact(i);\n    }\n    return {R,\
    \ U};\n}\ntemplate<class T>\n/*\n * g(A, x) \u3092\n * 0 <= B[i] < A[i] \u304B\
    \u3064 B[i] = x \u3092\u6E80\u305F\u3059\n * \u5E83\u7FA9\u5358\u8ABF\u5897\u52A0\
    \u5217 B \u306E\u6570\u3068\u3059\u308B\n * res[x] = sum C[i] * g(A[i:N], x)\n\
    \ * \u3092\u8FD4\u3059\n */\nstd::vector<T> count_increase_sequences_with_upper_bounds(std::vector<int>\
    \ A, std::vector<T> C){\n    int N = A.size();\n    assert((int)C.size() == N);\n\
    \    assert(N);\n    for (int i = (int)(A.size()) - 1; i > 0; i--) A[i - 1] =\
    \ std::min(A[i - 1], A[i]);\n    if (A.back() == 0) return {};\n    if (N == 1){\n\
    \        std::vector<T> res(A[0]);\n        for (int i = 0; i < A[0]; i++) res[i]\
    \ = C[0];\n        return res;\n    }\n    int m = N / 2;\n    std::vector<int>\
    \ LA(m), RA(N - m);\n    std::vector<T> LC(m), RC(N - m);\n    for (int i = 0;\
    \ i < m; i++){\n        LA[i] = A[i];\n        LC[i] = C[i];\n    }\n    for (int\
    \ i = 0; i < N - m; i++){\n        RA[i] = A[i + m] - A[m - 1];\n        RC[i]\
    \ = C[i + m];\n    }\n    std::vector<T> res;\n    res.reserve(A.back());\n  \
    \  auto L = count_increase_sequences_with_upper_bounds(LA, LC);\n    if (!L.empty()){\n\
    \        auto [R, U] = count_square(L, RC);\n        for (int i = 0; i < (int)R.size();\
    \ i++) res.push_back(R[i]);\n        std::swap(U, RC);\n    }\n    auto R = count_increase_sequences_with_upper_bounds(RA,\
    \ RC);\n    for (auto x : R) res.push_back(x);\n    return res;\n}\ntemplate<class\
    \ T>\nstd::vector<T> NAIVE_count_increase_sequences_with_upper_lower_bounds(std::vector<int>\
    \ A, std::vector<int> B, std::vector<T> C = {}){\n    std::vector<T> tmp(B.back()\
    \ - A[0]);\n    if (C.empty()){\n        int b = B[0];\n        for (int i = 1;\
    \ i < (int)B.size(); i++) b = std::min(b, B[i]);\n        for (int i = 0; i <\
    \ b - A[0]; i++) tmp[i] = 1;\n    }\n    else for (int i = 0; i < (int)std::min(tmp.size(),\
    \ C.size()); i++) tmp[i] = C[i];\n    int N = A.size();\n    for (int i = 1; i\
    \ < N; i++){\n        for (int j = 1; j < (int)tmp.size(); j++){\n           \
    \ tmp[j] += tmp[j - 1];\n        }\n        for (int j = 0; j < (int)tmp.size();\
    \ j++){\n            if (j < A[i] - A[0] || B[i] - A[0] <= j) tmp[j] = 0;\n  \
    \      }\n    }\n    std::vector<T> res(B.back() - A.back());\n    for (int i\
    \ = 0; i < B.back() - A.back(); i++){\n        res[i] = tmp[A.back() - A[0] +\
    \ i];\n    }\n    return res;\n}\n\ntemplate<class T>\n/*\n * f(a, b) \u3092 X[0]\
    \ = a, X[N - 1] = b \u3067\u3042\u308B\u3088\u3046\u306A\u3001A, B \u306B\u631F\
    \u307E\u308C\u305F\u3082\u306E\u3068\u3059\u308B\n * \u9577\u3055 B[N - 1] - A[N\
    \ - 1] \u3092\u8FD4\u3059\n * res[b - A.back()] = sum C[a - A[0]] * f(a, b)\n\
    \ * A, B \u306F\u5E83\u7FA9\u5358\u8ABF\u5897\u52A0\u304C\u5B09\u3057\u3044\n\
    \ */\nstd::vector<T> count_increase_sequences_with_upper_lower_bounds(std::vector<int>\
    \ A, std::vector<int> B, std::vector<T> C = {}){\n    int N = A.size();\n    assert(A.size()\
    \ == B.size());\n    for (int i = 0; i < N - 1; i++){\n        A[i + 1] = std::max(A[i],\
    \ A[i + 1]);\n    }\n    for (int i = N - 1; i > 0; i--){\n        B[i - 1] =\
    \ std::min(B[i], B[i - 1]);\n    }\n    if (A.back() >= B.back()) return {};\n\
    \    // A[0] == 0 \u306B\u3059\u308B\n    std::vector<T> res(B.back() - A.back(),\
    \ 0);\n    {\n        int tmp = A[0];\n        for (int i = 0; i < N; i++){\n\
    \            A[i] -= tmp;\n            B[i] -= tmp;\n            if (A[i] >= B[i])\
    \ return res;\n        }\n    }\n    if (C.empty()){\n        C.resize(B[0] -\
    \ A[0], 1);\n    }\n    else assert((int)(C.size()) == B[0] - A[0]);\n    int\
    \ l = 0;\n    while (B[l] <= A.back()){\n        for (int i = (int)(C.size())\
    \ - 1; i > 0; i--) C[i] -= C[i - 1];\n        int nl = l;\n        while (A[nl]\
    \ < B[l]) nl++;\n        std::vector<int> tmp(B[l] - A[l]);\n        tmp[0] =\
    \ 1;\n        for (int i = l; i < nl; i++){\n            tmp[A[i] - A[l]]++;\n\
    \        }\n        for (int i = 1; i < B[l] - A[l]; i++) tmp[i] += tmp[i - 1];\n\
    \        auto X = count_increase_sequences_with_upper_bounds(tmp, C);\n      \
    \  std::vector<int> nB(nl - l + 1);\n        for (int i = l; i <= nl; i++){\n\
    \            nB[i - l] = B[i] - B[l];\n        }\n        auto Y = count_increase_sequences_with_upper_bounds(nB,\
    \ X);\n        C.resize(B[nl] - A[nl]);\n        for (int i = 0; i < B[nl] - A[nl];\
    \ i++){\n            C[i] = Y[i + A[nl] - B[l]];\n        }\n        l = nl;\n\
    \    }\n    // A \u3092\u63C3\u3048\u3066\u3057\u307E\u3048\n    {\n        int\
    \ a = A[l];\n        for (int i = l; i < N; i++){\n            A[i] -= a;\n  \
    \          B[i] -= a;\n        }\n    }\n    for (int i = (int)(C.size()) - 1;\
    \ i > 0; i--) C[i] -= C[i - 1];\n    std::vector<T> D(N - l, 0);\n    if (A.back()\
    \ != 0){\n        std::vector<T> L(A.back());\n        for (int i = 0; i < (int)L.size();\
    \ i++) L[i] = C[i];\n        std::vector<int> tmp(L.size());\n        tmp[0] =\
    \ 1;\n        for (int i = l; i < N; i++){\n            if (A[i] < (int)tmp.size())\
    \ tmp[A[i]]++;\n        }\n        for (int i = 1; i < (int)tmp.size(); i++){\n\
    \            tmp[i] += tmp[i - 1];\n        }\n        auto nD = count_increase_sequences_with_upper_bounds(tmp,\
    \ L);\n        for (int i = 0; i < (int)nD.size(); i++) D[i] = nD[i];\n    }\n\
    \    for (int i = A.back(); i < B[l]; i++) C[i - A.back()] = C[i];\n    C.resize(B[l]\
    \ - A.back());\n    auto [R, U] = count_square(C, D);\n    res = R;\n    std::vector<int>\
    \ nB(N - l);\n    for (int i = 0; i < N - l; i++) nB[i] = B[i + l] - B[l];\n \
    \   R = count_increase_sequences_with_upper_bounds(nB, U);\n    for (auto x :\
    \ R) res.push_back(x);\n    return res;\n}\n}"
  dependsOn:
  - math/Binomial.hpp
  - fps/FPS_cyclic_convolution.hpp
  isVerificationFile: false
  path: fps/count_increasing_sequences.hpp
  requiredBy: []
  timestamp: '2025-10-08 23:27:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/count_increasing_sequences.test.cpp
documentation_of: fps/count_increasing_sequences.hpp
layout: document
redirect_from:
- /library/fps/count_increasing_sequences.hpp
- /library/fps/count_increasing_sequences.hpp.html
title: fps/count_increasing_sequences.hpp
---
