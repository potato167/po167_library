---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  - icon: ':x:'
    path: fps/FPS_differetial.hpp
    title: fps/FPS_differetial.hpp
  - icon: ':x:'
    path: fps/FPS_integral.hpp
    title: fps/FPS_integral.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/fps/exp.test.cpp
    title: test/fps/exp.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_exp.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    #line 4 \"fps/FPS_cyclic_convolution.hpp\"\n\nnamespace po167{\n// |f| = |g| =\
    \ 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 3 \"fps/FPS_differetial.hpp\"\n\nnamespace\
    \ po167{\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T> f){\n\
    \    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1; i++){\n\
    \        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n    return f;\n\
    }\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate <class T>\n\
    std::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty()) return f;\n\
    \    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] = 1;\n    num_inv[1]\
    \ = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size(); i++){\n\
    \        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n#line 7 \"fps/FPS_exp.hpp\"\n\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_exp(std::vector<T> f, int len = -1){\n    if (len == -1) len = f.size();\n\
    \    if (len == 0) return {};\n    if (len == 1) return {T(1)};\n    assert(!f.empty()\
    \ && f[0] == 0);\n    int s = 1;\n    // simple\n    std::vector<T> g = {T(1)};\n\
    \    while (s < len){\n        // g' / g\n        // A * B\n        std::vector<T>\
    \ A = g, B = g;\n        A = FPS_differential(A);\n        B = FPS_inv(B, 2 *\
    \ s);\n        A.resize(2 * s);\n        A = FPS_cyclic_convolution(A, B);\n \
    \       A.pop_back();\n        A = FPS_integral(A);\n        for (int i = 0; i\
    \ < s; i++) A[i] = 0;\n        for (int i = s; i < s * 2; i++) A[i] = (i < (int)f.size()\
    \ ? f[i] : 0) - A[i];\n        // g_hat = g (1 - g + f)\n        // g += B = g\
    \ * A\n        g.resize(2 * s);\n        B = FPS_cyclic_convolution(A, g);\n \
    \       for (int i = s; i < s * 2; i++) g[i] = B[i];\n        s *= 2;\n    }\n\
    \    g.resize(len);\n    return g;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n#include\
    \ \"../fps/FPS_cyclic_convolution.hpp\"\n#include \"../fps/FPS_differetial.hpp\"\
    \n#include \"../fps/FPS_integral.hpp\"\n\n\nnamespace po167{\ntemplate<class T>\n\
    std::vector<T> FPS_exp(std::vector<T> f, int len = -1){\n    if (len == -1) len\
    \ = f.size();\n    if (len == 0) return {};\n    if (len == 1) return {T(1)};\n\
    \    assert(!f.empty() && f[0] == 0);\n    int s = 1;\n    // simple\n    std::vector<T>\
    \ g = {T(1)};\n    while (s < len){\n        // g' / g\n        // A * B\n   \
    \     std::vector<T> A = g, B = g;\n        A = FPS_differential(A);\n       \
    \ B = FPS_inv(B, 2 * s);\n        A.resize(2 * s);\n        A = FPS_cyclic_convolution(A,\
    \ B);\n        A.pop_back();\n        A = FPS_integral(A);\n        for (int i\
    \ = 0; i < s; i++) A[i] = 0;\n        for (int i = s; i < s * 2; i++) A[i] = (i\
    \ < (int)f.size() ? f[i] : 0) - A[i];\n        // g_hat = g (1 - g + f)\n    \
    \    // g += B = g * A\n        g.resize(2 * s);\n        B = FPS_cyclic_convolution(A,\
    \ g);\n        for (int i = s; i < s * 2; i++) g[i] = B[i];\n        s *= 2;\n\
    \    }\n    g.resize(len);\n    return g;\n}\n}"
  dependsOn:
  - fps/FPS_cyclic_convolution.hpp
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  isVerificationFile: false
  path: fps/FPS_exp.hpp
  requiredBy:
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/fps/exp.test.cpp
documentation_of: fps/FPS_exp.hpp
layout: document
redirect_from:
- /library/fps/FPS_exp.hpp
- /library/fps/FPS_exp.hpp.html
title: fps/FPS_exp.hpp
---
