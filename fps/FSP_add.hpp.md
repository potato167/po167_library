---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FSP_add.hpp\"\n#include <vector>\n\nnamespace po167{\n\
    template <class T>\n// a(x) += b(x) * c * x^d\nvoid fps_add(std::vector<T> &a,\
    \ std::vector<T> b, T c = 1, int d = 0){\n    for (int i = 0, i < (int)(b.size()),\
    \ i++){\n        while ((int)a.size() <= i + d) a.push_back((mint)0);\n      \
    \  a[i + d] += b[i] * c;\n    }\n}\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\ntemplate <class T>\n\
    // a(x) += b(x) * c * x^d\nvoid fps_add(std::vector<T> &a, std::vector<T> b, T\
    \ c = 1, int d = 0){\n    for (int i = 0, i < (int)(b.size()), i++){\n       \
    \ while ((int)a.size() <= i + d) a.push_back((mint)0);\n        a[i + d] += b[i]\
    \ * c;\n    }\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FSP_add.hpp
  requiredBy: []
  timestamp: '2025-03-29 02:27:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FSP_add.hpp
layout: document
redirect_from:
- /library/fps/FSP_add.hpp
- /library/fps/FSP_add.hpp.html
title: fps/FSP_add.hpp
---
