---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/sparse_exp.test.cpp
    title: test/fps/sparse_exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/sparse_inv.test.cpp
    title: test/fps/sparse_inv.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/sparse_log.test.cpp
    title: test/fps/sparse_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/sparse_pow.test.cpp
    title: test/fps/sparse_pow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_sparse.hpp\"\n#include <vector>\n#include <cassert>\n\
    \nnamespace po167{\ntemplate<class T>\nstd::vector<T> make_inv_vector(int N){\n\
    \    std::vector<T> fact(1 + N, 1);\n    std::vector<T> inv(1 + N, 1);\n    for\
    \ (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i;\n    T tmp = 1;\n    tmp\
    \ = tmp / fact[N];\n    for (int i = N; i >= 1; i--){\n        inv[i] = tmp *\
    \ fact[i - 1];\n        tmp = tmp * i;\n    }\n    return inv;\n}\ntemplate<class\
    \ T>\nstd::vector<std::pair<int, T>> pick_value(std::vector<T> f){\n    std::vector<std::pair<int,\
    \ T>> res;\n    for (int i = 0; i < (int)(f.size()); i++){\n        if (f[i] !=\
    \ 0){\n            res.push_back({i, f[i]});\n        }\n    }\n    return res;\n\
    }\n\n// f \u306B\u5B9A\u6570\u9805\u304C\u306A\u3044\u3068\u304D\u306E\u8FD4\u308A\
    \u5024\u306F\u30A8\u30E9\u30FC\u3092\u8D77\u3053\u3057\u307E\u3059\u3002\ntemplate<class\
    \ T>\nstd::vector<T> FPS_sparse_inv(std::vector<T> f, int m = -1){\n    if (m\
    \ < 0) m = (int)f.size();\n    if (m == 0) return {};\n    assert(!f.empty() &&\
    \ f[0] != 0);\n    std::vector<T> res(m);\n    T inv = (T)(1) / f[0];\n    res[0]\
    \ = inv;\n    auto p = pick_value(f);\n    for (int i = 1; i < m; i++){\n    \
    \    for (auto [a, b] : p) if (a != 0 && a <= i){\n            res[i] -= b * res[i\
    \ - a];\n        }\n        res[i] *= inv;\n    }\n    return res;\n}\n\n/*\n\
    \ * return F = log(f)\n * F' = (1 / f) f'\n * s.t f[0] == 1\n */\ntemplate<class\
    \ T>\nstd::vector<T> FPS_sparse_log(std::vector<T> f, int m = -1) {\n    if (m\
    \ == -1) m = (int)f.size();\n    if (m == 0) return {};\n    assert(!f.empty()\
    \ && f[0] == 1);\n    auto inv = FPS_sparse_inv(f, m - 1);\n    // f <- f'\n \
    \   for (int i = 1; i < (int)f.size(); i++){\n        f[i - 1] = f[i] * i;\n \
    \   }\n    f.pop_back();\n    std::vector<T> res(m - 1);\n    for (int i = 0;\
    \ i < (int)f.size(); i++) if (f[i] != 0){\n        for (int j = 0; j < m - 1 -\
    \ i; j++){\n            res[j + i] += inv[j] * f[i];\n        }\n    }\n    inv\
    \ = make_inv_vector<T>(m);\n    res.push_back(0);\n    for (int i = m - 1; i >\
    \ 0; i--){\n        res[i] = res[i - 1] * inv[i];\n    }\n    res[0] = 0;\n  \
    \  return res;\n}\n\n/*\n * return F = exp(f)\n * F' = f'F\n * s.t f[0] = 0\n\
    \ */\ntemplate<class T>\nstd::vector<T> FPS_sparse_exp(std::vector<T> f, int m\
    \ = -1){\n    if (m == -1) m = (int)f.size();\n    if (m == 0) return {};\n  \
    \  if (f.empty()){\n        std::vector<T> res(m, 0);\n        res[0] = 1;\n \
    \       return res;\n    }\n    assert(f[0] == 0);\n    auto p = pick_value(f);\n\
    \    std::vector<T> res(m);\n    res[0] = 1;\n    auto inv = make_inv_vector<T>(m\
    \ + 1);\n    for (int i = 1; i < m; i++){\n        for (auto [a, b] : p){\n  \
    \          if (a <= i){\n                res[i] += b * res[i - a] * a;\n     \
    \       }\n        }\n        res[i] *= inv[i];\n    }\n    return res;\n}\n/*\n\
    \ * return F = f^n\n * F' = n * f^{n - 1} * f'\n * fF' = n * F * f'\n *\n */\n\
    template<class T>\nstd::vector<T> FPS_sparse_pow(std::vector<T> f, long long n,\
    \ int m = -1){\n    if (m == -1) m = (int)f.size();\n    if (m == 0) return {};\n\
    \    if (n == 0){\n        std::vector<T> res(m, 0);\n        res[0] = 1;\n  \
    \      return res;\n    }\n    int non_zero_ind = -1;\n    for (int i = 0; i <\
    \ (int)f.size(); i++){\n        if (f[i] != 0){\n            non_zero_ind = i;\n\
    \            break;\n        }\n    }\n    // a * b >= c\n    // b >= c / a\n\
    \    if (non_zero_ind == -1\n    || (non_zero_ind != 0 && (n > m / (long long)(non_zero_ind)\
    \ || (long long)(non_zero_ind) * n >= m))){\n        std::vector<T> res(m, 0);\n\
    \        return res;\n    }\n    if (non_zero_ind){\n        assert(n >= 0);\n\
    \        std::vector<T> nf((int)(f.size()) - non_zero_ind * n);\n        for (int\
    \ i = non_zero_ind; i < (int)(f.size()); i++){\n            if (i - non_zero_ind\
    \ < (int)nf.size()) nf[i - non_zero_ind] = f[i];\n        }\n        auto tmp\
    \ = FPS_sparse_pow(nf, n, m - non_zero_ind * n);\n        std::vector<T> res(m,\
    \ 0);\n        for (int i = 0; i < (int)tmp.size(); i++){\n            res[i +\
    \ non_zero_ind * n] = tmp[i];\n        }\n        return res;\n    }\n    std::vector<T>\
    \ res(m, 0);\n    // f[0] \u306F pow \u3067\u6C42\u3081\u308B\n    {\n       \
    \ res[0] = 1;\n        long long tmp = n;\n        T v = f[0];\n        if (n\
    \ < 0){\n            tmp = -tmp;\n            v = (T)(1) / v;\n        }\n   \
    \     while (tmp){\n            if (tmp & 1) res[0] *= v;\n            v = v *\
    \ v;\n            tmp /= 2;\n        }\n    }\n    T inv = (T)(1) / f[0];\n  \
    \  auto invs = make_inv_vector<T>(m);\n    // fF' = n * F * f'\n    auto p = pick_value(f);\n\
    \    for (int i = 1; i < m; i++){\n        for (auto [a, b] : p) if (a != 0){\n\
    \            if (a <= i){\n                res[i] += b * (T)(a) * res[i - a] *\
    \ (T)(n);\n            }\n            if (a < i){\n                res[i] -= b\
    \ * res[i - a] * (T)(i - a);\n            }\n        }\n        res[i] *= inv;\n\
    \        res[i] *= invs[i];\n    }\n    return res;\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\n\nnamespace po167{\n\
    template<class T>\nstd::vector<T> make_inv_vector(int N){\n    std::vector<T>\
    \ fact(1 + N, 1);\n    std::vector<T> inv(1 + N, 1);\n    for (int i = 1; i <=\
    \ N; i++) fact[i] = fact[i - 1] * i;\n    T tmp = 1;\n    tmp = tmp / fact[N];\n\
    \    for (int i = N; i >= 1; i--){\n        inv[i] = tmp * fact[i - 1];\n    \
    \    tmp = tmp * i;\n    }\n    return inv;\n}\ntemplate<class T>\nstd::vector<std::pair<int,\
    \ T>> pick_value(std::vector<T> f){\n    std::vector<std::pair<int, T>> res;\n\
    \    for (int i = 0; i < (int)(f.size()); i++){\n        if (f[i] != 0){\n   \
    \         res.push_back({i, f[i]});\n        }\n    }\n    return res;\n}\n\n\
    // f \u306B\u5B9A\u6570\u9805\u304C\u306A\u3044\u3068\u304D\u306E\u8FD4\u308A\u5024\
    \u306F\u30A8\u30E9\u30FC\u3092\u8D77\u3053\u3057\u307E\u3059\u3002\ntemplate<class\
    \ T>\nstd::vector<T> FPS_sparse_inv(std::vector<T> f, int m = -1){\n    if (m\
    \ < 0) m = (int)f.size();\n    if (m == 0) return {};\n    assert(!f.empty() &&\
    \ f[0] != 0);\n    std::vector<T> res(m);\n    T inv = (T)(1) / f[0];\n    res[0]\
    \ = inv;\n    auto p = pick_value(f);\n    for (int i = 1; i < m; i++){\n    \
    \    for (auto [a, b] : p) if (a != 0 && a <= i){\n            res[i] -= b * res[i\
    \ - a];\n        }\n        res[i] *= inv;\n    }\n    return res;\n}\n\n/*\n\
    \ * return F = log(f)\n * F' = (1 / f) f'\n * s.t f[0] == 1\n */\ntemplate<class\
    \ T>\nstd::vector<T> FPS_sparse_log(std::vector<T> f, int m = -1) {\n    if (m\
    \ == -1) m = (int)f.size();\n    if (m == 0) return {};\n    assert(!f.empty()\
    \ && f[0] == 1);\n    auto inv = FPS_sparse_inv(f, m - 1);\n    // f <- f'\n \
    \   for (int i = 1; i < (int)f.size(); i++){\n        f[i - 1] = f[i] * i;\n \
    \   }\n    f.pop_back();\n    std::vector<T> res(m - 1);\n    for (int i = 0;\
    \ i < (int)f.size(); i++) if (f[i] != 0){\n        for (int j = 0; j < m - 1 -\
    \ i; j++){\n            res[j + i] += inv[j] * f[i];\n        }\n    }\n    inv\
    \ = make_inv_vector<T>(m);\n    res.push_back(0);\n    for (int i = m - 1; i >\
    \ 0; i--){\n        res[i] = res[i - 1] * inv[i];\n    }\n    res[0] = 0;\n  \
    \  return res;\n}\n\n/*\n * return F = exp(f)\n * F' = f'F\n * s.t f[0] = 0\n\
    \ */\ntemplate<class T>\nstd::vector<T> FPS_sparse_exp(std::vector<T> f, int m\
    \ = -1){\n    if (m == -1) m = (int)f.size();\n    if (m == 0) return {};\n  \
    \  if (f.empty()){\n        std::vector<T> res(m, 0);\n        res[0] = 1;\n \
    \       return res;\n    }\n    assert(f[0] == 0);\n    auto p = pick_value(f);\n\
    \    std::vector<T> res(m);\n    res[0] = 1;\n    auto inv = make_inv_vector<T>(m\
    \ + 1);\n    for (int i = 1; i < m; i++){\n        for (auto [a, b] : p){\n  \
    \          if (a <= i){\n                res[i] += b * res[i - a] * a;\n     \
    \       }\n        }\n        res[i] *= inv[i];\n    }\n    return res;\n}\n/*\n\
    \ * return F = f^n\n * F' = n * f^{n - 1} * f'\n * fF' = n * F * f'\n *\n */\n\
    template<class T>\nstd::vector<T> FPS_sparse_pow(std::vector<T> f, long long n,\
    \ int m = -1){\n    if (m == -1) m = (int)f.size();\n    if (m == 0) return {};\n\
    \    if (n == 0){\n        std::vector<T> res(m, 0);\n        res[0] = 1;\n  \
    \      return res;\n    }\n    int non_zero_ind = -1;\n    for (int i = 0; i <\
    \ (int)f.size(); i++){\n        if (f[i] != 0){\n            non_zero_ind = i;\n\
    \            break;\n        }\n    }\n    // a * b >= c\n    // b >= c / a\n\
    \    if (non_zero_ind == -1\n    || (non_zero_ind != 0 && (n > m / (long long)(non_zero_ind)\
    \ || (long long)(non_zero_ind) * n >= m))){\n        std::vector<T> res(m, 0);\n\
    \        return res;\n    }\n    if (non_zero_ind){\n        assert(n >= 0);\n\
    \        std::vector<T> nf((int)(f.size()) - non_zero_ind * n);\n        for (int\
    \ i = non_zero_ind; i < (int)(f.size()); i++){\n            if (i - non_zero_ind\
    \ < (int)nf.size()) nf[i - non_zero_ind] = f[i];\n        }\n        auto tmp\
    \ = FPS_sparse_pow(nf, n, m - non_zero_ind * n);\n        std::vector<T> res(m,\
    \ 0);\n        for (int i = 0; i < (int)tmp.size(); i++){\n            res[i +\
    \ non_zero_ind * n] = tmp[i];\n        }\n        return res;\n    }\n    std::vector<T>\
    \ res(m, 0);\n    // f[0] \u306F pow \u3067\u6C42\u3081\u308B\n    {\n       \
    \ res[0] = 1;\n        long long tmp = n;\n        T v = f[0];\n        if (n\
    \ < 0){\n            tmp = -tmp;\n            v = (T)(1) / v;\n        }\n   \
    \     while (tmp){\n            if (tmp & 1) res[0] *= v;\n            v = v *\
    \ v;\n            tmp /= 2;\n        }\n    }\n    T inv = (T)(1) / f[0];\n  \
    \  auto invs = make_inv_vector<T>(m);\n    // fF' = n * F * f'\n    auto p = pick_value(f);\n\
    \    for (int i = 1; i < m; i++){\n        for (auto [a, b] : p) if (a != 0){\n\
    \            if (a <= i){\n                res[i] += b * (T)(a) * res[i - a] *\
    \ (T)(n);\n            }\n            if (a < i){\n                res[i] -= b\
    \ * res[i - a] * (T)(i - a);\n            }\n        }\n        res[i] *= inv;\n\
    \        res[i] *= invs[i];\n    }\n    return res;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_sparse.hpp
  requiredBy: []
  timestamp: '2025-10-18 20:08:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/sparse_log.test.cpp
  - test/fps/sparse_inv.test.cpp
  - test/fps/sparse_exp.test.cpp
  - test/fps/sparse_pow.test.cpp
documentation_of: fps/FPS_sparse.hpp
layout: document
redirect_from:
- /library/fps/FPS_sparse.hpp
- /library/fps/FPS_sparse.hpp.html
title: fps/FPS_sparse.hpp
---
