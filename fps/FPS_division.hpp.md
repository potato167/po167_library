---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/Multipoint_Evaluation.hpp
    title: fps/Multipoint_Evaluation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/division.test.cpp
    title: test/fps/division.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/multpoint_evalution.test.cpp
    title: test/fps/multpoint_evalution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_division.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate <class\
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
    \    return g;\n}\n}\n#line 6 \"fps/FPS_division.hpp\"\nnamespace po167{\ntemplate<class\
    \ T>\n// f = g * res.first + res.second\n// |res.first| <= |f| - |g| + 1\n// |res.second|\
    \ <= |g| - 1\nstd::pair<std::vector<T>, std::vector<T>>\nFPS_division(std::vector<T>\
    \ f, std::vector<T> g){\n    while (!f.empty() && f.back() == 0) f.pop_back();\n\
    \    assert(!g.empty() && g.back() != 0);\n    if (f.size() < g.size()){\n   \
    \     return {{}, f};\n    }\n    // rev(f) / rev(g) = rev(q) (mod x ^ {|f| -\
    \ |g| + 1})\n    std::vector<T> r = f;\n    std::reverse(f.begin(), f.end());\n\
    \    std::reverse(g.begin(), g.end());\n    int z = (int)f.size() - (int)g.size()\
    \ + 1;\n    f.resize(z);\n    std::vector<T> q = atcoder::convolution(f, FPS_inv(g,\
    \ z));\n    q.resize(z);\n    std::reverse(g.begin(), g.end());\n    std::reverse(q.begin(),\
    \ q.end());\n    f = atcoder::convolution(q, g);\n    for (int i = 0; i < (int)f.size();\
    \ i++) r[i] -= f[i];\n    while (!q.empty() && q.back() == 0) q.pop_back();\n\
    \    while (!r.empty() && r.back() == 0) r.pop_back();\n    return {q, r};\n}\n\
    }\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n\n#include\
    \ \"FPS_inv.hpp\"\nnamespace po167{\ntemplate<class T>\n// f = g * res.first +\
    \ res.second\n// |res.first| <= |f| - |g| + 1\n// |res.second| <= |g| - 1\nstd::pair<std::vector<T>,\
    \ std::vector<T>>\nFPS_division(std::vector<T> f, std::vector<T> g){\n    while\
    \ (!f.empty() && f.back() == 0) f.pop_back();\n    assert(!g.empty() && g.back()\
    \ != 0);\n    if (f.size() < g.size()){\n        return {{}, f};\n    }\n    //\
    \ rev(f) / rev(g) = rev(q) (mod x ^ {|f| - |g| + 1})\n    std::vector<T> r = f;\n\
    \    std::reverse(f.begin(), f.end());\n    std::reverse(g.begin(), g.end());\n\
    \    int z = (int)f.size() - (int)g.size() + 1;\n    f.resize(z);\n    std::vector<T>\
    \ q = atcoder::convolution(f, FPS_inv(g, z));\n    q.resize(z);\n    std::reverse(g.begin(),\
    \ g.end());\n    std::reverse(q.begin(), q.end());\n    f = atcoder::convolution(q,\
    \ g);\n    for (int i = 0; i < (int)f.size(); i++) r[i] -= f[i];\n    while (!q.empty()\
    \ && q.back() == 0) q.pop_back();\n    while (!r.empty() && r.back() == 0) r.pop_back();\n\
    \    return {q, r};\n}\n}"
  dependsOn:
  - fps/FPS_inv.hpp
  isVerificationFile: false
  path: fps/FPS_division.hpp
  requiredBy:
  - fps/Multipoint_Evaluation.hpp
  timestamp: '2024-11-23 03:09:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/multpoint_evalution.test.cpp
  - test/fps/division.test.cpp
documentation_of: fps/FPS_division.hpp
layout: document
redirect_from:
- /library/fps/FPS_division.hpp
- /library/fps/FPS_division.hpp.html
title: fps/FPS_division.hpp
---
