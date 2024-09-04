---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/multpoint_evalution_geo.test.cpp
    title: test/fps/multpoint_evalution_geo.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_cyclic_convolution.hpp\"\n#include <vector>\n#include\
    \ <atcoder/convolution>\n\nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class\
    \ T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T> f, std::vector<T> g){\n\
    \    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 2 \"fps/Multipoint_Evaluation_Geo.hpp\"\
    \nnamespace po167{\ntemplate <class T>\n// return {f(ar^0), f(ar^1), f(ar^2),\
    \ ... f(ar^{len - 1})}\nstd::vector<T> Multipoint_Evaluation_Geo(\n    std::vector<T>\
    \ f,\n    T a, T r, int len = -1\n){\n    if (len == -1) len = f.size();\n   \
    \ if (r == 0){\n        T tmp = 1;\n        std::vector<T> res(len, f[0]);\n \
    \       for (int i = 1; i < (int)f.size(); i++){\n            tmp *= a;\n    \
    \        res[0] += tmp * f[i];\n        }\n        return res;\n    }\n    /*\n\
    \    X[k] = sum (fi * (ar^k)^i)\n         = sum (fi * a^i * r^{ki})\n        \
    \ = sum (fi * a^i * r^t[k + i] * r^-t[k] * r^-t[i])\n         = r^-t[k] sum r^t[k\
    \ + i](fi * a^i * r^-t[i])\n    */\n    int n = f.size();\n    T invr = (T)(1)\
    \ / (T)(r);\n    T tmp = 1, tmpr1 = 1, tmpr2 = 1;\n    for (int i = 0; i < n;\
    \ i++){\n        f[i] *= tmp * tmpr2;\n        tmpr2 *= tmpr1;\n        tmpr1\
    \ *= invr;\n        tmp *= a;\n    }\n    std::vector<T> g(n + len - 1);\n   \
    \ tmpr1 = 1, tmpr2 = 1;\n    for (int i = 0; i < n + len - 1; i++){\n        g[i]\
    \ = tmpr2;\n        tmpr2 *= tmpr1;\n        tmpr1 *= r;\n    }\n    std::reverse(f.begin(),\
    \ f.end());\n    int size = 1;\n    while (size < n + len - 1) size *= 2;\n  \
    \  f.resize(size);\n    g.resize(size);\n    f = po167::FPS_cyclic_convolution(f,\
    \ g);\n    std::vector<T> res(len);\n    for (int i = n - 1; i < n + len - 1;\
    \ i++){\n        res[i - n + 1] = f[i];\n    }\n    tmpr1 = 1, tmpr2 = 1;\n  \
    \  for (int i = 0; i < len; i++){\n        res[i] *= tmpr2;\n        tmpr2 *=\
    \ tmpr1;\n        tmpr1 *= invr;\n    }\n    return res;\n}\n}\n"
  code: "#include \"FPS_cyclic_convolution.hpp\"\nnamespace po167{\ntemplate <class\
    \ T>\n// return {f(ar^0), f(ar^1), f(ar^2), ... f(ar^{len - 1})}\nstd::vector<T>\
    \ Multipoint_Evaluation_Geo(\n    std::vector<T> f,\n    T a, T r, int len = -1\n\
    ){\n    if (len == -1) len = f.size();\n    if (r == 0){\n        T tmp = 1;\n\
    \        std::vector<T> res(len, f[0]);\n        for (int i = 1; i < (int)f.size();\
    \ i++){\n            tmp *= a;\n            res[0] += tmp * f[i];\n        }\n\
    \        return res;\n    }\n    /*\n    X[k] = sum (fi * (ar^k)^i)\n        \
    \ = sum (fi * a^i * r^{ki})\n         = sum (fi * a^i * r^t[k + i] * r^-t[k] *\
    \ r^-t[i])\n         = r^-t[k] sum r^t[k + i](fi * a^i * r^-t[i])\n    */\n  \
    \  int n = f.size();\n    T invr = (T)(1) / (T)(r);\n    T tmp = 1, tmpr1 = 1,\
    \ tmpr2 = 1;\n    for (int i = 0; i < n; i++){\n        f[i] *= tmp * tmpr2;\n\
    \        tmpr2 *= tmpr1;\n        tmpr1 *= invr;\n        tmp *= a;\n    }\n \
    \   std::vector<T> g(n + len - 1);\n    tmpr1 = 1, tmpr2 = 1;\n    for (int i\
    \ = 0; i < n + len - 1; i++){\n        g[i] = tmpr2;\n        tmpr2 *= tmpr1;\n\
    \        tmpr1 *= r;\n    }\n    std::reverse(f.begin(), f.end());\n    int size\
    \ = 1;\n    while (size < n + len - 1) size *= 2;\n    f.resize(size);\n    g.resize(size);\n\
    \    f = po167::FPS_cyclic_convolution(f, g);\n    std::vector<T> res(len);\n\
    \    for (int i = n - 1; i < n + len - 1; i++){\n        res[i - n + 1] = f[i];\n\
    \    }\n    tmpr1 = 1, tmpr2 = 1;\n    for (int i = 0; i < len; i++){\n      \
    \  res[i] *= tmpr2;\n        tmpr2 *= tmpr1;\n        tmpr1 *= invr;\n    }\n\
    \    return res;\n}\n}\n"
  dependsOn:
  - fps/FPS_cyclic_convolution.hpp
  isVerificationFile: false
  path: fps/Multipoint_Evaluation_Geo.hpp
  requiredBy: []
  timestamp: '2024-09-05 06:08:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/multpoint_evalution_geo.test.cpp
documentation_of: fps/Multipoint_Evaluation_Geo.hpp
layout: document
redirect_from:
- /library/fps/Multipoint_Evaluation_Geo.hpp
- /library/fps/Multipoint_Evaluation_Geo.hpp.html
title: fps/Multipoint_Evaluation_Geo.hpp
---
