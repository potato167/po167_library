---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/consecutive_linear.test.cpp
    title: test/fps/consecutive_linear.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_consecutive_linear.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n#include <atcoder/convolution>\n\
    #line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate <class\
    \ T>\nstd::vector<T> FPS_inv(std::vector<T> f, int len = -1){\n    if (len ==\
    \ -1) len = f.size();\n    assert(f[0] != 0);\n    std::vector<T> g = {1 / f[0]};\n\
    \    int s = 1;\n    while(s < len){\n        // g = 2g_s - f(g_s)^2 (mod x ^\
    \ (2 * s))\n        // g = g - (fg - 1)g\n        // (fg - 1) = 0 (mod x ^ (s))\n\
    \        std::vector<T> n_g(s * 2, 0);\n        std::vector<T> f_s(s * 2, 0);\n\
    \        g.resize(s * 2);\n        for (int i = 0; i < s * 2; i++){\n        \
    \    if (int(f.size()) > i) f_s[i] = f[i];\n            n_g[i] = g[i];\n     \
    \   }\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        T iz = 1 / (T)(s\
    \ * 2);\n        for (int i = s; i < s * 2; i++){\n            f_s[i] *= iz;\n\
    \        }\n        for (int i = 0; i < s; i++){\n            f_s[i] = 0;\n  \
    \      }\n        atcoder::internal::butterfly(f_s);\n        for (int i = 0;\
    \ i < s * 2; i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        for (int i = s; i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n\
    \        }\n        std::swap(n_g, g);\n        s *= 2;\n    }\n    g.resize(len);\n\
    \    return g;\n}\n}\n#line 8 \"fps/FPS_consecutive_linear.hpp\"\n\nnamespace\
    \ po167 {\nnamespace internal {\n\n// Q(0) != 0, 0 < r; [x^i]P(x)/Q(x) = 0 (i\
    \ < 0).\n// return { [x^i]P(x)/Q(x) : l <= i < r }.\ntemplate<class T>\nstd::vector<T>\
    \ fps_div_consecutive(long long l, long long r,\n                            \
    \      std::vector<T> P, std::vector<T> Q) {\n    assert(0 < r);\n    if (l >=\
    \ r) return {};\n    assert(!Q.empty() && Q[0] != T(0));\n    std::vector<T> res(r\
    \ - l);\n    if (P.empty()) return res;\n    while (Q.size() > 1 && Q.back() ==\
    \ T(0)) Q.pop_back();\n    while (P.size() > 1 && P.back() == T(0)) P.pop_back();\n\
    \    int p = P.size(), q = Q.size();\n    long long L = std::max(0LL, l);\n  \
    \  if (p == 1 && P[0] == T(0)) return res;\n    if (q == 1) {\n        T inv =\
    \ T(1) / Q[0];\n        for (long long i = L; i < r && i < p; ++i) res[i - l]\
    \ = P[i] * inv;\n        return res;\n    }\n    if (r <= 4LL * q) {\n       \
    \ auto B = FPS_inv(std::move(Q), int(r));\n        if (p > 1) {\n            P.resize(std::min<long\
    \ long>(p, r));\n            B = atcoder::convolution(std::move(P), std::move(B));\n\
    \        }\n        T scale = p == 1 ? P[0] : T(1);\n        for (long long i\
    \ = L; i < r; ++i) res[i - l] = B[i] * scale;\n        return res;\n    }\n  \
    \  int h = p + q - 1, n = 1;\n    while (n < q - 1 || 2LL * n < r - L + h - 1)\
    \ n *= 2;\n    assert((T::mod() - 1) % (2 * n) == 0);\n    T top = q == n + 1\
    \ ? Q.back() * Q.back() * T(1 - 2 * (n & 1)) : T(0);\n    Q.resize(2 * n);\n \
    \   atcoder::internal::butterfly(Q);\n\n    // C(x^2) = Q_original(x) Q_original(-x).\n\
    \    std::vector<T> C(n);\n    for (int i = 0; i < n; ++i) C[i] = Q[2 * i] * Q[2\
    \ * i + 1];\n    atcoder::internal::butterfly_inv(C);\n    C.resize(q);\n    T\
    \ inv_n = T(1) / T(n);\n    for (auto &x : C) x *= inv_n;\n    if (q == n + 1)\
    \ {\n        C[0] -= top;\n        C[n] = top;\n    }\n    long long nl = std::max(0LL,\
    \ (L - h + 2) / 2), nr = r / 2 + r % 2;\n    auto D = fps_div_consecutive(nl,\
    \ nr, std::vector<T>{T(1)}, std::move(C));\n    D.resize(n);\n    atcoder::internal::butterfly(D);\n\
    \n    // P(x) Q_original(-x) D(x^2) mod (x^(2n) - 1).\n    if (p > 1) {\n    \
    \    P.resize(2 * n);\n        atcoder::internal::butterfly(P);\n        for (int\
    \ i = 0; i < 2 * n; ++i) Q[i] *= P[i ^ 1];\n    }\n    for (int i = 0; i < n;\
    \ ++i) {\n        std::swap(Q[2 * i], Q[2 * i + 1]);\n        Q[2 * i] *= D[i];\n\
    \        Q[2 * i + 1] *= D[i];\n    }\n    atcoder::internal::butterfly_inv(Q);\n\
    \    T scale = (p == 1 ? P[0] : T(1)) / T(2 * n);\n    for (long long i = L; i\
    \ < r; ++i) res[i - l] = Q[i - 2 * nl] * scale;\n    return res;\n}\n\n} // namespace\
    \ internal\n\n// A(0) != 0, 0 < r; B(x) = 1/A(x), B_i = 0 (i < 0).\n// return\
    \ { B_l, B_(l+1), ..., B_(r-1) }.\ntemplate<class T>\nstd::vector<T> FPS_Inv_Consecutive(long\
    \ long l, long long r, std::vector<T> A) {\n    return internal::fps_div_consecutive(l,\
    \ r, std::vector<T>{T(1)}, std::move(A));\n}\n\n// d = |a|, |c| = d+1, c[0] !=\
    \ 0, 0 < r.\n// sum_{j=0}^d c[j] a[i-j] = 0 (i >= d); a[i] = 0 (i < 0).\n// return\
    \ { a[l], a[l+1], ..., a[r-1] }.\ntemplate<class T>\nstd::vector<T> Consecutive_Linear(long\
    \ long l, long long r,\n                                 std::vector<T> a, std::vector<T>\
    \ c) {\n    assert(0 < r && a.size() + 1 == c.size() && c[0] != T(0));\n    if\
    \ (l >= r) return {};\n    int d = a.size();\n    if (r <= d) {\n        std::vector<T>\
    \ res(r - l);\n        for (long long i = std::max(0LL, l); i < r; ++i) res[i\
    \ - l] = a[i];\n        return res;\n    }\n    a = atcoder::convolution(a, c);\n\
    \    a.resize(d);\n    return internal::fps_div_consecutive(l, r, std::move(a),\
    \ std::move(c));\n}\n\n} // namespace po167\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n#include <atcoder/convolution>\n#include \"FPS_inv.hpp\"\n\n\
    namespace po167 {\nnamespace internal {\n\n// Q(0) != 0, 0 < r; [x^i]P(x)/Q(x)\
    \ = 0 (i < 0).\n// return { [x^i]P(x)/Q(x) : l <= i < r }.\ntemplate<class T>\n\
    std::vector<T> fps_div_consecutive(long long l, long long r,\n               \
    \                   std::vector<T> P, std::vector<T> Q) {\n    assert(0 < r);\n\
    \    if (l >= r) return {};\n    assert(!Q.empty() && Q[0] != T(0));\n    std::vector<T>\
    \ res(r - l);\n    if (P.empty()) return res;\n    while (Q.size() > 1 && Q.back()\
    \ == T(0)) Q.pop_back();\n    while (P.size() > 1 && P.back() == T(0)) P.pop_back();\n\
    \    int p = P.size(), q = Q.size();\n    long long L = std::max(0LL, l);\n  \
    \  if (p == 1 && P[0] == T(0)) return res;\n    if (q == 1) {\n        T inv =\
    \ T(1) / Q[0];\n        for (long long i = L; i < r && i < p; ++i) res[i - l]\
    \ = P[i] * inv;\n        return res;\n    }\n    if (r <= 4LL * q) {\n       \
    \ auto B = FPS_inv(std::move(Q), int(r));\n        if (p > 1) {\n            P.resize(std::min<long\
    \ long>(p, r));\n            B = atcoder::convolution(std::move(P), std::move(B));\n\
    \        }\n        T scale = p == 1 ? P[0] : T(1);\n        for (long long i\
    \ = L; i < r; ++i) res[i - l] = B[i] * scale;\n        return res;\n    }\n  \
    \  int h = p + q - 1, n = 1;\n    while (n < q - 1 || 2LL * n < r - L + h - 1)\
    \ n *= 2;\n    assert((T::mod() - 1) % (2 * n) == 0);\n    T top = q == n + 1\
    \ ? Q.back() * Q.back() * T(1 - 2 * (n & 1)) : T(0);\n    Q.resize(2 * n);\n \
    \   atcoder::internal::butterfly(Q);\n\n    // C(x^2) = Q_original(x) Q_original(-x).\n\
    \    std::vector<T> C(n);\n    for (int i = 0; i < n; ++i) C[i] = Q[2 * i] * Q[2\
    \ * i + 1];\n    atcoder::internal::butterfly_inv(C);\n    C.resize(q);\n    T\
    \ inv_n = T(1) / T(n);\n    for (auto &x : C) x *= inv_n;\n    if (q == n + 1)\
    \ {\n        C[0] -= top;\n        C[n] = top;\n    }\n    long long nl = std::max(0LL,\
    \ (L - h + 2) / 2), nr = r / 2 + r % 2;\n    auto D = fps_div_consecutive(nl,\
    \ nr, std::vector<T>{T(1)}, std::move(C));\n    D.resize(n);\n    atcoder::internal::butterfly(D);\n\
    \n    // P(x) Q_original(-x) D(x^2) mod (x^(2n) - 1).\n    if (p > 1) {\n    \
    \    P.resize(2 * n);\n        atcoder::internal::butterfly(P);\n        for (int\
    \ i = 0; i < 2 * n; ++i) Q[i] *= P[i ^ 1];\n    }\n    for (int i = 0; i < n;\
    \ ++i) {\n        std::swap(Q[2 * i], Q[2 * i + 1]);\n        Q[2 * i] *= D[i];\n\
    \        Q[2 * i + 1] *= D[i];\n    }\n    atcoder::internal::butterfly_inv(Q);\n\
    \    T scale = (p == 1 ? P[0] : T(1)) / T(2 * n);\n    for (long long i = L; i\
    \ < r; ++i) res[i - l] = Q[i - 2 * nl] * scale;\n    return res;\n}\n\n} // namespace\
    \ internal\n\n// A(0) != 0, 0 < r; B(x) = 1/A(x), B_i = 0 (i < 0).\n// return\
    \ { B_l, B_(l+1), ..., B_(r-1) }.\ntemplate<class T>\nstd::vector<T> FPS_Inv_Consecutive(long\
    \ long l, long long r, std::vector<T> A) {\n    return internal::fps_div_consecutive(l,\
    \ r, std::vector<T>{T(1)}, std::move(A));\n}\n\n// d = |a|, |c| = d+1, c[0] !=\
    \ 0, 0 < r.\n// sum_{j=0}^d c[j] a[i-j] = 0 (i >= d); a[i] = 0 (i < 0).\n// return\
    \ { a[l], a[l+1], ..., a[r-1] }.\ntemplate<class T>\nstd::vector<T> Consecutive_Linear(long\
    \ long l, long long r,\n                                 std::vector<T> a, std::vector<T>\
    \ c) {\n    assert(0 < r && a.size() + 1 == c.size() && c[0] != T(0));\n    if\
    \ (l >= r) return {};\n    int d = a.size();\n    if (r <= d) {\n        std::vector<T>\
    \ res(r - l);\n        for (long long i = std::max(0LL, l); i < r; ++i) res[i\
    \ - l] = a[i];\n        return res;\n    }\n    a = atcoder::convolution(a, c);\n\
    \    a.resize(d);\n    return internal::fps_div_consecutive(l, r, std::move(a),\
    \ std::move(c));\n}\n\n} // namespace po167"
  dependsOn:
  - fps/FPS_inv.hpp
  isVerificationFile: false
  path: fps/FPS_consecutive_linear.hpp
  requiredBy: []
  timestamp: '2026-10-22 02:25:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/consecutive_linear.test.cpp
documentation_of: fps/FPS_consecutive_linear.hpp
layout: document
redirect_from:
- /library/fps/FPS_consecutive_linear.hpp
- /library/fps/FPS_consecutive_linear.hpp.html
title: fps/FPS_consecutive_linear.hpp
---
