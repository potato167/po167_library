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
    template <class T>\nstd::vector<T> FPS_add(std::vector<T> f, std::vector<T> g){\n\
    \    int len = max(f.size(), g.size());\n    f.resize(len, 0);\n    g.resize(len,\
    \ 0);\n    for (int i = 0; i < len; i++) f[i] += g[i];\n    return f;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\ntemplate <class T>\n\
    std::vector<T> FPS_add(std::vector<T> f, std::vector<T> g){\n    int len = max(f.size(),\
    \ g.size());\n    f.resize(len, 0);\n    g.resize(len, 0);\n    for (int i = 0;\
    \ i < len; i++) f[i] += g[i];\n    return f;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FSP_add.hpp
  requiredBy: []
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FSP_add.hpp
layout: document
redirect_from:
- /library/fps/FSP_add.hpp
- /library/fps/FSP_add.hpp.html
title: fps/FSP_add.hpp
---
