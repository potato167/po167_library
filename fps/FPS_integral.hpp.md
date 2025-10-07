---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_exp.hpp
    title: fps/FPS_exp.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_log.hpp
    title: fps/FPS_log.hpp
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
    path: test/fps/exp.test.cpp
    title: test/fps/exp.test.cpp
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
  bundledCode: "#line 2 \"fps/FPS_integral.hpp\"\n#include <vector>\n\nnamespace po167{\n\
    template <class T>\nstd::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty())\
    \ return f;\n    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] =\
    \ 1;\n    num_inv[1] = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size();\
    \ i++){\n        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\ntemplate <class T>\n\
    std::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty()) return f;\n\
    \    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] = 1;\n    num_inv[1]\
    \ = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size(); i++){\n\
    \        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_integral.hpp
  requiredBy:
  - fps/FPS_exp.hpp
  - fps/FPS_log.hpp
  - fps/FPS_inverse.hpp
  - fps/FPS_pow.hpp
  - fps/FPS_sum_of_power.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/sum_of_power.test.cpp
  - test/fps/pow.test.cpp
  - test/fps/comp_inverse.test.cpp
  - test/fps/exp.test.cpp
documentation_of: fps/FPS_integral.hpp
layout: document
redirect_from:
- /library/fps/FPS_integral.hpp
- /library/fps/FPS_integral.hpp.html
title: fps/FPS_integral.hpp
---
