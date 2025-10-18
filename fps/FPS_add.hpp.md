---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/Polynomial_Interpolation.hpp
    title: fps/Polynomial_Interpolation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/polynomial_interpolation.test.cpp
    title: test/fps/polynomial_interpolation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_add.hpp\"\n#include <vector>\n\nnamespace po167{\n\
    template <class T>\n// a(x) += b(x) * c * x^d\nvoid FPS_add(std::vector<T> &a,\
    \ std::vector<T> b, T c = 1, int d = 0){\n    for (int i = 0; i < (int)(b.size());\
    \ i++){\n        while ((int)a.size() <= i + d) a.push_back((T)0);\n        a[i\
    \ + d] += b[i] * c;\n    }\n}\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\ntemplate <class T>\n\
    // a(x) += b(x) * c * x^d\nvoid FPS_add(std::vector<T> &a, std::vector<T> b, T\
    \ c = 1, int d = 0){\n    for (int i = 0; i < (int)(b.size()); i++){\n       \
    \ while ((int)a.size() <= i + d) a.push_back((T)0);\n        a[i + d] += b[i]\
    \ * c;\n    }\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_add.hpp
  requiredBy:
  - fps/Polynomial_Interpolation.hpp
  timestamp: '2025-10-18 20:47:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/polynomial_interpolation.test.cpp
documentation_of: fps/FPS_add.hpp
layout: document
redirect_from:
- /library/fps/FPS_add.hpp
- /library/fps/FPS_add.hpp.html
title: fps/FPS_add.hpp
---
