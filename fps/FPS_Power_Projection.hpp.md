---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_pick_even_odd.hpp
    title: fps/FPS_pick_even_odd.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp_inverse.test.cpp
    title: test/fps/comp_inverse.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_Power_Projection.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n#include <atcoder/convolution>\n\
    #line 3 \"fps/FPS_pick_even_odd.hpp\"\n\nnamespace po167{\n// s.t |v| = 2 ^ s\
    \ (no assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T> &v, int\
    \ odd){\n    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n    if (odd\
    \ == 0){\n        for (int i = 0; i < z; i++){\n            v[i] = (v[i * 2] +\
    \ v[i * 2 + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n     \
    \   T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n\
    \        while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}\n#line\
    \ 8 \"fps/FPS_Power_Projection.hpp\"\n\nnamespace po167 {\n// Return [x^(g.size()-1)]\
    \ g(x)f(x)^i for 0 <= i < m.\ntemplate<class T>\nstd::vector<T> Power_Projection(std::vector<T>\
    \ g, std::vector<T> f, int m) {\n    assert(m >= 0);\n    if (m == 0) return {};\n\
    \    assert(!g.empty() && !f.empty() && f[0] == 0);\n    const int len = static_cast<int>(g.size()),\
    \ need = std::min(m, len);\n    std::vector<T> ans(m);\n    if (need <= 32) {\n\
    \        int b = 1;\n        while (b * b < need) ++b;\n        std::vector<std::vector<T>>\
    \ power(std::min(b, need - 1) + 1);\n        f.resize(std::min(len, static_cast<int>(f.size())));\n\
    \        if (need > 1) power[1] = std::move(f);\n        for (int i = 2; i < static_cast<int>(power.size());\
    \ ++i) {\n            power[i] = atcoder::convolution(power[i - 1], power[1]);\n\
    \            if (static_cast<int>(power[i].size()) > len) power[i].resize(len);\n\
    \        }\n        for (int j = 0; j < need; j += b) {\n            ans[j] =\
    \ g.back();\n            for (int i = 1; i < b && j + i < need; ++i)\n       \
    \         for (int t = 0; t < static_cast<int>(power[i].size()); ++t)\n      \
    \              ans[j + i] += g[len - 1 - t] * power[i][t];\n            if (j\
    \ + b < need) {\n                g = atcoder::convolution(g, power[b]);\n    \
    \            g.resize(len);\n            }\n        }\n        return ans;\n \
    \   }\n    int k = 1, d = 1, cap = 1, ind = len - 1;\n    while (k < len) k *=\
    \ 2;\n    while (cap < need) cap *= 2;\n    g.resize(k); f.resize(k);\n    for\
    \ (T& x : f) x = -x;\n    std::vector<T> a, b, e;\n    assert((T::mod() - 1) %\
    \ (2 * k) == 0);\n    std::vector<T> weight(2 * k);\n    for (int i = 0; i < k;\
    \ ++i) weight[2 * i] = 1;\n    po167::FPS_pick_even_odd(weight, 1);\n    T q =\
    \ 1;\n    while (k > 1) {\n        const int dy = d == 1 ? 1 : 2 * d, h = k /\
    \ 2, nd = std::min(2 * d, cap);\n        g.resize(k * dy); f.resize(k * dy);\n\
    \        // Retain the old y-NTT values and append the missing half.\n       \
    \ if (d > 1) {\n            e.resize(d); e[0] = T(d).inv();\n            const\
    \ T root = T(atcoder::internal::primitive_root_constexpr(T::mod())).pow((T::mod()\
    \ - 1) / dy);\n            for (int i = 1; i < d; ++i) e[i] = e[i - 1] * root;\n\
    \            for (int j = k - 1; j >= 0; --j) for (int t = 0; t < 2; ++t) {\n\
    \                if (t && !j) continue;\n                auto& v = t ? f : g;\n\
    \                a.assign(v.begin() + j * d, v.begin() + (j + 1) * d);\n     \
    \           atcoder::internal::butterfly_inv(a);\n                if (t) a[0]\
    \ = -a[0]; // Q stores its y^d term at index 0.\n                for (int i =\
    \ 0; i < d; ++i) a[i] *= e[i];\n                atcoder::internal::butterfly(a);\n\
    \                if (j) std::copy_n(v.begin() + j * d, d, v.begin() + j * dy);\n\
    \                std::copy_n(a.begin(), d, v.begin() + j * dy + d);\n        \
    \    }\n        }\n        if (k == 2) {\n            for (int i = 0; i < dy;\
    \ ++i) g[i] = g[dy + i] * q - g[i] * f[dy + i];\n            q *= q; d = dy;\n\
    \            break;\n        }\n        a.clear(); b.clear();\n        for (int\
    \ i = 0; i < dy; ++i) {\n            a.resize(2 * k); b.resize(2 * k);\n     \
    \       for (int j = 0; j < k; ++j) { a[j] = g[j * dy + i]; b[j] = j || d == 1\
    \ ? f[j * dy + i] : q; }\n            atcoder::internal::butterfly(a);\n     \
    \       atcoder::internal::butterfly(b);\n            for (int j = 0; j < k; ++j)\
    \ {\n                const T x = b[2 * j], y = b[2 * j + 1];\n               \
    \ const auto u = 1ULL * a[2 * j].val() * y.val();\n                const auto\
    \ v = 1ULL * a[2 * j + 1].val() * x.val();\n                const auto z = (u\
    \ + ((ind & 1) ? 1ULL * T::mod() * T::mod() - v : v)) % T::mod();\n          \
    \      a[j] = ind & 1 ? T::raw(z) * weight[j] : T::raw((z + (z & 1) * T::mod())\
    \ >> 1);\n                b[j] = x * y;\n            }\n            a.resize(k);\
    \ b.resize(k);\n            atcoder::internal::butterfly_inv(a);\n           \
    \ atcoder::internal::butterfly_inv(b);\n            if (d == 1) for (int j = 0;\
    \ j < h; ++j) {\n                const T x = T(k) * g[2 * j + (ind & 1)], y =\
    \ T(2 * k) * f[2 * j];\n                g[2 * j] = x + a[j]; g[2 * j + 1] = x\
    \ - a[j];\n                f[2 * j] = b[j] + y; f[2 * j + 1] = b[j] - y;\n   \
    \         }\n            else for (int j = 0; j < h; ++j) { g[j * dy + i] = a[j];\
    \ if (j) f[j * dy + i] = b[j]; }\n        }\n        q *= T(k) * q;\n        if\
    \ (nd < dy) {\n            for (int j = 0; j < h; ++j) {\n                a.assign(g.begin()\
    \ + j * dy, g.begin() + (j + 1) * dy);\n                atcoder::internal::butterfly_inv(a);\n\
    \                a.resize(nd); atcoder::internal::butterfly(a);\n            \
    \    std::copy_n(a.begin(), nd, g.begin() + j * nd);\n                if (j) {\n\
    \                    b.assign(f.begin() + j * dy, f.begin() + (j + 1) * dy);\n\
    \                    atcoder::internal::butterfly_inv(b);\n                  \
    \  b[0] = b[nd]; b.resize(nd); atcoder::internal::butterfly(b);\n            \
    \        std::copy_n(b.begin(), nd, f.begin() + j * nd);\n                }\n\
    \            }\n            q *= dy;\n        }\n        k = h; d = nd; ind /=\
    \ 2;\n    }\n    g.resize(d);\n    atcoder::internal::butterfly_inv(g);\n    const\
    \ T iq = (q * d).inv();\n    for (int i = 0; i < need; ++i) ans[i] = g[i] * iq;\n\
    \    return ans;\n}\n} // namespace po167\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n#include <atcoder/convolution>\n#include \"../fps/FPS_pick_even_odd.hpp\"\
    \n\nnamespace po167 {\n// Return [x^(g.size()-1)] g(x)f(x)^i for 0 <= i < m.\n\
    template<class T>\nstd::vector<T> Power_Projection(std::vector<T> g, std::vector<T>\
    \ f, int m) {\n    assert(m >= 0);\n    if (m == 0) return {};\n    assert(!g.empty()\
    \ && !f.empty() && f[0] == 0);\n    const int len = static_cast<int>(g.size()),\
    \ need = std::min(m, len);\n    std::vector<T> ans(m);\n    if (need <= 32) {\n\
    \        int b = 1;\n        while (b * b < need) ++b;\n        std::vector<std::vector<T>>\
    \ power(std::min(b, need - 1) + 1);\n        f.resize(std::min(len, static_cast<int>(f.size())));\n\
    \        if (need > 1) power[1] = std::move(f);\n        for (int i = 2; i < static_cast<int>(power.size());\
    \ ++i) {\n            power[i] = atcoder::convolution(power[i - 1], power[1]);\n\
    \            if (static_cast<int>(power[i].size()) > len) power[i].resize(len);\n\
    \        }\n        for (int j = 0; j < need; j += b) {\n            ans[j] =\
    \ g.back();\n            for (int i = 1; i < b && j + i < need; ++i)\n       \
    \         for (int t = 0; t < static_cast<int>(power[i].size()); ++t)\n      \
    \              ans[j + i] += g[len - 1 - t] * power[i][t];\n            if (j\
    \ + b < need) {\n                g = atcoder::convolution(g, power[b]);\n    \
    \            g.resize(len);\n            }\n        }\n        return ans;\n \
    \   }\n    int k = 1, d = 1, cap = 1, ind = len - 1;\n    while (k < len) k *=\
    \ 2;\n    while (cap < need) cap *= 2;\n    g.resize(k); f.resize(k);\n    for\
    \ (T& x : f) x = -x;\n    std::vector<T> a, b, e;\n    assert((T::mod() - 1) %\
    \ (2 * k) == 0);\n    std::vector<T> weight(2 * k);\n    for (int i = 0; i < k;\
    \ ++i) weight[2 * i] = 1;\n    po167::FPS_pick_even_odd(weight, 1);\n    T q =\
    \ 1;\n    while (k > 1) {\n        const int dy = d == 1 ? 1 : 2 * d, h = k /\
    \ 2, nd = std::min(2 * d, cap);\n        g.resize(k * dy); f.resize(k * dy);\n\
    \        // Retain the old y-NTT values and append the missing half.\n       \
    \ if (d > 1) {\n            e.resize(d); e[0] = T(d).inv();\n            const\
    \ T root = T(atcoder::internal::primitive_root_constexpr(T::mod())).pow((T::mod()\
    \ - 1) / dy);\n            for (int i = 1; i < d; ++i) e[i] = e[i - 1] * root;\n\
    \            for (int j = k - 1; j >= 0; --j) for (int t = 0; t < 2; ++t) {\n\
    \                if (t && !j) continue;\n                auto& v = t ? f : g;\n\
    \                a.assign(v.begin() + j * d, v.begin() + (j + 1) * d);\n     \
    \           atcoder::internal::butterfly_inv(a);\n                if (t) a[0]\
    \ = -a[0]; // Q stores its y^d term at index 0.\n                for (int i =\
    \ 0; i < d; ++i) a[i] *= e[i];\n                atcoder::internal::butterfly(a);\n\
    \                if (j) std::copy_n(v.begin() + j * d, d, v.begin() + j * dy);\n\
    \                std::copy_n(a.begin(), d, v.begin() + j * dy + d);\n        \
    \    }\n        }\n        if (k == 2) {\n            for (int i = 0; i < dy;\
    \ ++i) g[i] = g[dy + i] * q - g[i] * f[dy + i];\n            q *= q; d = dy;\n\
    \            break;\n        }\n        a.clear(); b.clear();\n        for (int\
    \ i = 0; i < dy; ++i) {\n            a.resize(2 * k); b.resize(2 * k);\n     \
    \       for (int j = 0; j < k; ++j) { a[j] = g[j * dy + i]; b[j] = j || d == 1\
    \ ? f[j * dy + i] : q; }\n            atcoder::internal::butterfly(a);\n     \
    \       atcoder::internal::butterfly(b);\n            for (int j = 0; j < k; ++j)\
    \ {\n                const T x = b[2 * j], y = b[2 * j + 1];\n               \
    \ const auto u = 1ULL * a[2 * j].val() * y.val();\n                const auto\
    \ v = 1ULL * a[2 * j + 1].val() * x.val();\n                const auto z = (u\
    \ + ((ind & 1) ? 1ULL * T::mod() * T::mod() - v : v)) % T::mod();\n          \
    \      a[j] = ind & 1 ? T::raw(z) * weight[j] : T::raw((z + (z & 1) * T::mod())\
    \ >> 1);\n                b[j] = x * y;\n            }\n            a.resize(k);\
    \ b.resize(k);\n            atcoder::internal::butterfly_inv(a);\n           \
    \ atcoder::internal::butterfly_inv(b);\n            if (d == 1) for (int j = 0;\
    \ j < h; ++j) {\n                const T x = T(k) * g[2 * j + (ind & 1)], y =\
    \ T(2 * k) * f[2 * j];\n                g[2 * j] = x + a[j]; g[2 * j + 1] = x\
    \ - a[j];\n                f[2 * j] = b[j] + y; f[2 * j + 1] = b[j] - y;\n   \
    \         }\n            else for (int j = 0; j < h; ++j) { g[j * dy + i] = a[j];\
    \ if (j) f[j * dy + i] = b[j]; }\n        }\n        q *= T(k) * q;\n        if\
    \ (nd < dy) {\n            for (int j = 0; j < h; ++j) {\n                a.assign(g.begin()\
    \ + j * dy, g.begin() + (j + 1) * dy);\n                atcoder::internal::butterfly_inv(a);\n\
    \                a.resize(nd); atcoder::internal::butterfly(a);\n            \
    \    std::copy_n(a.begin(), nd, g.begin() + j * nd);\n                if (j) {\n\
    \                    b.assign(f.begin() + j * dy, f.begin() + (j + 1) * dy);\n\
    \                    atcoder::internal::butterfly_inv(b);\n                  \
    \  b[0] = b[nd]; b.resize(nd); atcoder::internal::butterfly(b);\n            \
    \        std::copy_n(b.begin(), nd, f.begin() + j * nd);\n                }\n\
    \            }\n            q *= dy;\n        }\n        k = h; d = nd; ind /=\
    \ 2;\n    }\n    g.resize(d);\n    atcoder::internal::butterfly_inv(g);\n    const\
    \ T iq = (q * d).inv();\n    for (int i = 0; i < need; ++i) ans[i] = g[i] * iq;\n\
    \    return ans;\n}\n} // namespace po167"
  dependsOn:
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: false
  path: fps/FPS_Power_Projection.hpp
  requiredBy:
  - fps/FPS_inverse.hpp
  timestamp: '2026-10-21 22:04:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/comp_inverse.test.cpp
documentation_of: fps/FPS_Power_Projection.hpp
layout: document
redirect_from:
- /library/fps/FPS_Power_Projection.hpp
- /library/fps/FPS_Power_Projection.hpp.html
title: fps/FPS_Power_Projection.hpp
---
