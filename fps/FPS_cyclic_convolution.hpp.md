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
    path: fps/FPS_pow.hpp
    title: fps/FPS_pow.hpp
  - icon: ':heavy_check_mark:'
    path: fps/Multipoint_Evaluation_Geo.hpp
    title: fps/Multipoint_Evaluation_Geo.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp_inverse.test.cpp
    title: test/fps/comp_inverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/exp.test.cpp
    title: test/fps/exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/multpoint_evalution_geo.test.cpp
    title: test/fps/multpoint_evalution_geo.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/pow.test.cpp
    title: test/fps/pow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_cyclic_convolution.hpp\"\n#include <vector>\n#include\
    \ <atcoder/convolution>\n\nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class\
    \ T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T> f, std::vector<T> g){\n\
    \    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n\nnamespace\
    \ po167{\n// |f| = |g| = 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_cyclic_convolution.hpp
  requiredBy:
  - fps/FPS_inverse.hpp
  - fps/FPS_exp.hpp
  - fps/FPS_pow.hpp
  - fps/Multipoint_Evaluation_Geo.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/exp.test.cpp
  - test/fps/multpoint_evalution_geo.test.cpp
  - test/fps/pow.test.cpp
  - test/fps/comp_inverse.test.cpp
documentation_of: fps/FPS_cyclic_convolution.hpp
layout: document
redirect_from:
- /library/fps/FPS_cyclic_convolution.hpp
- /library/fps/FPS_cyclic_convolution.hpp.html
title: fps/FPS_cyclic_convolution.hpp
---
