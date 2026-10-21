---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Power_Projection.hpp
    title: fps/FPS_Power_Projection.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_differetial.hpp
    title: fps/FPS_differetial.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_exp.hpp
    title: fps/FPS_exp.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_integral.hpp
    title: fps/FPS_integral.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_log.hpp
    title: fps/FPS_log.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_pick_even_odd.hpp
    title: fps/FPS_pick_even_odd.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp_inverse.test.cpp
    title: test/fps/comp_inverse.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_inverse.hpp\"\n#include <vector>\n#line 3 \"fps/FPS_exp.hpp\"\
    \n#include <atcoder/convolution>\n#line 4 \"fps/FPS_cyclic_convolution.hpp\"\n\
    \nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 3 \"fps/FPS_differetial.hpp\"\n\nnamespace\
    \ po167{\n// return f'\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T>\
    \ f){\n    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1;\
    \ i++){\n        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n   \
    \ return f;\n}\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate\
    \ <class T>\nstd::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty())\
    \ return f;\n    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] =\
    \ 1;\n    num_inv[1] = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size();\
    \ i++){\n        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
    \ + 1);\n    f.push_back(0);\n    for (int i = (int)f.size() - 1; i > 0; i--){\n\
    \        f[i] = f[i - 1] * num_inv[i];\n    }\n    f[0] = 0;\n    return f;\n\
    }\n}\n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate\
    \ <class T>\nstd::vector<T> FPS_inv(std::vector<T> f, int len = -1){\n    if (len\
    \ == -1) len = f.size();\n    assert(f[0] != 0);\n    std::vector<T> g = {1 /\
    \ f[0]};\n    int s = 1;\n    while(s < len){\n        // g = 2g_s - f(g_s)^2\
    \ (mod x ^ (2 * s))\n        // g = g - (fg - 1)g\n        // (fg - 1) = 0 (mod\
    \ x ^ (s))\n        std::vector<T> n_g(s * 2, 0);\n        std::vector<T> f_s(s\
    \ * 2, 0);\n        g.resize(s * 2);\n        for (int i = 0; i < s * 2; i++){\n\
    \            if (int(f.size()) > i) f_s[i] = f[i];\n            n_g[i] = g[i];\n\
    \        }\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        T iz = 1 / (T)(s\
    \ * 2);\n        for (int i = s; i < s * 2; i++){\n            f_s[i] *= iz;\n\
    \        }\n        for (int i = 0; i < s; i++){\n            f_s[i] = 0;\n  \
    \      }\n        atcoder::internal::butterfly(f_s);\n        for (int i = 0;\
    \ i < s * 2; i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        for (int i = s; i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n\
    \        }\n        std::swap(n_g, g);\n        s *= 2;\n    }\n    g.resize(len);\n\
    \    return g;\n}\n}\n#line 8 \"fps/FPS_exp.hpp\"\n\nnamespace po167{\ntemplate<class\
    \ T>\nstd::vector<T> FPS_exp(std::vector<T> f, int len = -1){\n    if (len ==\
    \ -1) len = f.size();\n    if (len == 0) return {};\n    if (len == 1) return\
    \ {T(1)};\n    assert(!f.empty() && f[0] == 0);\n    int s = 1;\n    // simple\n\
    \    std::vector<T> g = {T(1)};\n    while (s < len){\n        // g' / g\n   \
    \     // A * B\n        std::vector<T> A = g, B = g;\n        A = FPS_differential(A);\n\
    \        B = FPS_inv(B, 2 * s);\n        A.resize(2 * s);\n        A = FPS_cyclic_convolution(A,\
    \ B);\n        A.pop_back();\n        A = FPS_integral(A);\n        for (int i\
    \ = 0; i < s; i++) A[i] = 0;\n        for (int i = s; i < s * 2; i++) A[i] = (i\
    \ < (int)f.size() ? f[i] : 0) - A[i];\n        // g_hat = g (1 - g + f)\n    \
    \    // g += B = g * A\n        g.resize(2 * s);\n        B = FPS_cyclic_convolution(A,\
    \ g);\n        for (int i = s; i < s * 2; i++) g[i] = B[i];\n        s *= 2;\n\
    \    }\n    g.resize(len);\n    return g;\n}\n}\n#line 6 \"fps/FPS_log.hpp\"\n\
    \nnamespace po167{\ntemplate<class T>\nstd::vector<T> FPS_log(std::vector<T> f,\
    \ int len = -1){\n    if (len == -1) len = f.size();\n    if (len == 0) return\
    \ {};\n    if (len == 1) return {T(0)};\n    assert(!f.empty() && f[0] == 1);\n\
    \    std::vector<T> res = atcoder::convolution(FPS_differential(f), FPS_inv(f,\
    \ len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n}\n}\n#line\
    \ 2 \"fps/FPS_Power_Projection.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <utility>\n#line 3 \"fps/FPS_pick_even_odd.hpp\"\n\nnamespace po167{\n\
    // s.t |v| = 2 ^ s (no assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T>\
    \ &v, int odd){\n    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n  \
    \  if (odd == 0){\n        for (int i = 0; i < z; i++){\n            v[i] = (v[i\
    \ * 2] + v[i * 2 + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n\
    \        T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
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
    \    return ans;\n}\n} // namespace po167\n#line 6 \"fps/FPS_inverse.hpp\"\n\n\
    namespace po167{\n// return g\n// g(f) = x\n// [x ^ 0] f  = 0\n// [x ^ 1] f !=\
    \ 0\ntemplate<class T>\nstd::vector<T> FPS_inverse(std::vector<T> f, int len =\
    \ -1){\n    if (len == -1) len = f.size();\n    if (len == 0) return {};\n   \
    \ if (len == 1) return {(T)(0)};\n    assert((int)f.size() >= 2);\n    assert(f[0]\
    \ == 0);\n    assert(f[1] != 0);\n    T c = (T)(1) / f[1];\n    for (auto &x :\
    \ f) x *= c;\n    std::vector<T> inv_num(len + 1, 1);\n    for (int i = 2; i <=\
    \ len; i++){\n        inv_num[i] = (0 - inv_num[T::mod() % i]) * (T::mod() / i);\n\
    \    }\n    f.resize(len);\n    std::vector<T> p(len);\n    p[0] = 1;\n    p =\
    \ Power_Projection(p, f, len);\n    std::vector<T> g(len - 1);\n    for (int i\
    \ = 1; i < len; i++){\n        g[len - 1 - i] = p[i] * (T)(len - 1) * inv_num[i];\n\
    \    }\n    g = FPS_log(g);\n    for (int i = 0; i < len - 1; i++){\n        g[i]\
    \ *= (T)(-1) * inv_num[len - 1];\n    }\n    g = FPS_exp(g);\n    g.insert(g.begin(),\
    \ 0);\n    T v = 1;\n    for (auto &x : g) x *= v, v *= c;\n    return g;\n}\n\
    \n}\n"
  code: "#pragma once\n#include <vector>\n#include \"../fps/FPS_exp.hpp\"\n#include\
    \ \"../fps/FPS_log.hpp\"\n#include \"../fps/FPS_Power_Projection.hpp\"\n\nnamespace\
    \ po167{\n// return g\n// g(f) = x\n// [x ^ 0] f  = 0\n// [x ^ 1] f != 0\ntemplate<class\
    \ T>\nstd::vector<T> FPS_inverse(std::vector<T> f, int len = -1){\n    if (len\
    \ == -1) len = f.size();\n    if (len == 0) return {};\n    if (len == 1) return\
    \ {(T)(0)};\n    assert((int)f.size() >= 2);\n    assert(f[0] == 0);\n    assert(f[1]\
    \ != 0);\n    T c = (T)(1) / f[1];\n    for (auto &x : f) x *= c;\n    std::vector<T>\
    \ inv_num(len + 1, 1);\n    for (int i = 2; i <= len; i++){\n        inv_num[i]\
    \ = (0 - inv_num[T::mod() % i]) * (T::mod() / i);\n    }\n    f.resize(len);\n\
    \    std::vector<T> p(len);\n    p[0] = 1;\n    p = Power_Projection(p, f, len);\n\
    \    std::vector<T> g(len - 1);\n    for (int i = 1; i < len; i++){\n        g[len\
    \ - 1 - i] = p[i] * (T)(len - 1) * inv_num[i];\n    }\n    g = FPS_log(g);\n \
    \   for (int i = 0; i < len - 1; i++){\n        g[i] *= (T)(-1) * inv_num[len\
    \ - 1];\n    }\n    g = FPS_exp(g);\n    g.insert(g.begin(), 0);\n    T v = 1;\n\
    \    for (auto &x : g) x *= v, v *= c;\n    return g;\n}\n\n}"
  dependsOn:
  - fps/FPS_exp.hpp
  - fps/FPS_cyclic_convolution.hpp
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_log.hpp
  - fps/FPS_Power_Projection.hpp
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: false
  path: fps/FPS_inverse.hpp
  requiredBy: []
  timestamp: '2026-10-21 22:04:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/comp_inverse.test.cpp
documentation_of: fps/FPS_inverse.hpp
layout: document
redirect_from:
- /library/fps/FPS_inverse.hpp
- /library/fps/FPS_inverse.hpp.html
title: fps/FPS_inverse.hpp
---
