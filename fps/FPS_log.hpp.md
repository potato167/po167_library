---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: fps/FPS_differetial.hpp
    title: fps/FPS_differetial.hpp
  - icon: ':x:'
    path: fps/FPS_integral.hpp
    title: fps/FPS_integral.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_log.hpp\"\n#include <vector>\n#line 3 \"fps/FPS_differetial.hpp\"\
    \n\nnamespace po167{\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T>\
    \ f){\n    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1;\
    \ i++){\n        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n   \
    \ return f;\n}\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate\
    \ <class T>\nstd::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty())\
    \ return f;\n    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] =\
    \ 1;\n    num_inv[1] = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size();\
    \ i++){\n        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n#line 5 \"fps/FPS_log.hpp\"\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_log(std::vector<T> f, int len = -1){\n    if (len == -1) len = f.size();\n\
    \    if (len == 0) return {};\n    if (len == 1) return {T(0)};\n    assert(!f.empty()\
    \ && f[0] == 1);\n    std::vector<T> res = atcoder::convolution(FPS_differential(f),\
    \ FPS_inv(f, len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n\
    }\n}\n"
  code: "#pragma once\n#include <vector>\n#include \"../fps/FPS_differetial.hpp\"\n\
    #include \"../fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate<class T>\n\
    std::vector<T> FPS_log(std::vector<T> f, int len = -1){\n    if (len == -1) len\
    \ = f.size();\n    if (len == 0) return {};\n    if (len == 1) return {T(0)};\n\
    \    assert(!f.empty() && f[0] == 1);\n    std::vector<T> res = atcoder::convolution(FPS_differential(f),\
    \ FPS_inv(f, len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n\
    }\n}"
  dependsOn:
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  isVerificationFile: false
  path: fps/FPS_log.hpp
  requiredBy:
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_log.hpp
layout: document
redirect_from:
- /library/fps/FPS_log.hpp
- /library/fps/FPS_log.hpp.html
title: fps/FPS_log.hpp
---
