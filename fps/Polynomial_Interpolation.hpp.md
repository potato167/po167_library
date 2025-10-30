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
    \ op(op, 0, f.size());\n}\n}\n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n\
    // return 1 / f\ntemplate <class T>\nstd::vector<T> FPS_inv(std::vector<T> f,\
    \ int len = -1){\n    if (len == -1) len = f.size();\n    assert(f[0] != 0);\n\
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
    \ 5 \"fps/Multipoint_Evaluation.hpp\"\n\nnamespace po167{\n// return {f(p[0]),\
    \ f(p[1]), f(p[2]), ... }\n// https://codeforces.com/blog/entry/100279\ntemplate<class\
    \ T>\nstd::vector<T> Multipoint_Evaluation(std::vector<T> f, std::vector<T> p){\n\
    \    std::reverse(f.begin(), f.end());\n    int M = f.size();\n    int N = p.size();\n\
    \    std::vector<std::vector<T>> g(N);\n    for (int i = 0; i < N; i++){\n   \
    \     g[i] = {1, p[i] * -1};\n    }\n    auto tmp = po167::FPS_Product_Sequence(g);\n\
    \    tmp = po167::FPS_inv(tmp, M);\n    tmp = atcoder::convolution(tmp, f);\n\
    \    tmp.resize(M);\n    int size = 1;\n    while (size < N) size *= 2;\n    std::vector<std::vector<T>>\
    \ seg(size * 2, {1});\n    for (int i = 0; i < N; i++){\n        seg[i + size]\
    \ = g[i];\n    }\n    for (int i = size - 1; i > 0; i--){\n        seg[i] = atcoder::convolution(seg[i\
    \ * 2], seg[i * 2 + 1]);\n    }\n\n    std::vector<T> inv = {1, (T)(1) / (T)(2)};\n\
    \    // a, b \u306E convolution \u306E\u3046\u3061\u3001l, r \u306E\u9593\u3060\
    \u3051\u6B32\u3057\u3044\n    auto calc = [&](std::vector<T> a, std::vector<T>\
    \ b, int l, int r) -> std::vector<T> {\n        if (l == r) return {};\n     \
    \   if (l < 0) l = 0;\n        while ((int)a.size() > r) a.pop_back();\n     \
    \   while ((int)b.size() > r) b.pop_back();\n        int lim = (int)a.size() +\
    \ (int)b.size() - 1;\n        lim -= std::min(lim - r, l);\n        int z = 0;\n\
    \        while ((1 << z) < lim) z++;\n        a.resize((1 << z), 0);\n       \
    \ b.resize((1 << z), 0);\n        atcoder::internal::butterfly(a);\n        atcoder::internal::butterfly(b);\n\
    \        for (int i = 0; i < (1 << z); i++) a[i] *= b[i];\n        atcoder::internal::butterfly_inv(a);\n\
    \        while ((int)inv.size() <= z){\n            inv.push_back(inv.back() *\
    \ inv[1]);\n        }\n        std::vector<T> d(r - l);\n        for (int i =\
    \ l; i < r; i++) d[i - l] = a[i] * inv[z];\n        return d;\n    };\n\n    std::vector<T>\
    \ res(N);\n    auto rec = [&](auto self, int ind, std::vector<T> v) -> void {\n\
    \        if ((int)seg[ind].size() == 1){\n            return;\n        }\n   \
    \     if (size <= ind){\n            res[ind - size] = v.back();\n           \
    \ return;\n        }\n        self(self, ind * 2, calc(v, seg[ind * 2 + 1], (int)(v.size()\
    \ - seg[ind * 2].size() + 1) ,(int)v.size()));\n        self(self, ind * 2 + 1,\
    \ calc(v, seg[ind * 2], (int)(v.size() - seg[ind * 2 + 1].size() + 1) ,(int)v.size()));\n\
    \    };\n    rec(rec, 1, tmp);\n    return res;\n}\n}\n#line 3 \"fps/FPS_add.hpp\"\
    \n\nnamespace po167{\ntemplate <class T>\n// a(x) += b(x) * c * x^d\nvoid FPS_add(std::vector<T>\
    \ &a, std::vector<T> b, T c = 1, int d = 0){\n    for (int i = 0; i < (int)(b.size());\
    \ i++){\n        while ((int)a.size() <= i + d) a.push_back((T)0);\n        a[i\
    \ + d] += b[i] * c;\n    }\n}\n}\n#line 5 \"fps/Polynomial_Interpolation.hpp\"\
    \n\nnamespace po167{\ntemplate<class T>\n// \u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\
    \u306E\u591A\u9805\u5F0F\u88DC\u5B8C\n// f(X[i]) = Y[i] \u3067\u3042\u308B f \u3092\
    \u8FD4\u3059\nstd::vector<T> Polynomial_Interpolation(std::vector<int> X, std::vector<T>\
    \ Y){\n    int N = X.size();\n    assert(Y.size() == X.size());\n    if (N ==\
    \ 0) return {};\n    {\n        auto Z = X;\n        std::sort(Z.begin(), Z.end());\n\
    \        for (int i = 0; i < N - 1; i++){\n            assert(Z[i] != Z[i + 1]);\n\
    \        }\n    }\n    std::vector<std::vector<T>> p(N);\n    for (int i = 0;\
    \ i < N; i++) p[i] = {-X[i], 1};\n    auto g = FPS_Product_Sequence(p);\n    for\
    \ (int i = 0; i < N; i++){\n        g[i] = g[i + 1] * (i + 1);\n    }\n    g.pop_back();\n\
    \    std::vector<T> xt(N);\n    for (int i = 0; i < N; i++) xt[i] = X[i];\n  \
    \  auto Z = Multipoint_Evaluation(g, xt);\n    std::vector<T> inv = {1, (T)(1)\
    \ / (T)(2)};\n    auto rec = [&](auto self, int l, int r) -> std::pair<std::vector<T>,\
    \ std::vector<T>> {\n        if (l + 1 == r){\n            return {{Y[l] / Z[l]},\
    \ {-X[l], 1}};\n        }\n        int m = (l + r) / 2;\n        auto [Lf, Ls]\
    \ = self(self, l, m);\n        auto [Rf, Rs] = self(self, m, r);\n        int\
    \ mx_size = r - l + 1;\n        if (mx_size < 128){\n            auto D = atcoder::convolution(Ls,\
    \ Rs);\n            auto U = atcoder::convolution(Ls, Rf);\n            FPS_add(U,\
    \ atcoder::convolution(Lf, Rs));\n            return {U, D};\n        }\n    \
    \    int z = 0;\n        while ((1 << z) < mx_size) z++;\n        while (int(inv.size())\
    \ <= z) inv.push_back(inv.back() * inv[1]);\n        Lf.resize(1 << z, 0);\n \
    \       Ls.resize(1 << z, 0);\n        Rf.resize(1 << z, 0);\n        Rs.resize(1\
    \ << z, 0);\n        atcoder::internal::butterfly(Lf);\n        atcoder::internal::butterfly(Ls);\n\
    \        atcoder::internal::butterfly(Rf);\n        atcoder::internal::butterfly(Rs);\n\
    \        std::vector<T> D(1 << z), U(1 << z);\n        for (int i = 0; i < (1\
    \ << z); i++){\n            D[i] = Ls[i] * Rs[i] * inv[z];\n            U[i] =\
    \ (Ls[i] * Rf[i] + Lf[i] * Rs[i]) * inv[z];\n        }\n        atcoder::internal::butterfly_inv(D);\n\
    \        atcoder::internal::butterfly_inv(U);\n        D.resize(r - l + 1);\n\
    \        U.resize(r - l);\n        return {U, D};\n    };\n    return rec(rec,\
    \ 0, N).first;\n}\n}\n"
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
    \ xt[i] = X[i];\n    auto Z = Multipoint_Evaluation(g, xt);\n    std::vector<T>\
    \ inv = {1, (T)(1) / (T)(2)};\n    auto rec = [&](auto self, int l, int r) ->\
    \ std::pair<std::vector<T>, std::vector<T>> {\n        if (l + 1 == r){\n    \
    \        return {{Y[l] / Z[l]}, {-X[l], 1}};\n        }\n        int m = (l +\
    \ r) / 2;\n        auto [Lf, Ls] = self(self, l, m);\n        auto [Rf, Rs] =\
    \ self(self, m, r);\n        int mx_size = r - l + 1;\n        if (mx_size < 128){\n\
    \            auto D = atcoder::convolution(Ls, Rs);\n            auto U = atcoder::convolution(Ls,\
    \ Rf);\n            FPS_add(U, atcoder::convolution(Lf, Rs));\n            return\
    \ {U, D};\n        }\n        int z = 0;\n        while ((1 << z) < mx_size) z++;\n\
    \        while (int(inv.size()) <= z) inv.push_back(inv.back() * inv[1]);\n  \
    \      Lf.resize(1 << z, 0);\n        Ls.resize(1 << z, 0);\n        Rf.resize(1\
    \ << z, 0);\n        Rs.resize(1 << z, 0);\n        atcoder::internal::butterfly(Lf);\n\
    \        atcoder::internal::butterfly(Ls);\n        atcoder::internal::butterfly(Rf);\n\
    \        atcoder::internal::butterfly(Rs);\n        std::vector<T> D(1 << z),\
    \ U(1 << z);\n        for (int i = 0; i < (1 << z); i++){\n            D[i] =\
    \ Ls[i] * Rs[i] * inv[z];\n            U[i] = (Ls[i] * Rf[i] + Lf[i] * Rs[i])\
    \ * inv[z];\n        }\n        atcoder::internal::butterfly_inv(D);\n       \
    \ atcoder::internal::butterfly_inv(U);\n        D.resize(r - l + 1);\n       \
    \ U.resize(r - l);\n        return {U, D};\n    };\n    return rec(rec, 0, N).first;\n\
    }\n}\n"
  dependsOn:
  - fps/FPS_Product_Sequence.hpp
  - fps/Multipoint_Evaluation.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_add.hpp
  isVerificationFile: false
  path: fps/Polynomial_Interpolation.hpp
  requiredBy: []
  timestamp: '2025-10-30 10:13:28+09:00'
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
