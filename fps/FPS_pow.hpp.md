---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_differetial.hpp
    title: fps/FPS_differetial.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_exp.hpp
    title: fps/FPS_exp.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_integral.hpp
    title: fps/FPS_integral.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_log.hpp
    title: fps/FPS_log.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/pow.test.cpp
    title: test/fps/pow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_pow.hpp\"\n\n#include <vector>\n#include <atcoder/convolution>\n\
    \n#line 4 \"fps/FPS_cyclic_convolution.hpp\"\n\nnamespace po167{\n// |f| = |g|\
    \ = 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 3 \"fps/FPS_differetial.hpp\"\n\nnamespace\
    \ po167{\n// return f'\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T>\
    \ f){\n    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1;\
    \ i++){\n        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n   \
    \ return f;\n}\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate\
    \ <class T>\nstd::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty())\
    \ return f;\n    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] =\
    \ 1;\n    num_inv[1] = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size();\
    \ i++){\n        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate\
    \ <class T>\nstd::vector<T> FPS_inv(std::vector<T> f, int len = -1){\n    if (len\
    \ == -1) len = f.size();\n    assert(f[0] != 0);\n    std::vector<T> g = {1 /\
    \ f[0]};\n    int s = 1;\n    while(s < len){\n        // g = 2g_s - f(g_s)^2\
    \ (mod x ^ (2 * s))\n        // g = g - (fg - 1)g\n        // (fg - 1) = 0 (mod\
    \ x ^ (s))\n        std::vector<T> n_g(s * 2, 0);\n        std::vector<T> f_s(s\
    \ * 2, 0);\n        g.resize(s * 2);\n        for (int i = 0; i < s * 2; i++){\n\
    \            if (int(f.size()) > i) f_s[i] = f[i];\n            n_g[i] = g[i];\n\
    \        }\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        T iz = 1 / (T)(s\
    \ * 2);\n        for (int i = s; i < s * 2; i++){\n            f_s[i] *= iz;\n\
    \        }\n        for (int i = 0; i < s; i++){\n            f_s[i] = 0;\n  \
    \      }\n        atcoder::internal::butterfly(f_s);\n        for (int i = 0;\
    \ i < s * 2; i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        for (int i = s; i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n\
    \        }\n        std::swap(n_g, g);\n        s *= 2;\n    }\n    g.resize(len);\n\
    \    return g;\n}\n}\n#line 8 \"fps/FPS_exp.hpp\"\n\nnamespace po167{\ntemplate<class\
    \ T>\nstd::vector<T> FPS_exp(std::vector<T> f, int len = -1){\n    if (len ==\
    \ -1) len = f.size();\n    if (len == 0) return {};\n    if (len == 1) return\
    \ {T(1)};\n    assert(!f.empty() && f[0] == 0);\n    int s = 1;\n    // simple\n\
    \    std::vector<T> g = {T(1)};\n    while (s < len){\n        // g' / g\n   \
    \     // A * B\n        std::vector<T> A = g, B = g;\n        A = FPS_differential(A);\n\
    \        B = FPS_inv(B, 2 * s);\n        A.resize(2 * s);\n        A = FPS_cyclic_convolution(A,\
    \ B);\n        A.pop_back();\n        A = FPS_integral(A);\n        for (int i\
    \ = 0; i < s; i++) A[i] = 0;\n        for (int i = s; i < s * 2; i++) A[i] = (i\
    \ < (int)f.size() ? f[i] : 0) - A[i];\n        // g_hat = g (1 - g + f)\n    \
    \    // g += B = g * A\n        g.resize(2 * s);\n        B = FPS_cyclic_convolution(A,\
    \ g);\n        for (int i = s; i < s * 2; i++) g[i] = B[i];\n        s *= 2;\n\
    \    }\n    g.resize(len);\n    return g;\n}\n}\n#line 5 \"fps/FPS_log.hpp\"\n\
    \nnamespace po167{\ntemplate<class T>\nstd::vector<T> FPS_log(std::vector<T> f,\
    \ int len = -1){\n    if (len == -1) len = f.size();\n    if (len == 0) return\
    \ {};\n    if (len == 1) return {T(0)};\n    assert(!f.empty() && f[0] == 1);\n\
    \    std::vector<T> res = atcoder::convolution(FPS_differential(f), FPS_inv(f,\
    \ len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n}\n}\n#line\
    \ 8 \"fps/FPS_pow.hpp\"\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_pow(std::vector<T> f,long long M, int len = -1){\n    if (len == -1) len\
    \ = f.size();\n    std::vector<T> res(len, 0);\n    if (M == 0){\n        res[0]\
    \ = 1;\n        return res;\n    }\n    for (int i = 0; i < (int)f.size(); i++){\n\
    \        if (f[i] == 0) continue;\n        if (i > (len - 1) / M) break;\n   \
    \     std::vector<T> g((int)f.size() - i);\n        T v = (T)(1) / (T)(f[i]);\n\
    \        for (int j = i; j < (int)f.size(); j++){\n            g[j - i] = f[j]\
    \ * v;\n        }\n        long long zero = i * M;\n        if (i) len -= i *\
    \ M;\n        g = FPS_log(g, len);\n        for (T &x : g) x *= M;\n        g\
    \ = FPS_exp(g, len);\n        v = (T)(1) / v;\n        T c = 1;\n        while\
    \ (M){\n            if (M & 1) c = c * v;\n            v = v * v;\n          \
    \  M >>= 1;\n        }\n        for (int i = 0; i < len; i++) res[i + zero] =\
    \ g[i] * c;\n        return res;\n    }\n    return res;\n}\n}\n"
  code: "#pragma once\n\n#include <vector>\n#include <atcoder/convolution>\n\n#include\
    \ \"FPS_exp.hpp\"\n#include \"FPS_log.hpp\"\n\nnamespace po167{\ntemplate<class\
    \ T>\nstd::vector<T> FPS_pow(std::vector<T> f,long long M, int len = -1){\n  \
    \  if (len == -1) len = f.size();\n    std::vector<T> res(len, 0);\n    if (M\
    \ == 0){\n        res[0] = 1;\n        return res;\n    }\n    for (int i = 0;\
    \ i < (int)f.size(); i++){\n        if (f[i] == 0) continue;\n        if (i >\
    \ (len - 1) / M) break;\n        std::vector<T> g((int)f.size() - i);\n      \
    \  T v = (T)(1) / (T)(f[i]);\n        for (int j = i; j < (int)f.size(); j++){\n\
    \            g[j - i] = f[j] * v;\n        }\n        long long zero = i * M;\n\
    \        if (i) len -= i * M;\n        g = FPS_log(g, len);\n        for (T &x\
    \ : g) x *= M;\n        g = FPS_exp(g, len);\n        v = (T)(1) / v;\n      \
    \  T c = 1;\n        while (M){\n            if (M & 1) c = c * v;\n         \
    \   v = v * v;\n            M >>= 1;\n        }\n        for (int i = 0; i < len;\
    \ i++) res[i + zero] = g[i] * c;\n        return res;\n    }\n    return res;\n\
    }\n}"
  dependsOn:
  - fps/FPS_exp.hpp
  - fps/FPS_cyclic_convolution.hpp
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_log.hpp
  isVerificationFile: false
  path: fps/FPS_pow.hpp
  requiredBy: []
  timestamp: '2024-09-05 20:11:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/pow.test.cpp
documentation_of: fps/FPS_pow.hpp
layout: document
redirect_from:
- /library/fps/FPS_pow.hpp
- /library/fps/FPS_pow.hpp.html
title: fps/FPS_pow.hpp
---
