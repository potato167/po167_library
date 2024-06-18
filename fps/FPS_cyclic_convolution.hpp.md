---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: fps/FPS_exp.hpp
    title: fps/FPS_exp.hpp
  - icon: ':warning:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  - icon: ':warning:'
    path: test/fps/exp.hpp
    title: test/fps/exp.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
  - test/fps/exp.hpp
  - fps/FPS_exp.hpp
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_cyclic_convolution.hpp
layout: document
redirect_from:
- /library/fps/FPS_cyclic_convolution.hpp
- /library/fps/FPS_cyclic_convolution.hpp.html
title: fps/FPS_cyclic_convolution.hpp
---
