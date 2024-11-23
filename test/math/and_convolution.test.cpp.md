---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/Bitwise_Convolution.hpp
    title: math/Bitwise_Convolution.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/math/and_convolution.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n#line 2 \"math/Bitwise_Convolution.hpp\"\
    \n#include <vector>\n#include <cassert>\nnamespace po167{\n//https://kazuma8128.hatenablog.com/entry/2018/05/31/144519\n\
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
    \    return p;\n}\n\n};\n#line 3 \"test/math/and_convolution.test.cpp\"\n#include\
    \ <iostream>\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<mint> A(1 << N), B(1 << N);\n\
    \    int v;\n    for (auto &a : A) std::cin >> v, a = v;\n    for (auto &b : B)\
    \ std::cin >> v, b = v;\n    auto ans = po167::and_convolution(A, B);\n    for\
    \ (auto &c : ans) std::cout << c.val() << \" \";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n#include \"../../math/Bitwise_Convolution.hpp\"\n#include <iostream>\n#include\
    \ <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\nint main(){\n  \
    \  std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int N;\n\
    \    std::cin >> N;\n    std::vector<mint> A(1 << N), B(1 << N);\n    int v;\n\
    \    for (auto &a : A) std::cin >> v, a = v;\n    for (auto &b : B) std::cin >>\
    \ v, b = v;\n    auto ans = po167::and_convolution(A, B);\n    for (auto &c :\
    \ ans) std::cout << c.val() << \" \";\n}"
  dependsOn:
  - math/Bitwise_Convolution.hpp
  isVerificationFile: true
  path: test/math/and_convolution.test.cpp
  requiredBy: []
  timestamp: '2024-11-23 15:36:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/and_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/math/and_convolution.test.cpp
- /verify/test/math/and_convolution.test.cpp.html
title: test/math/and_convolution.test.cpp
---
