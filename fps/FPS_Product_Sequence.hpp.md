---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_sum_of_power.hpp
    title: fps/FPS_sum_of_power.hpp
  - icon: ':heavy_check_mark:'
    path: fps/Polynomial_Interpolation.hpp
    title: fps/Polynomial_Interpolation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/polynomial_interpolation.test.cpp
    title: test/fps/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/product_sequence.test.cpp
    title: test/fps/product_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/sum_of_power.test.cpp
    title: test/fps/sum_of_power.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_Product_Sequence.hpp\"\n#include <vector>\n#include\
    \ <atcoder/convolution>\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_Product_Sequence(std::vector<std::vector<T>> f){\n    if (f.empty()) return\
    \ {1};\n    auto op = [&](auto self,int l, int r) -> std::vector<T> {\n      \
    \  if (l + 1 == r) return f[l];\n        int m = (l + r) / 2;\n        return\
    \ atcoder::convolution(self(self, l, m), self(self, m, r));\n    };\n    return\
    \ op(op, 0, f.size());\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n\nnamespace\
    \ po167{\ntemplate<class T>\nstd::vector<T> FPS_Product_Sequence(std::vector<std::vector<T>>\
    \ f){\n    if (f.empty()) return {1};\n    auto op = [&](auto self,int l, int\
    \ r) -> std::vector<T> {\n        if (l + 1 == r) return f[l];\n        int m\
    \ = (l + r) / 2;\n        return atcoder::convolution(self(self, l, m), self(self,\
    \ m, r));\n    };\n    return op(op, 0, f.size());\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_Product_Sequence.hpp
  requiredBy:
  - fps/FPS_sum_of_power.hpp
  - fps/Polynomial_Interpolation.hpp
  timestamp: '2024-06-19 18:48:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/product_sequence.test.cpp
  - test/fps/sum_of_power.test.cpp
  - test/fps/polynomial_interpolation.test.cpp
documentation_of: fps/FPS_Product_Sequence.hpp
layout: document
redirect_from:
- /library/fps/FPS_Product_Sequence.hpp
- /library/fps/FPS_Product_Sequence.hpp.html
title: fps/FPS_Product_Sequence.hpp
---
