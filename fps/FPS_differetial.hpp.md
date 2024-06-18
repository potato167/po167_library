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
    path: fps/FPS_log.hpp
    title: fps/FPS_log.hpp
  - icon: ':warning:'
    path: test/fps/exp.hpp
    title: test/fps/exp.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_differetial.hpp\"\n#include <vector>\n\nnamespace\
    \ po167{\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T> f){\n\
    \    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1; i++){\n\
    \        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n    return f;\n\
    }\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\ntemplate <class T>\n\
    std::vector<T> FPS_differential(std::vector<T> f){\n    if (f.empty()) return\
    \ f;\n    for (int i = 0; i < (int)f.size() - 1; i++){\n        f[i] = f[i + 1]\
    \ * (T)(i + 1);\n    }\n    f.pop_back();\n    return f;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_differetial.hpp
  requiredBy:
  - test/fps/exp.hpp
  - fps/FPS_exp.hpp
  - fps/FPS_log.hpp
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_differetial.hpp
layout: document
redirect_from:
- /library/fps/FPS_differetial.hpp
- /library/fps/FPS_differetial.hpp.html
title: fps/FPS_differetial.hpp
---
