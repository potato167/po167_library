---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: fps/FPS_Boston_Mori.hpp
    title: fps/FPS_Boston_Mori.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/fps/linear_kth.test.cpp
    title: test/fps/linear_kth.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_extend.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \nnamespace po167{\n// in  : DFT(v) (len(v) = z)\n// out : DFT(v) (len(v) = 2\
    \ * z)\ntemplate<class T>\nvoid FPS_extend(std::vector<T> &v){\n    int z = v.size();\n\
    \    T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n    auto cp = v;\n    atcoder::internal::butterfly_inv(cp);\n \
    \   T tmp = (T)(1) / (T)(z);\n    for (int i = 0; i < z; i++){\n        cp[i]\
    \ *= tmp;\n        tmp *= e;\n    }\n    atcoder::internal::butterfly(cp);\n \
    \   for (int i = 0; i < z; i++) v.push_back(cp[i]);\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n\nnamespace\
    \ po167{\n// in  : DFT(v) (len(v) = z)\n// out : DFT(v) (len(v) = 2 * z)\ntemplate<class\
    \ T>\nvoid FPS_extend(std::vector<T> &v){\n    int z = v.size();\n    T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n    auto cp = v;\n    atcoder::internal::butterfly_inv(cp);\n \
    \   T tmp = (T)(1) / (T)(z);\n    for (int i = 0; i < z; i++){\n        cp[i]\
    \ *= tmp;\n        tmp *= e;\n    }\n    atcoder::internal::butterfly(cp);\n \
    \   for (int i = 0; i < z; i++) v.push_back(cp[i]);\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_extend.hpp
  requiredBy:
  - fps/FPS_Boston_Mori.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/fps/linear_kth.test.cpp
documentation_of: fps/FPS_extend.hpp
layout: document
redirect_from:
- /library/fps/FPS_extend.hpp
- /library/fps/FPS_extend.hpp.html
title: fps/FPS_extend.hpp
---
