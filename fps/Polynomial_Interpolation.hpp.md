---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Product_Sequence.hpp
    title: fps/FPS_Product_Sequence.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_add.hpp
    title: fps/FPS_add.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_division.hpp
    title: fps/FPS_division.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  - icon: ':heavy_check_mark:'
    path: fps/Multipoint_Evaluation.hpp
    title: fps/Multipoint_Evaluation.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/polynomial_interpolation.test.cpp
    title: test/fps/polynomial_interpolation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_Product_Sequence.hpp\"\n#include <vector>\n#include\
    \ <atcoder/convolution>\n\nnamespace po167{\ntemplate<class T>\nstd::vector<T>\
    \ FPS_Product_Sequence(std::vector<std::vector<T>> f){\n    if (f.empty()) return\
    \ {1};\n    auto op = [&](auto self,int l, int r) -> std::vector<T> {\n      \
    \  if (l + 1 == r) return f[l];\n        int m = (l + r) / 2;\n        return\
    \ atcoder::convolution(self(self, l, m), self(self, m, r));\n    };\n    return\
    \ op(op, 0, f.size());\n}\n}\n#line 4 \"fps/FPS_division.hpp\"\n\n#line 4 \"fps/FPS_inv.hpp\"\
    \n\nnamespace po167{\n// return 1 / f\ntemplate <class T>\nstd::vector<T> FPS_inv(std::vector<T>\
    \ f, int len = -1){\n    if (len == -1) len = f.size();\n    assert(f[0] != 0);\n\
    \    std::vector<T> g = {1 / f[0]};\n    int s = 1;\n    while(s < len){\n   \
    \     // g = 2g_s - f(g_s)^2 (mod x ^ (2 * s))\n        // g = g - (fg - 1)g\n\
    \        // (fg - 1) = 0 (mod x ^ (s))\n        std::vector<T> n_g(s * 2, 0);\n\
    \        std::vector<T> f_s(s * 2, 0);\n        g.resize(s * 2);\n        for\
    \ (int i = 0; i < s * 2; i++){\n            if (int(f.size()) > i) f_s[i] = f[i];\n\
    \            n_g[i] = g[i];\n        }\n        atcoder::internal::butterfly(g);\n\
    \        atcoder::internal::butterfly(f_s);\n        for (int i = 0; i < s * 2;\
    \ i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        T iz = 1 / (T)(s * 2);\n        for (int i = s; i < s * 2; i++){\n  \
    \          f_s[i] *= iz;\n        }\n        for (int i = 0; i < s; i++){\n  \
    \          f_s[i] = 0;\n        }\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        for (int i = s;\
    \ i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n        }\n        std::swap(n_g,\
    \ g);\n        s *= 2;\n    }\n    g.resize(len);\n    return g;\n}\n}\n#line\
    \ 6 \"fps/FPS_division.hpp\"\nnamespace po167{\ntemplate<class T>\n// f = g *\
    \ res.first + res.second\n// |res.first| <= |f| - |g| + 1\n// |res.second| <=\
    \ |g| - 1\nstd::pair<std::vector<T>, std::vector<T>>\nFPS_division(std::vector<T>\
    \ f, std::vector<T> g){\n    while (!f.empty() && f.back() == 0) f.pop_back();\n\
    \    assert(!g.empty() && g.back() != 0);\n    if (f.size() < g.size()){\n   \
    \     return {{}, f};\n    }\n    // rev(f) / rev(g) = rev(q) (mod x ^ {|f| -\
    \ |g| + 1})\n    std::vector<T> r = f;\n    std::reverse(f.begin(), f.end());\n\
    \    std::reverse(g.begin(), g.end());\n    int z = (int)f.size() - (int)g.size()\
    \ + 1;\n    f.resize(z);\n    std::vector<T> q = atcoder::convolution(f, FPS_inv(g,\
    \ z));\n    q.resize(z);\n    std::reverse(g.begin(), g.end());\n    std::reverse(q.begin(),\
    \ q.end());\n    f = atcoder::convolution(q, g);\n    for (int i = 0; i < (int)f.size();\
    \ i++) r[i] -= f[i];\n    while (!q.empty() && q.back() == 0) q.pop_back();\n\
    \    while (!r.empty() && r.back() == 0) r.pop_back();\n    return {q, r};\n}\n\
    }\n#line 4 \"fps/Multipoint_Evaluation.hpp\"\n\nnamespace po167{\n// return {f(p[0]),\
    \ f(p[1]), f(p[2]), ... }\ntemplate <class T>\nstd::vector<T> Multipoint_Evaluation(\n\
    \    std::vector<T> f,\n    std::vector<T> p\n){\n    int m = p.size();\n    if\
    \ (m == 0) return {};\n    if (m == 1){\n        T res = 0;\n        T tmp = 1;\n\
    \        for (auto x : f) res += tmp * x, tmp *= p[0];\n        return {res};\n\
    \    }\n    int size = 1;\n    while (size < m) size *= 2;\n    std::vector<std::vector<T>>\
    \ prod(size * 2);\n    for (int i = 0; i < size; i++){\n        if (i < m) prod[i\
    \ + size] = {(T)(-1) * p[i], 1};\n        else prod[i + size] = {1};\n    }\n\
    \    for (int i = size - 1; i > 0; i--){\n        prod[i] = atcoder::convolution(prod[i\
    \ * 2], prod[i * 2 + 1]);\n    }\n    std::vector<T> res(m);\n    auto calc =\
    \ [&](auto self, int l, int r, int ind, std::vector<T> tmp) -> void {\n      \
    \  if (m <= l) return;\n        if (l + 1 == r){\n            res[l] = (tmp.empty()\
    \ ? T(0) : tmp[0]);\n            return;\n        }\n        int mid = (l + r)\
    \ / 2;\n        self(self, l, mid, ind * 2, po167::FPS_division(tmp, prod[ind\
    \ * 2]).second);\n        self(self, mid, r, ind * 2 + 1, po167::FPS_division(tmp,\
    \ prod[ind * 2 + 1]).second);\n    };calc(calc, 0, size, 1, f);\n    return res;\n\
    }\n}\n#line 3 \"fps/FPS_add.hpp\"\n\nnamespace po167{\ntemplate <class T>\n//\
    \ a(x) += b(x) * c * x^d\nvoid FPS_add(std::vector<T> &a, std::vector<T> b, T\
    \ c = 1, int d = 0){\n    for (int i = 0; i < (int)(b.size()); i++){\n       \
    \ while ((int)a.size() <= i + d) a.push_back((T)0);\n        a[i + d] += b[i]\
    \ * c;\n    }\n}\n}\n#line 5 \"fps/Polynomial_Interpolation.hpp\"\n\nnamespace\
    \ po167{\ntemplate<class T>\n// \u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\u306E\u591A\
    \u9805\u5F0F\u88DC\u5B8C\n// f(X[i]) = Y[i] \u3067\u3042\u308B f \u3092\u8FD4\u3059\
    \nstd::vector<T> Polynomial_Interpolation(std::vector<int> X, std::vector<T> Y){\n\
    \    int N = X.size();\n    assert(Y.size() == X.size());\n    if (N == 0) return\
    \ {};\n    {\n        auto Z = X;\n        std::sort(Z.begin(), Z.end());\n  \
    \      for (int i = 0; i < N - 1; i++){\n            assert(Z[i] != Z[i + 1]);\n\
    \        }\n    }\n    std::vector<std::vector<T>> p(N);\n    for (int i = 0;\
    \ i < N; i++) p[i] = {-X[i], 1};\n    auto g = FPS_Product_Sequence(p);\n    for\
    \ (int i = 0; i < N; i++){\n        g[i] = g[i + 1] * (i + 1);\n    }\n    g.pop_back();\n\
    \    std::vector<T> xt(N);\n    for (int i = 0; i < N; i++) xt[i] = X[i];\n  \
    \  auto Z = Multipoint_Evaluation(g, xt);\n    auto rec = [&](auto self, int l,\
    \ int r) -> std::pair<std::vector<T>, std::vector<T>> {\n        if (l + 1 ==\
    \ r){\n            return {{Y[l] / Z[l]}, {-X[l], 1}};\n        }\n        int\
    \ m = (l + r) / 2;\n        auto L = self(self, l, m);\n        auto R = self(self,\
    \ m, r);\n        auto D = atcoder::convolution(L.second, R.second);\n       \
    \ auto U = atcoder::convolution(L.second, R.first);\n        FPS_add(U, atcoder::convolution(L.first,\
    \ R.second));\n        return {U, D};\n    };\n    return rec(rec, 0, N).first;\n\
    }\n}\n"
  code: "#pragma once\n#include \"FPS_Product_Sequence.hpp\"\n#include \"Multipoint_Evaluation.hpp\"\
    \n#include \"FPS_add.hpp\"\n\nnamespace po167{\ntemplate<class T>\n// \u30E9\u30B0\
    \u30E9\u30F3\u30B8\u30E5\u306E\u591A\u9805\u5F0F\u88DC\u5B8C\n// f(X[i]) = Y[i]\
    \ \u3067\u3042\u308B f \u3092\u8FD4\u3059\nstd::vector<T> Polynomial_Interpolation(std::vector<int>\
    \ X, std::vector<T> Y){\n    int N = X.size();\n    assert(Y.size() == X.size());\n\
    \    if (N == 0) return {};\n    {\n        auto Z = X;\n        std::sort(Z.begin(),\
    \ Z.end());\n        for (int i = 0; i < N - 1; i++){\n            assert(Z[i]\
    \ != Z[i + 1]);\n        }\n    }\n    std::vector<std::vector<T>> p(N);\n   \
    \ for (int i = 0; i < N; i++) p[i] = {-X[i], 1};\n    auto g = FPS_Product_Sequence(p);\n\
    \    for (int i = 0; i < N; i++){\n        g[i] = g[i + 1] * (i + 1);\n    }\n\
    \    g.pop_back();\n    std::vector<T> xt(N);\n    for (int i = 0; i < N; i++)\
    \ xt[i] = X[i];\n    auto Z = Multipoint_Evaluation(g, xt);\n    auto rec = [&](auto\
    \ self, int l, int r) -> std::pair<std::vector<T>, std::vector<T>> {\n       \
    \ if (l + 1 == r){\n            return {{Y[l] / Z[l]}, {-X[l], 1}};\n        }\n\
    \        int m = (l + r) / 2;\n        auto L = self(self, l, m);\n        auto\
    \ R = self(self, m, r);\n        auto D = atcoder::convolution(L.second, R.second);\n\
    \        auto U = atcoder::convolution(L.second, R.first);\n        FPS_add(U,\
    \ atcoder::convolution(L.first, R.second));\n        return {U, D};\n    };\n\
    \    return rec(rec, 0, N).first;\n}\n}\n"
  dependsOn:
  - fps/FPS_Product_Sequence.hpp
  - fps/Multipoint_Evaluation.hpp
  - fps/FPS_division.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_add.hpp
  isVerificationFile: false
  path: fps/Polynomial_Interpolation.hpp
  requiredBy: []
  timestamp: '2025-10-18 21:09:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/polynomial_interpolation.test.cpp
documentation_of: fps/Polynomial_Interpolation.hpp
layout: document
redirect_from:
- /library/fps/Polynomial_Interpolation.hpp
- /library/fps/Polynomial_Interpolation.hpp.html
title: fps/Polynomial_Interpolation.hpp
---
