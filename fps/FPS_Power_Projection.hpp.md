---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_pick_even_odd.hpp
    title: fps/FPS_pick_even_odd.hpp
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
  bundledCode: "#line 2 \"fps/FPS_Power_Projection.hpp\"\n#include <vector>\n#include\
    \ <atcoder/convolution>\n\n#line 1 \"fps/FPS_pick_even_odd.hpp\"\n#pragma\n#line\
    \ 3 \"fps/FPS_pick_even_odd.hpp\"\n\nnamespace po167{\n// s.t |v| = 2 ^ s (no\
    \ assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T> &v, int odd){\n\
    \    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n    if (odd == 0){\n\
    \        for (int i = 0; i < z; i++){\n            v[i] = (v[i * 2] + v[i * 2\
    \ + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n        T e =\
    \ (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod() / (2\
    \ * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n    \
    \    while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}\n#line\
    \ 6 \"fps/FPS_Power_Projection.hpp\"\n\nnamespace po167{\n// n = |g|\n// return\
    \ \n// for i = 0, 1, ... , m - 1\n//     [x ^ {n - 1}] g(x) f(x) ^ i\ntemplate<class\
    \ T>\nstd::vector<T> Power_Projection(std::vector<T> g, std::vector<T> f, int\
    \ m){\n    int ind = (int)g.size() - 1;\n    int n = 1;\n    while(n < (int)g.size())\
    \ n *= 2;\n    f.reserve(4 * n);\n    g.reserve(4 * n);\n    g.resize(n, 0);\n\
    \    f.resize(n, 0);\n    std::vector<T> hold_f(n), hold_g(n);\n    // g(x) /\
    \ (y - f(x))\n    for (auto &x : f) x *= -1;\n    int nk = n;\n    T iz = (T)(1)\
    \ / (T)(2 * n);\n    while (nk != 1){\n        hold_g = g;\n        hold_f = f;\n\
    \        // n -> 4 * n\n        g.resize(4 * n);\n        f.resize(4 * n);\n \
    \       for (int i = n / nk - 1; i >= 0; i--){\n            for (int j = nk -\
    \ 1; j >= 0; j--){\n                g[i * nk * 2 + j] = g[i * nk + j];\n     \
    \           if (i) g[i * nk + j] = 0;\n                f[i * nk * 2 + j] = f[i\
    \ * nk + j];\n                if (i) f[i * nk + j] = 0;\n            }\n     \
    \   }\n        // tran\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f);\n\
    \        for (int i = 0; i < 2 * n; i++){\n            g[i * 2] *= f[i * 2 + 1];\n\
    \            g[i * 2 + 1] *= f[i * 2];\n            f[i * 2] *= f[i * 2 + 1];\n\
    \            f[i * 2 + 1] = f[i * 2];\n        }\n        FPS_pick_even_odd(g,\
    \ (ind & 1));\n        FPS_pick_even_odd(f, 0);\n        atcoder::internal::butterfly_inv(g);\n\
    \        atcoder::internal::butterfly_inv(f);\n        for (auto &x : g) x *=\
    \ iz;\n        for (auto &x : f) x *= iz;\n        // y ^ nk\n        for (int\
    \ i = 0; i < n; i++){\n            if ((ind + i + 1) & 1)\n                g[n\
    \ + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_g[i];\n            if ((i & 1)\
    \ == 0)\n                f[n + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_f[i]\
    \ * 2;\n        }\n        nk /= 2;\n        for (int i = 0; i < n; i++){\n  \
    \          g[i] = g[(i / nk) * nk * 2 + (i & (nk - 1))];\n            f[i] = f[(i\
    \ / nk) * nk * 2 + (i & (nk - 1))];\n        }\n        g.resize(n);\n       \
    \ f.resize(n);\n        ind /= 2;\n    }\n    f.push_back(1);\n    std::reverse(g.begin(),\
    \ g.end());\n    std::reverse(f.begin(), f.end());\n    g.resize(m);\n    std::vector<T>\
    \ ans = atcoder::convolution(g, FPS_inv(f, m));\n    ans.resize(m);\n    return\
    \ ans;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <atcoder/convolution>\n\n#include\
    \ \"../fps/FPS_pick_even_odd.hpp\"\n\nnamespace po167{\n// n = |g|\n// return\
    \ \n// for i = 0, 1, ... , m - 1\n//     [x ^ {n - 1}] g(x) f(x) ^ i\ntemplate<class\
    \ T>\nstd::vector<T> Power_Projection(std::vector<T> g, std::vector<T> f, int\
    \ m){\n    int ind = (int)g.size() - 1;\n    int n = 1;\n    while(n < (int)g.size())\
    \ n *= 2;\n    f.reserve(4 * n);\n    g.reserve(4 * n);\n    g.resize(n, 0);\n\
    \    f.resize(n, 0);\n    std::vector<T> hold_f(n), hold_g(n);\n    // g(x) /\
    \ (y - f(x))\n    for (auto &x : f) x *= -1;\n    int nk = n;\n    T iz = (T)(1)\
    \ / (T)(2 * n);\n    while (nk != 1){\n        hold_g = g;\n        hold_f = f;\n\
    \        // n -> 4 * n\n        g.resize(4 * n);\n        f.resize(4 * n);\n \
    \       for (int i = n / nk - 1; i >= 0; i--){\n            for (int j = nk -\
    \ 1; j >= 0; j--){\n                g[i * nk * 2 + j] = g[i * nk + j];\n     \
    \           if (i) g[i * nk + j] = 0;\n                f[i * nk * 2 + j] = f[i\
    \ * nk + j];\n                if (i) f[i * nk + j] = 0;\n            }\n     \
    \   }\n        // tran\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f);\n\
    \        for (int i = 0; i < 2 * n; i++){\n            g[i * 2] *= f[i * 2 + 1];\n\
    \            g[i * 2 + 1] *= f[i * 2];\n            f[i * 2] *= f[i * 2 + 1];\n\
    \            f[i * 2 + 1] = f[i * 2];\n        }\n        FPS_pick_even_odd(g,\
    \ (ind & 1));\n        FPS_pick_even_odd(f, 0);\n        atcoder::internal::butterfly_inv(g);\n\
    \        atcoder::internal::butterfly_inv(f);\n        for (auto &x : g) x *=\
    \ iz;\n        for (auto &x : f) x *= iz;\n        // y ^ nk\n        for (int\
    \ i = 0; i < n; i++){\n            if ((ind + i + 1) & 1)\n                g[n\
    \ + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_g[i];\n            if ((i & 1)\
    \ == 0)\n                f[n + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_f[i]\
    \ * 2;\n        }\n        nk /= 2;\n        for (int i = 0; i < n; i++){\n  \
    \          g[i] = g[(i / nk) * nk * 2 + (i & (nk - 1))];\n            f[i] = f[(i\
    \ / nk) * nk * 2 + (i & (nk - 1))];\n        }\n        g.resize(n);\n       \
    \ f.resize(n);\n        ind /= 2;\n    }\n    f.push_back(1);\n    std::reverse(g.begin(),\
    \ g.end());\n    std::reverse(f.begin(), f.end());\n    g.resize(m);\n    std::vector<T>\
    \ ans = atcoder::convolution(g, FPS_inv(f, m));\n    ans.resize(m);\n    return\
    \ ans;\n}\n}"
  dependsOn:
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: false
  path: fps/FPS_Power_Projection.hpp
  requiredBy:
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 00:51:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_Power_Projection.hpp
layout: document
redirect_from:
- /library/fps/FPS_Power_Projection.hpp
- /library/fps/FPS_Power_Projection.hpp.html
title: fps/FPS_Power_Projection.hpp
---
