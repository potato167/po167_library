---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/fps/comp_test.cpp
    title: test/fps/comp_test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - "https://maspypy.com/fps-\u5408\u6210\u30FB\u9006\u95A2\u6570\u306E\u89E3\u8AAC\
      \uFF082\uFF09\u8EE2\u7F6E\u539F\u7406\u306B\u3088\u308B\u5408\u6210\u30A2"
  bundledCode: "#line 2 \"fps/FPS_composition.hpp\"\n#include <atcoder/convolution>\n\
    \nnamespace po167{\n// n = |g|\n// return f(g(x))\n// https://maspypy.com/fps-\u5408\
    \u6210\u30FB\u9006\u95A2\u6570\u306E\u89E3\u8AAC\uFF082\uFF09\u8EE2\u7F6E\u539F\
    \u7406\u306B\u3088\u308B\u5408\u6210\u30A2\ntemplate<class T>\nstd::vector<T>\
    \ FPS_comp(std::vector<T> f, std::vector<T> g){\n    assert(g[0] == 0);\n    auto\
    \ rec = [&](auto rec, int n, int k, std::vector<T> Q) -> std::vector<T> {\n  \
    \      if (n == 1){\n            std::vector<T> p(2 * k);\n            std::reverse(f.begin(),\
    \ f.end());\n            for (int i = 0; i < k; i++) p[2 * i] = f[i];\n      \
    \      return p;\n        }\n        std::vector<T> nxt_Q(2 * n * k);\n      \
    \  for (int i = 0; i < n * k; i++) nxt_Q[n * k + i] += Q[i * 2] * 2;\n       \
    \ Q.resize(4 * n * k);\n        atcoder::internal::butterfly(Q);\n        // Q(-x)\n\
    \        std::vector<T> R(4 * n * k);\n        for (int i = 0; i < 2 * n * k;\
    \ i++){\n            R[i * 2] = Q[i * 2 + 1];\n            R[i * 2 + 1] = Q[i\
    \ * 2];\n        }\n        T iz = (T)(1) / (T)(4 * n * k);\n        for (int\
    \ i = 0; i < 4 * n * k; i++) Q[i] *= R[i];\n        for (int i = 0; i < 2 * n\
    \ * k; i++) Q[i] = Q[i * 2];\n        Q.resize(2 * n * k);\n        atcoder::internal::butterfly_inv(Q);\n\
    \        for (int i = 0; i < 2 * n * k; i++) nxt_Q[i] += Q[i] * iz * 2;\n    \
    \    for (int j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){\n      \
    \      nxt_Q[n * j + i] = 0;\n        }\n        std::vector<T> pq = rec(rec,\
    \ n / 2, k * 2, nxt_Q);\n        std::vector<T> p(2 * n * k);\n        for (int\
    \ j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){\n            pq[n *\
    \ j + i] = 0;\n        }\n        for (int i = 0; i < n * k; i++) p[i * 2 + 1]\
    \ += pq[n * k + i];\n        std::reverse(pq.begin(), pq.end());\n        atcoder::internal::butterfly(pq);\n\
    \        pq.resize(4 * n * k);\n        for (int i = 2 * n * k - 1; i >= 0; i--){\n\
    \            pq[i * 2 + 1] = pq[i];\n            pq[i * 2] = pq[i];\n        }\n\
    \        for (int i = 0; i < 4 * n * k; i++) pq[i] *= R[i];\n        atcoder::internal::butterfly_inv(pq);\n\
    \        for (int i = 0; i < 2 * n * k; i++) p[i] += pq[4 * n * k - 1 - i] * iz;\n\
    \        return p;\n    };\n    int N = (int)g.size();\n    int n = 1;\n    while\
    \ (n < N) n *= 2;\n    f.resize(n, 0);\n    g.resize(n, 0);\n    std::vector<T>\
    \ Q(2 * n);\n    for (int i = 0; i < n; i++) Q[i] = -g[i];\n    auto p = rec(rec,\
    \ n, 1, Q);\n    std::vector<T> res(n);\n    for (int i = 0; i < n; i++) res[i]\
    \ = p[i];\n    std::reverse(res.begin(), res.end());\n    res.resize(N);\n   \
    \ return res;\n}\n}\n"
  code: "#pragma once\n#include <atcoder/convolution>\n\nnamespace po167{\n// n =\
    \ |g|\n// return f(g(x))\n// https://maspypy.com/fps-\u5408\u6210\u30FB\u9006\u95A2\
    \u6570\u306E\u89E3\u8AAC\uFF082\uFF09\u8EE2\u7F6E\u539F\u7406\u306B\u3088\u308B\
    \u5408\u6210\u30A2\ntemplate<class T>\nstd::vector<T> FPS_comp(std::vector<T>\
    \ f, std::vector<T> g){\n    assert(g[0] == 0);\n    auto rec = [&](auto rec,\
    \ int n, int k, std::vector<T> Q) -> std::vector<T> {\n        if (n == 1){\n\
    \            std::vector<T> p(2 * k);\n            std::reverse(f.begin(), f.end());\n\
    \            for (int i = 0; i < k; i++) p[2 * i] = f[i];\n            return\
    \ p;\n        }\n        std::vector<T> nxt_Q(2 * n * k);\n        for (int i\
    \ = 0; i < n * k; i++) nxt_Q[n * k + i] += Q[i * 2] * 2;\n        Q.resize(4 *\
    \ n * k);\n        atcoder::internal::butterfly(Q);\n        // Q(-x)\n      \
    \  std::vector<T> R(4 * n * k);\n        for (int i = 0; i < 2 * n * k; i++){\n\
    \            R[i * 2] = Q[i * 2 + 1];\n            R[i * 2 + 1] = Q[i * 2];\n\
    \        }\n        T iz = (T)(1) / (T)(4 * n * k);\n        for (int i = 0; i\
    \ < 4 * n * k; i++) Q[i] *= R[i];\n        for (int i = 0; i < 2 * n * k; i++)\
    \ Q[i] = Q[i * 2];\n        Q.resize(2 * n * k);\n        atcoder::internal::butterfly_inv(Q);\n\
    \        for (int i = 0; i < 2 * n * k; i++) nxt_Q[i] += Q[i] * iz * 2;\n    \
    \    for (int j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){\n      \
    \      nxt_Q[n * j + i] = 0;\n        }\n        std::vector<T> pq = rec(rec,\
    \ n / 2, k * 2, nxt_Q);\n        std::vector<T> p(2 * n * k);\n        for (int\
    \ j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){\n            pq[n *\
    \ j + i] = 0;\n        }\n        for (int i = 0; i < n * k; i++) p[i * 2 + 1]\
    \ += pq[n * k + i];\n        std::reverse(pq.begin(), pq.end());\n        atcoder::internal::butterfly(pq);\n\
    \        pq.resize(4 * n * k);\n        for (int i = 2 * n * k - 1; i >= 0; i--){\n\
    \            pq[i * 2 + 1] = pq[i];\n            pq[i * 2] = pq[i];\n        }\n\
    \        for (int i = 0; i < 4 * n * k; i++) pq[i] *= R[i];\n        atcoder::internal::butterfly_inv(pq);\n\
    \        for (int i = 0; i < 2 * n * k; i++) p[i] += pq[4 * n * k - 1 - i] * iz;\n\
    \        return p;\n    };\n    int N = (int)g.size();\n    int n = 1;\n    while\
    \ (n < N) n *= 2;\n    f.resize(n, 0);\n    g.resize(n, 0);\n    std::vector<T>\
    \ Q(2 * n);\n    for (int i = 0; i < n; i++) Q[i] = -g[i];\n    auto p = rec(rec,\
    \ n, 1, Q);\n    std::vector<T> res(n);\n    for (int i = 0; i < n; i++) res[i]\
    \ = p[i];\n    std::reverse(res.begin(), res.end());\n    res.resize(N);\n   \
    \ return res;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_composition.hpp
  requiredBy:
  - test/fps/comp_test.cpp
  timestamp: '2025-10-10 06:41:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_composition.hpp
layout: document
redirect_from:
- /library/fps/FPS_composition.hpp
- /library/fps/FPS_composition.hpp.html
title: fps/FPS_composition.hpp
---
