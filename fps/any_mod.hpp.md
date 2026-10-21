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
    links: []
  bundledCode: "#line 2 \"fps/any_mod.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n#include <atcoder/convolution>\n\nnamespace\
    \ po167 {\n\n// c[k] = sum_{i+j=k} a[i] * b[j] (mod pmod), 0 <= c[k] < pmod.\n\
    // 1 <= pmod, |a| + |b| - 1 <= 2^24 (unless an input is empty).\n// After normalization\
    \ to [0, pmod), each integer coefficient must be\n// < 754974721 * 167772161 *\
    \ 469762049.\n// This is automatic for pmod <= 2^31 - 1 under the length bound\
    \ above.\ninline std::vector<long long> convolution_any_mod(\n    std::vector<long\
    \ long> a, std::vector<long long> b, long long pmod) {\n    assert(pmod >= 1);\n\
    \    if (a.empty() || b.empty()) return {};\n    assert(a.size() + b.size() -\
    \ 1 <= (1 << 24));\n    int n = (int)a.size(), m = (int)b.size(), s = n + m -\
    \ 1;\n    if (pmod == 1) return std::vector<long long>(s);\n\n    constexpr long\
    \ long m0 = 754974721, m1 = 167772161, m2 = 469762049;\n    if (pmod == m0) return\
    \ atcoder::convolution<m0>(a, b);\n    if (pmod == m1) return atcoder::convolution<m1>(a,\
    \ b);\n    if (pmod == m2) return atcoder::convolution<m2>(a, b);\n    if (pmod\
    \ == 998244353 && s <= (1 << 23))\n        return atcoder::convolution<998244353>(a,\
    \ b);\n\n    for (auto &x : a) if (x < 0 || x >= pmod) {\n        x %= pmod;\n\
    \        if (x < 0) x += pmod;\n    }\n    for (auto &x : b) if (x < 0 || x >=\
    \ pmod) {\n        x %= pmod;\n        if (x < 0) x += pmod;\n    }\n    if (std::min(n,\
    \ m) <= 256) {\n        std::vector<long long> c(s);\n        for (int k = 0;\
    \ k < s; ++k) {\n            __int128 sum = 0;\n            for (int i = std::max(0,\
    \ k - m + 1); i < std::min(n, k + 1); ++i)\n                sum += (__int128)a[i]\
    \ * b[k - i];\n            c[k] = (long long)(sum % pmod);\n        }\n      \
    \  return c;\n    }\n\n    auto conv = [&](auto zero) {\n        using mint =\
    \ decltype(zero);\n        return atcoder::convolution(std::vector<mint>(a.begin(),\
    \ a.end()),\n                                    std::vector<mint>(b.begin(),\
    \ b.end()));\n    };\n    auto c0 = conv(atcoder::static_modint<m0>());\n    auto\
    \ c1 = conv(atcoder::static_modint<m1>());\n    auto c2 = conv(atcoder::static_modint<m2>());\n\
    \    std::vector<long long> c(s);\n    long long m01 = m0 * m1 % pmod;\n    //\
    \ 95869806 = m0^(-1) mod m1, 187290749 = (m0*m1)^(-1) mod m2.\n    for (int i\
    \ = 0; i < s; ++i) {\n        long long x = (c1[i].val() - (long long)c0[i].val())\
    \ * 95869806 % m1;\n        if (x < 0) x += m1;\n        x = c0[i].val() + m0\
    \ * x;\n        long long y = (c2[i].val() - x % m2) * 187290749 % m2;\n     \
    \   if (y < 0) y += m2;\n        c[i] = pmod <= 2147483647\n            ? (x +\
    \ m01 * y) % pmod\n            : (long long)((x + (__int128)m01 * y) % pmod);\n\
    \    }\n    return c;\n}\n\ntemplate<class T>\nstd::vector<T> convolution_mint(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n    if (a.empty() || b.empty())\
    \ return {};\n    std::vector<long long> A(a.size()), B(b.size());\n    for (int\
    \ i = 0; i < (int)a.size(); ++i) A[i] = a[i].val();\n    for (int i = 0; i < (int)b.size();\
    \ ++i) B[i] = b[i].val();\n    auto c = convolution_any_mod(std::move(A), std::move(B),\
    \ T::mod());\n    return std::vector<T>(c.begin(), c.end());\n}\n\n} // namespace\
    \ po167\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n#include <atcoder/convolution>\n\nnamespace po167 {\n\n// c[k]\
    \ = sum_{i+j=k} a[i] * b[j] (mod pmod), 0 <= c[k] < pmod.\n// 1 <= pmod, |a| +\
    \ |b| - 1 <= 2^24 (unless an input is empty).\n// After normalization to [0, pmod),\
    \ each integer coefficient must be\n// < 754974721 * 167772161 * 469762049.\n\
    // This is automatic for pmod <= 2^31 - 1 under the length bound above.\ninline\
    \ std::vector<long long> convolution_any_mod(\n    std::vector<long long> a, std::vector<long\
    \ long> b, long long pmod) {\n    assert(pmod >= 1);\n    if (a.empty() || b.empty())\
    \ return {};\n    assert(a.size() + b.size() - 1 <= (1 << 24));\n    int n = (int)a.size(),\
    \ m = (int)b.size(), s = n + m - 1;\n    if (pmod == 1) return std::vector<long\
    \ long>(s);\n\n    constexpr long long m0 = 754974721, m1 = 167772161, m2 = 469762049;\n\
    \    if (pmod == m0) return atcoder::convolution<m0>(a, b);\n    if (pmod == m1)\
    \ return atcoder::convolution<m1>(a, b);\n    if (pmod == m2) return atcoder::convolution<m2>(a,\
    \ b);\n    if (pmod == 998244353 && s <= (1 << 23))\n        return atcoder::convolution<998244353>(a,\
    \ b);\n\n    for (auto &x : a) if (x < 0 || x >= pmod) {\n        x %= pmod;\n\
    \        if (x < 0) x += pmod;\n    }\n    for (auto &x : b) if (x < 0 || x >=\
    \ pmod) {\n        x %= pmod;\n        if (x < 0) x += pmod;\n    }\n    if (std::min(n,\
    \ m) <= 256) {\n        std::vector<long long> c(s);\n        for (int k = 0;\
    \ k < s; ++k) {\n            __int128 sum = 0;\n            for (int i = std::max(0,\
    \ k - m + 1); i < std::min(n, k + 1); ++i)\n                sum += (__int128)a[i]\
    \ * b[k - i];\n            c[k] = (long long)(sum % pmod);\n        }\n      \
    \  return c;\n    }\n\n    auto conv = [&](auto zero) {\n        using mint =\
    \ decltype(zero);\n        return atcoder::convolution(std::vector<mint>(a.begin(),\
    \ a.end()),\n                                    std::vector<mint>(b.begin(),\
    \ b.end()));\n    };\n    auto c0 = conv(atcoder::static_modint<m0>());\n    auto\
    \ c1 = conv(atcoder::static_modint<m1>());\n    auto c2 = conv(atcoder::static_modint<m2>());\n\
    \    std::vector<long long> c(s);\n    long long m01 = m0 * m1 % pmod;\n    //\
    \ 95869806 = m0^(-1) mod m1, 187290749 = (m0*m1)^(-1) mod m2.\n    for (int i\
    \ = 0; i < s; ++i) {\n        long long x = (c1[i].val() - (long long)c0[i].val())\
    \ * 95869806 % m1;\n        if (x < 0) x += m1;\n        x = c0[i].val() + m0\
    \ * x;\n        long long y = (c2[i].val() - x % m2) * 187290749 % m2;\n     \
    \   if (y < 0) y += m2;\n        c[i] = pmod <= 2147483647\n            ? (x +\
    \ m01 * y) % pmod\n            : (long long)((x + (__int128)m01 * y) % pmod);\n\
    \    }\n    return c;\n}\n\ntemplate<class T>\nstd::vector<T> convolution_mint(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n    if (a.empty() || b.empty())\
    \ return {};\n    std::vector<long long> A(a.size()), B(b.size());\n    for (int\
    \ i = 0; i < (int)a.size(); ++i) A[i] = a[i].val();\n    for (int i = 0; i < (int)b.size();\
    \ ++i) B[i] = b[i].val();\n    auto c = convolution_any_mod(std::move(A), std::move(B),\
    \ T::mod());\n    return std::vector<T>(c.begin(), c.end());\n}\n\n} // namespace\
    \ po167"
  dependsOn: []
  isVerificationFile: false
  path: fps/any_mod.hpp
  requiredBy: []
  timestamp: '2026-10-21 22:37:29+09:00'
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
