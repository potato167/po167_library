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
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_log.hpp
    title: fps/FPS_log.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_pick_even_odd.hpp
    title: fps/FPS_pick_even_odd.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large
    links:
    - https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large
  bundledCode: "#line 1 \"test/fps/comp_inverse.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large\"\
    \n\n\n#line 2 \"fps/FPS_inverse.hpp\"\n#include <vector>\n#line 3 \"fps/FPS_exp.hpp\"\
    \n#include <atcoder/convolution>\n#line 4 \"fps/FPS_cyclic_convolution.hpp\"\n\
    \nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 3 \"fps/FPS_differetial.hpp\"\n\nnamespace\
    \ po167{\ntemplate <class T>\nstd::vector<T> FPS_differential(std::vector<T> f){\n\
    \    if (f.empty()) return f;\n    for (int i = 0; i < (int)f.size() - 1; i++){\n\
    \        f[i] = f[i + 1] * (T)(i + 1);\n    }\n    f.pop_back();\n    return f;\n\
    }\n}\n#line 3 \"fps/FPS_integral.hpp\"\n\nnamespace po167{\ntemplate <class T>\n\
    std::vector<T> FPS_integral(std::vector<T> f){\n    if (f.empty()) return f;\n\
    \    std::vector<T> num_inv((int)f.size() + 1);\n    num_inv[0] = 1;\n    num_inv[1]\
    \ = 1;\n    auto m = T::mod();\n    for (int i = 2; i <= (int)f.size(); i++){\n\
    \        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);\n    }\n    f.reserve((int)f.size()\
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
    \    }\n    g.resize(len);\n    return g;\n}\n}\n#line 5 \"fps/FPS_log.hpp\"\n\
    \nnamespace po167{\ntemplate<class T>\nstd::vector<T> FPS_log(std::vector<T> f,\
    \ int len = -1){\n    if (len == -1) len = f.size();\n    if (len == 0) return\
    \ {};\n    if (len == 1) return {T(0)};\n    assert(!f.empty() && f[0] == 1);\n\
    \    std::vector<T> res = atcoder::convolution(FPS_differential(f), FPS_inv(f,\
    \ len));\n    res.resize(len - 1);\n    return FPS_integral(res);\n}\n}\n#line\
    \ 4 \"fps/FPS_Power_Projection.hpp\"\n\n#line 3 \"fps/FPS_pick_even_odd.hpp\"\n\
    \nnamespace po167{\n// s.t |v| = 2 ^ s (no assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T>\
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
    \ 7 \"fps/FPS_Power_Projection.hpp\"\n\nnamespace po167{\n// n = |g|\n// return\
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
    \ ans;\n}\n}\n#line 6 \"fps/FPS_inverse.hpp\"\n\nnamespace po167{\n// return g\n\
    // g(f) = x\n// [x ^ 0] f  = 0\n// [x ^ 1] f != 0\ntemplate<class T>\nstd::vector<T>\
    \ FPS_inverse(std::vector<T> f, int len = -1){\n    if (len == -1) len = f.size();\n\
    \    if (len == 0) return {};\n    if (len == 1) return {(T)(0)};\n    assert((int)f.size()\
    \ >= 2);\n    assert(f[0] == 0);\n    assert(f[1] != 0);\n    T c = (T)(1) / f[1];\n\
    \    for (auto &x : f) x *= c;\n    std::vector<T> inv_num(len + 1, 1);\n    for\
    \ (int i = 2; i <= len; i++){\n        inv_num[i] = (0 - inv_num[T::mod() % i])\
    \ * (T::mod() / i);\n    }\n    f.resize(len);\n    std::vector<T> p(len);\n \
    \   p[0] = 1;\n    p = Power_Projection(p, f, len);\n    std::vector<T> g(len\
    \ - 1);\n    for (int i = 1; i < len; i++){\n        g[len - 1 - i] = p[i] * (T)(len\
    \ - 1) * inv_num[i];\n    }\n    g = FPS_log(g);\n    for (int i = 0; i < len\
    \ - 1; i++){\n        g[i] *= (T)(-1) * inv_num[len - 1];\n    }\n    g = FPS_exp(g);\n\
    \    g.insert(g.begin(), 0);\n    T v = 1;\n    for (auto &x : g) x *= v, v *=\
    \ c;\n    return g;\n}\n\n}\n#line 5 \"test/fps/comp_inverse.test.cpp\"\n\n#include\
    \ <atcoder/modint>\n#include <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = atcoder::modint998244353;\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<mint> a(n);\n    for (int i = 0; i <\
    \ n; i++){\n        int mem;\n        std::cin >> mem;\n        a[i] = mem;\n\
    \    }\n    auto b = po167::FPS_inverse(a);\n    for (int i = 0; i < n; i++){\n\
    \        std::cout << b[i].val() << (i + 1 == n ? \"\\n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large\"\
    \n\n\n#include \"../../fps/FPS_inverse.hpp\"\n\n#include <atcoder/modint>\n#include\
    \ <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = atcoder::modint998244353;\n    int n;\n    std::cin >> n;\n\
    \    std::vector<mint> a(n);\n    for (int i = 0; i < n; i++){\n        int mem;\n\
    \        std::cin >> mem;\n        a[i] = mem;\n    }\n    auto b = po167::FPS_inverse(a);\n\
    \    for (int i = 0; i < n; i++){\n        std::cout << b[i].val() << (i + 1 ==\
    \ n ? \"\\n\" : \" \");\n    }\n}"
  dependsOn:
  - fps/FPS_inverse.hpp
  - fps/FPS_exp.hpp
  - fps/FPS_cyclic_convolution.hpp
  - fps/FPS_differetial.hpp
  - fps/FPS_integral.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_log.hpp
  - fps/FPS_Power_Projection.hpp
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: true
  path: test/fps/comp_inverse.test.cpp
  requiredBy: []
  timestamp: '2024-07-15 01:10:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/comp_inverse.test.cpp
layout: document
redirect_from:
- /verify/test/fps/comp_inverse.test.cpp
- /verify/test/fps/comp_inverse.test.cpp.html
title: test/fps/comp_inverse.test.cpp
---
