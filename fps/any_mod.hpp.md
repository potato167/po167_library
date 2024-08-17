---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/any_mod.test.cpp
    title: test/fps/any_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://kopricky.github.io/code/Computation_Advanced/garner.html
  bundledCode: "#line 2 \"fps/any_mod.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    #include <cassert>\n\nnamespace po167{\n//https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    template<typename T>\nT mod_add(const T a, const T b, const T mod){\n    return\
    \ (a + b) % mod;\n}\n \ntemplate<typename T>\nT mod_mul(const T a, const T b,\
    \ const T mod){\n    return a * b % mod;\n}\n \ntemplate<typename T>\nT mod_inv(T\
    \ a, T mod){\n    T u[] = {a, 1, 0}, v[] = {mod, 0, 1}, t;\n    while(*v){\n \
    \       t = *u / *v;\n        std::swap(u[0] -= t * v[0], v[0]);\n        std::swap(u[1]\
    \ -= t * v[1], v[1]);\n        std::swap(u[2] -= t * v[2], v[2]);\n    }\n   \
    \ u[1] %= mod;\n    return (u[1] < 0) ? (u[1] + mod) : u[1];\n}\n \ntemplate<typename\
    \ T>\nT garner(const std::vector<T>& a, std::vector<T> p, const T mod){\n    const\
    \ unsigned int sz = a.size();\n    std::vector<T> kp(sz + 1, 0), rmult(sz + 1,\
    \ 1);\n    p.push_back(mod);\n    for(unsigned int i = 0; i < sz; ++i){\n    \
    \    T x = mod_mul(a[i] - kp[i], mod_inv(rmult[i], p[i]), p[i]);\n        x =\
    \ (x < 0) ? (x + p[i]) : x;\n        for(unsigned int j = i + 1; j < sz + 1; ++j){\n\
    \            kp[j] = mod_add(kp[j], rmult[j] * x, p[j]);\n            rmult[j]\
    \ = mod_mul(rmult[j], p[i], p[j]);\n        }\n    }\n    return kp[sz];\n}\n\n\
    const long long _mod0=754974721;\nconst long long _mod1=167772161;\nconst long\
    \ long _mod2=469762049;\nstd::vector<long long> _MOD={_mod0,_mod1,_mod2};\nstd::vector<long\
    \ long> convolution_any_mod(std::vector<long long> a,std::vector<long long> b,long\
    \ long pmod){\n\tfor(auto &x:a) x = (x % pmod + pmod) % pmod;\n\tfor(auto &x:b)\
    \ x = (x % pmod + pmod) % pmod;\n\tstd::vector<std::vector<long long>> res(3);\n\
    \tres[0] = atcoder::convolution<_mod0>(a,b);\n\tres[1] = atcoder::convolution<_mod1>(a,b);\n\
    \tres[2] = atcoder::convolution<_mod2>(a,b);\n\tfor(int i=0;i<(int)res[0].size();i++){\n\
    \t\tstd::vector<long long> q(3);\n\t\tfor(int j=0;j<3;j++) q[j] = res[j][i];\n\
    \t\tres[0][i] = garner(q, _MOD, pmod);\n\t}\n\treturn res[0];\n}\ntemplate<typename\
    \ T>\nstd::vector<T> convolution_mint(std::vector<T> a, std::vector<T> b){\n \
    \   std::vector<long long> A, B;\n    A.reserve(a.size()), B.reserve(b.size());\n\
    \    for (auto x : a) A.push_back(x.val());\n    for (auto x : b) B.push_back(x.val());\n\
    \    std::vector<long long> C = convolution_any_mod(A, B, T::mod());\n    std::vector<T>\
    \ c;\n    c.reserve(C.size());\n    for (auto x : C) c.push_back(x);\n    return\
    \ c;\n}\n};\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n#include\
    \ <cassert>\n\nnamespace po167{\n//https://kopricky.github.io/code/Computation_Advanced/garner.html\n\
    template<typename T>\nT mod_add(const T a, const T b, const T mod){\n    return\
    \ (a + b) % mod;\n}\n \ntemplate<typename T>\nT mod_mul(const T a, const T b,\
    \ const T mod){\n    return a * b % mod;\n}\n \ntemplate<typename T>\nT mod_inv(T\
    \ a, T mod){\n    T u[] = {a, 1, 0}, v[] = {mod, 0, 1}, t;\n    while(*v){\n \
    \       t = *u / *v;\n        std::swap(u[0] -= t * v[0], v[0]);\n        std::swap(u[1]\
    \ -= t * v[1], v[1]);\n        std::swap(u[2] -= t * v[2], v[2]);\n    }\n   \
    \ u[1] %= mod;\n    return (u[1] < 0) ? (u[1] + mod) : u[1];\n}\n \ntemplate<typename\
    \ T>\nT garner(const std::vector<T>& a, std::vector<T> p, const T mod){\n    const\
    \ unsigned int sz = a.size();\n    std::vector<T> kp(sz + 1, 0), rmult(sz + 1,\
    \ 1);\n    p.push_back(mod);\n    for(unsigned int i = 0; i < sz; ++i){\n    \
    \    T x = mod_mul(a[i] - kp[i], mod_inv(rmult[i], p[i]), p[i]);\n        x =\
    \ (x < 0) ? (x + p[i]) : x;\n        for(unsigned int j = i + 1; j < sz + 1; ++j){\n\
    \            kp[j] = mod_add(kp[j], rmult[j] * x, p[j]);\n            rmult[j]\
    \ = mod_mul(rmult[j], p[i], p[j]);\n        }\n    }\n    return kp[sz];\n}\n\n\
    const long long _mod0=754974721;\nconst long long _mod1=167772161;\nconst long\
    \ long _mod2=469762049;\nstd::vector<long long> _MOD={_mod0,_mod1,_mod2};\nstd::vector<long\
    \ long> convolution_any_mod(std::vector<long long> a,std::vector<long long> b,long\
    \ long pmod){\n\tfor(auto &x:a) x = (x % pmod + pmod) % pmod;\n\tfor(auto &x:b)\
    \ x = (x % pmod + pmod) % pmod;\n\tstd::vector<std::vector<long long>> res(3);\n\
    \tres[0] = atcoder::convolution<_mod0>(a,b);\n\tres[1] = atcoder::convolution<_mod1>(a,b);\n\
    \tres[2] = atcoder::convolution<_mod2>(a,b);\n\tfor(int i=0;i<(int)res[0].size();i++){\n\
    \t\tstd::vector<long long> q(3);\n\t\tfor(int j=0;j<3;j++) q[j] = res[j][i];\n\
    \t\tres[0][i] = garner(q, _MOD, pmod);\n\t}\n\treturn res[0];\n}\ntemplate<typename\
    \ T>\nstd::vector<T> convolution_mint(std::vector<T> a, std::vector<T> b){\n \
    \   std::vector<long long> A, B;\n    A.reserve(a.size()), B.reserve(b.size());\n\
    \    for (auto x : a) A.push_back(x.val());\n    for (auto x : b) B.push_back(x.val());\n\
    \    std::vector<long long> C = convolution_any_mod(A, B, T::mod());\n    std::vector<T>\
    \ c;\n    c.reserve(C.size());\n    for (auto x : C) c.push_back(x);\n    return\
    \ c;\n}\n};"
  dependsOn: []
  isVerificationFile: false
  path: fps/any_mod.hpp
  requiredBy: []
  timestamp: '2024-08-17 09:03:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/any_mod.test.cpp
documentation_of: fps/any_mod.hpp
layout: document
redirect_from:
- /library/fps/any_mod.hpp
- /library/fps/any_mod.hpp.html
title: fps/any_mod.hpp
---
