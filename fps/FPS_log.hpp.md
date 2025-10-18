---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_differetial.hpp
    title: fps/FPS_differetial.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_integral.hpp
    title: fps/FPS_integral.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_pow.hpp
    title: fps/FPS_pow.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_sum_of_power.hpp
    title: fps/FPS_sum_of_power.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp_inverse.test.cpp
    title: test/fps/comp_inverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/pow.test.cpp
    title: test/fps/pow.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/sum_of_power.test.cpp
    title: test/fps/sum_of_power.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_log.hpp\"\n#include <vector>\n#line 3 \"fps/FPS_differetial.hpp\"\
    \n\nnamespace po167{\n// return f'\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T>\
    \ f){\n    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1;\
    \ i++){\n        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n   \
    \ return f;\n}\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate\
    \ <class T>\nstd::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty())\
    \ return f;\n    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] =\
    \ 1;\n    num_inv[1] = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size();\
    \ i++){\n        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n#line 3 \"fps/FPS_inv.hpp\"\n#include <atcoder/convolution>\n\nnamespace\
    \ po167{\n// return 1 / f\ntemplate <class T>\nstd::vector<T> FPS_inv(std::vector<T>\
    \ f, int len = -1){\n    if (len == -1) len = f.size();\n    assert(f[0] != 0);\n\
    \    std::vector<T> g = {1 / f[0]};\n    int s = 1;\n    while(s < len){\n   \
    \     // g = 2g_s - f(g_s)^2 (mod x ^ (2 * s))\n        // g = g - (fg - 1)g\n\
    \        // (fg - 1) = 0 (mod x ^ (s))\n        std::vector<T> n_g(s * 2, 0);\n\
    \        std::vector<T> f_s(s * 2, 0);\n        g.resize(s * 2);\n        for\
    \ (int i = 0; i < s * 2; i++){\n            if (int(f.size()) > i) f_s[i] = f[i];\n\
    \            n_g[i] = g[i];\n        }\n        atcoder::internal::butterfly(g);\n\
    \        atcoder::internal::butterfly(f_s);\n        for (int i = 0; i < s * 2;\
    \ i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        T iz = 1 / (T)(s * 2);\n        for (int i = s; i < s * 2; i++){\n  \
    \          f_s[i] *= iz;\n        }\n        for (int i = 0; i < s; i++){\n  \
    \          f_s[i] = 0;\n        }\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        for (int i = s;\
    \ i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n        }\n        std::swap(n_g,\
    \ g);\n        s *= 2;\n    }\n    g.resize(len);\n    return g;\n}\n}\n#line\
    \ 6 \"fps/FPS_log.hpp\"\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_log(std::vector<T> f, int len = -1){\n    if (len == -1) len = f.size();\n\
    \    if (len == 0) return {};\n    if (len == 1) return {T(0)};\n    assert(!f.empty()\
    \ && f[0] == 1);\n    std::vector<T> res = atcoder::convolution(FPS_differential(f),\
    \ FPS_inv(f, len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n\
    }\n}\n"
  code: "#pragma once\n#include <vector>\n#include \"../fps/FPS_differetial.hpp\"\n\
    #include \"../fps/FPS_integral.hpp\"\n#include \"../fps/FPS_inv.hpp\"\n\nnamespace\
    \ po167{\ntemplate<class T>\nstd::vector<T> FPS_log(std::vector<T> f, int len\
    \ = -1){\n    if (len == -1) len = f.size();\n    if (len == 0) return {};\n \
    \   if (len == 1) return {T(0)};\n    assert(!f.empty() && f[0] == 1);\n    std::vector<T>\
    \ res = atcoder::convolution(FPS_differential(f), FPS_inv(f, len));\n    res.resize(len\
    \ - 1);\n    return FPS_integral(res);\n}\n}"
  dependsOn:
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  - fps/FPS_inv.hpp
  isVerificationFile: false
  path: fps/FPS_log.hpp
  requiredBy:
  - fps/FPS_sum_of_power.hpp
  - fps/FPS_pow.hpp
  - fps/FPS_inverse.hpp
  timestamp: '2024-11-08 23:20:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/comp_inverse.test.cpp
  - test/fps/sum_of_power.test.cpp
  - test/fps/pow.test.cpp
documentation_of: fps/FPS_log.hpp
layout: document
redirect_from:
- /library/fps/FPS_log.hpp
- /library/fps/FPS_log.hpp.html
title: fps/FPS_log.hpp
---
