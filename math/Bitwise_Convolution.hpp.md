---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/and_convolution.test.cpp
    title: test/math/and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/or_convolution.test.cpp
    title: test/math/or_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/xor_convolution.test.cpp
    title: test/math/xor_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://kazuma8128.hatenablog.com/entry/2018/05/31/144519
  bundledCode: "#line 2 \"math/Bitwise_Convolution.hpp\"\n#include <vector>\n#include\
    \ <cassert>\nnamespace po167{\n//https://kazuma8128.hatenablog.com/entry/2018/05/31/144519\n\
    template<class T>\nvoid and_fwt(std::vector<T> &f){\n    int n = f.size();\n \
    \   for (int i = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n \
    \           if ((j & i) == 0){\n                f[j] = f[j] + f[j | i];\n    \
    \        }\n        }\n    }\n}\ntemplate<class T>\nvoid and_ifwt(std::vector<T>\
    \ &f){\n    int n = f.size();\n    for (int i = 1; i < n; i <<= 1){\n        for\
    \ (int j = 0; j < n; j++){\n            if ((j & i) == 0){\n                f[j]\
    \ = f[j] - f[j | i];\n            }\n        }\n    }\n}\ntemplate<class T>\n\
    std::vector<T> and_convolution(std::vector<T> p, std::vector<T> q){\n    int n\
    \ = p.size();\n    assert(n == (int)q.size());\n    and_fwt(p), and_fwt(q);\n\
    \    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];\n    and_ifwt(p);\n    return\
    \ p;\n}\n\ntemplate<class T>\nvoid or_fwt(std::vector<T> &f){\n    int n = f.size();\n\
    \    for (int i = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n\
    \            if (j & i){\n                f[j] = f[j] + f[j ^ i];\n          \
    \  }\n        }\n    }\n}\ntemplate<class T>\nvoid or_ifwt(std::vector<T> &f){\n\
    \    int n = f.size();\n    for (int i = 1; i < n; i <<= 1){\n        for (int\
    \ j = 0; j < n; j++){\n            if (j & i){\n                f[j] = f[j] -\
    \ f[j ^ i];\n            }\n        }\n    }\n}\n\ntemplate<class T>\nstd::vector<T>\
    \ or_convolution(std::vector<T> p, std::vector<T> q){\n    int n = p.size();\n\
    \    assert(n == (int)q.size());\n    or_fwt(p), or_fwt(q);\n    for (int i =\
    \ 0; i < n; i++) p[i] = p[i] * q[i];\n    or_ifwt(p);\n    return p;\n}\n\ntemplate<class\
    \ T>\nvoid xor_fwt(std::vector<T> &f){\n    int n = f.size();\n    for (int i\
    \ = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n            if\
    \ (j & i){\n                T x = f[j ^ i], y = f[j];\n                f[j ^ i]\
    \ = x + y;\n                f[j]     = x - y;\n            }\n        }\n    }\n\
    }\n\ntemplate<class T>\nstd::vector<T> xor_convolution(std::vector<T> p, std::vector<T>\
    \ q){\n    int n = p.size();\n    assert(n == (int)q.size());\n    xor_fwt(p),\
    \ xor_fwt(q);\n    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];\n    xor_fwt(p);\n\
    \    T inv = (T)(1) / (T)(n);\n    for (int i = 0; i < n; i++) p[i] = p[i] * inv;\n\
    \    return p;\n}\n\n};\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace po167{\n//https://kazuma8128.hatenablog.com/entry/2018/05/31/144519\n\
    template<class T>\nvoid and_fwt(std::vector<T> &f){\n    int n = f.size();\n \
    \   for (int i = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n \
    \           if ((j & i) == 0){\n                f[j] = f[j] + f[j | i];\n    \
    \        }\n        }\n    }\n}\ntemplate<class T>\nvoid and_ifwt(std::vector<T>\
    \ &f){\n    int n = f.size();\n    for (int i = 1; i < n; i <<= 1){\n        for\
    \ (int j = 0; j < n; j++){\n            if ((j & i) == 0){\n                f[j]\
    \ = f[j] - f[j | i];\n            }\n        }\n    }\n}\ntemplate<class T>\n\
    std::vector<T> and_convolution(std::vector<T> p, std::vector<T> q){\n    int n\
    \ = p.size();\n    assert(n == (int)q.size());\n    and_fwt(p), and_fwt(q);\n\
    \    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];\n    and_ifwt(p);\n    return\
    \ p;\n}\n\ntemplate<class T>\nvoid or_fwt(std::vector<T> &f){\n    int n = f.size();\n\
    \    for (int i = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n\
    \            if (j & i){\n                f[j] = f[j] + f[j ^ i];\n          \
    \  }\n        }\n    }\n}\ntemplate<class T>\nvoid or_ifwt(std::vector<T> &f){\n\
    \    int n = f.size();\n    for (int i = 1; i < n; i <<= 1){\n        for (int\
    \ j = 0; j < n; j++){\n            if (j & i){\n                f[j] = f[j] -\
    \ f[j ^ i];\n            }\n        }\n    }\n}\n\ntemplate<class T>\nstd::vector<T>\
    \ or_convolution(std::vector<T> p, std::vector<T> q){\n    int n = p.size();\n\
    \    assert(n == (int)q.size());\n    or_fwt(p), or_fwt(q);\n    for (int i =\
    \ 0; i < n; i++) p[i] = p[i] * q[i];\n    or_ifwt(p);\n    return p;\n}\n\ntemplate<class\
    \ T>\nvoid xor_fwt(std::vector<T> &f){\n    int n = f.size();\n    for (int i\
    \ = 1; i < n; i <<= 1){\n        for (int j = 0; j < n; j++){\n            if\
    \ (j & i){\n                T x = f[j ^ i], y = f[j];\n                f[j ^ i]\
    \ = x + y;\n                f[j]     = x - y;\n            }\n        }\n    }\n\
    }\n\ntemplate<class T>\nstd::vector<T> xor_convolution(std::vector<T> p, std::vector<T>\
    \ q){\n    int n = p.size();\n    assert(n == (int)q.size());\n    xor_fwt(p),\
    \ xor_fwt(q);\n    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];\n    xor_fwt(p);\n\
    \    T inv = (T)(1) / (T)(n);\n    for (int i = 0; i < n; i++) p[i] = p[i] * inv;\n\
    \    return p;\n}\n\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/Bitwise_Convolution.hpp
  requiredBy: []
  timestamp: '2024-11-23 15:36:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/xor_convolution.test.cpp
  - test/math/and_convolution.test.cpp
  - test/math/or_convolution.test.cpp
documentation_of: math/Bitwise_Convolution.hpp
layout: document
redirect_from:
- /library/math/Bitwise_Convolution.hpp
- /library/math/Bitwise_Convolution.hpp.html
title: math/Bitwise_Convolution.hpp
---
