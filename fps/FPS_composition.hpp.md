---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp.test.cpp
    title: test/fps/comp.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://maspypy.github.io/library/poly/composition.hpp
  bundledCode: "#line 2 \"fps/FPS_composition.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n#include <atcoder/convolution>\n\
    \nnamespace po167 {\n\n// N = |g|, g[0] = 0.\n// return { [x^i] f(g(x)) : 0 <=\
    \ i < N }.\n// https://maspypy.github.io/library/poly/composition.hpp\ntemplate<class\
    \ T>\nstd::vector<T> FPS_comp(std::vector<T> f, std::vector<T> g) {\n    int N\
    \ = g.size(), size = 1;\n    if (!N) return {};\n    assert(g[0] == T(0));\n \
    \   if (f.empty()) return std::vector<T>(N);\n    if (N == 1) return {f[0]};\n\
    \    while (size < N) size *= 2;\n    assert((T::mod() - 1) % (2 * size) == 0);\n\
    \    f.resize(size);\n    g.resize(4 * size);\n    for (int i = 0; i < N; ++i)\
    \ g[i] = -g[i];\n\n    // Forward / inverse NTT, or its transpose.\n    auto fft\
    \ = [](std::vector<T>& a, bool inverse, bool transpose) {\n        if (inverse\
    \ && transpose) std::reverse(a.begin() + 1, a.end());\n        if (inverse !=\
    \ transpose) atcoder::internal::butterfly_inv(a);\n        else atcoder::internal::butterfly(a);\n\
    \        if (!inverse && transpose) std::reverse(a.begin() + 1, a.end());\n  \
    \      if (inverse) {\n            T scale = T(T::mod() - (T::mod() - 1) / int(a.size()));\n\
    \            for (auto &x : a) x *= scale;\n        }\n    };\n    std::vector<T>\
    \ W(size);\n    W[0] = 1;\n    static const atcoder::internal::fft_info<T> info;\n\
    \    for (int m = 1, h = 2; m < size; m *= 2, ++h) {\n        for (int i = 0;\
    \ i < m; ++i) W[m + i] = W[i] * info.iroot[h];\n    }\n\n    auto rec = [&](auto&&\
    \ self, int n, int k, std::vector<T> Q) -> std::vector<T> {\n        if (n ==\
    \ 1) {\n            std::reverse(f.begin(), f.end());\n            fft(f, true,\
    \ true);\n            T scale = T(1) / T(k);\n            std::vector<T> p(4 *\
    \ size);\n            for (int i = 0; i < k; ++i) p[2 * i] = f[i] * scale;\n \
    \           return p;\n        }\n        auto double_y = [&](std::vector<T>&\
    \ a, int l, int r, bool transpose) {\n            std::vector<T> v(k);\n     \
    \       T z = T(1) / W[k / 2];\n            for (int i = l; i < r; ++i) {\n  \
    \              for (int j = 0; j < k; ++j) v[j] = a[2 * n * (j + (transpose ?\
    \ k : 0)) + i];\n                fft(v, !transpose, transpose);\n            \
    \    T power = 1;\n                for (int j = 1; j < k; ++j) {\n           \
    \         power *= z;\n                    v[j] *= power;\n                }\n\
    \                fft(v, transpose, transpose);\n                for (int j = 0;\
    \ j < k; ++j) {\n                    if (transpose) a[2 * n * j + i] += v[j];\n\
    \                    else a[2 * n * (k + j) + i] = v[j];\n                }\n\
    \            }\n        };\n        auto fft_x = [&](std::vector<T>& a, int count,\
    \ bool transpose) {\n            std::vector<T> v(2 * n);\n            for (int\
    \ j = 0; j < count; ++j) {\n                std::copy_n(a.begin() + 2 * n * j,\
    \ 2 * n, v.begin());\n                fft(v, false, transpose);\n            \
    \    std::copy(v.begin(), v.end(), a.begin() + 2 * n * j);\n            }\n  \
    \      };\n        if (n <= k) {\n            double_y(Q, 1, n, false);\n    \
    \        fft_x(Q, 2 * k, false);\n        } else {\n            fft_x(Q, k, false);\n\
    \            double_y(Q, 0, 2 * n, false);\n        }\n        for (int i = 0;\
    \ i < 2 * size; ++i) Q[i] += 1;\n        for (int i = 2 * size; i < 4 * size;\
    \ ++i) Q[i] -= 1;\n\n        std::vector<T> next(4 * size), v(n);\n        for\
    \ (int j = 0; j < 2 * k; ++j) {\n            for (int i = 0; i < n; ++i) v[i]\
    \ = Q[2 * n * j + 2 * i] * Q[2 * n * j + 2 * i + 1];\n            fft(v, true,\
    \ false);\n            for (int i = 1; i < n / 2; ++i) next[n * j + i] = v[i];\n\
    \        }\n        auto p = self(self, n / 2, 2 * k, std::move(next));\n    \
    \    for (int j = 2 * k - 1; j >= 0; --j) {\n            std::copy_n(p.begin()\
    \ + n * j, n / 2, v.begin());\n            std::fill(v.begin() + n / 2, v.end(),\
    \ T(0));\n            fft(v, true, true);\n            for (int i = 0; i < n;\
    \ ++i) {\n                T x = v[i] * W[i];\n                p[2 * n * j + 2\
    \ * i] = Q[2 * n * j + 2 * i + 1] * x;\n                p[2 * n * j + 2 * i +\
    \ 1] = -Q[2 * n * j + 2 * i] * x;\n            }\n        }\n        if (n <=\
    \ k) {\n            fft_x(p, 2 * k, true);\n            double_y(p, 0, n, true);\n\
    \        } else {\n            double_y(p, 0, 2 * n, true);\n            fft_x(p,\
    \ k, true);\n        }\n        return p;\n    };\n    auto p = rec(rec, size,\
    \ 1, std::move(g));\n    p.resize(size);\n    std::reverse(p.begin(), p.end());\n\
    \    p.resize(N);\n    return p;\n}\n\n} // namespace po167\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n#include <atcoder/convolution>\n\nnamespace po167 {\n\n// N\
    \ = |g|, g[0] = 0.\n// return { [x^i] f(g(x)) : 0 <= i < N }.\n// https://maspypy.github.io/library/poly/composition.hpp\n\
    template<class T>\nstd::vector<T> FPS_comp(std::vector<T> f, std::vector<T> g)\
    \ {\n    int N = g.size(), size = 1;\n    if (!N) return {};\n    assert(g[0]\
    \ == T(0));\n    if (f.empty()) return std::vector<T>(N);\n    if (N == 1) return\
    \ {f[0]};\n    while (size < N) size *= 2;\n    assert((T::mod() - 1) % (2 * size)\
    \ == 0);\n    f.resize(size);\n    g.resize(4 * size);\n    for (int i = 0; i\
    \ < N; ++i) g[i] = -g[i];\n\n    // Forward / inverse NTT, or its transpose.\n\
    \    auto fft = [](std::vector<T>& a, bool inverse, bool transpose) {\n      \
    \  if (inverse && transpose) std::reverse(a.begin() + 1, a.end());\n        if\
    \ (inverse != transpose) atcoder::internal::butterfly_inv(a);\n        else atcoder::internal::butterfly(a);\n\
    \        if (!inverse && transpose) std::reverse(a.begin() + 1, a.end());\n  \
    \      if (inverse) {\n            T scale = T(T::mod() - (T::mod() - 1) / int(a.size()));\n\
    \            for (auto &x : a) x *= scale;\n        }\n    };\n    std::vector<T>\
    \ W(size);\n    W[0] = 1;\n    static const atcoder::internal::fft_info<T> info;\n\
    \    for (int m = 1, h = 2; m < size; m *= 2, ++h) {\n        for (int i = 0;\
    \ i < m; ++i) W[m + i] = W[i] * info.iroot[h];\n    }\n\n    auto rec = [&](auto&&\
    \ self, int n, int k, std::vector<T> Q) -> std::vector<T> {\n        if (n ==\
    \ 1) {\n            std::reverse(f.begin(), f.end());\n            fft(f, true,\
    \ true);\n            T scale = T(1) / T(k);\n            std::vector<T> p(4 *\
    \ size);\n            for (int i = 0; i < k; ++i) p[2 * i] = f[i] * scale;\n \
    \           return p;\n        }\n        auto double_y = [&](std::vector<T>&\
    \ a, int l, int r, bool transpose) {\n            std::vector<T> v(k);\n     \
    \       T z = T(1) / W[k / 2];\n            for (int i = l; i < r; ++i) {\n  \
    \              for (int j = 0; j < k; ++j) v[j] = a[2 * n * (j + (transpose ?\
    \ k : 0)) + i];\n                fft(v, !transpose, transpose);\n            \
    \    T power = 1;\n                for (int j = 1; j < k; ++j) {\n           \
    \         power *= z;\n                    v[j] *= power;\n                }\n\
    \                fft(v, transpose, transpose);\n                for (int j = 0;\
    \ j < k; ++j) {\n                    if (transpose) a[2 * n * j + i] += v[j];\n\
    \                    else a[2 * n * (k + j) + i] = v[j];\n                }\n\
    \            }\n        };\n        auto fft_x = [&](std::vector<T>& a, int count,\
    \ bool transpose) {\n            std::vector<T> v(2 * n);\n            for (int\
    \ j = 0; j < count; ++j) {\n                std::copy_n(a.begin() + 2 * n * j,\
    \ 2 * n, v.begin());\n                fft(v, false, transpose);\n            \
    \    std::copy(v.begin(), v.end(), a.begin() + 2 * n * j);\n            }\n  \
    \      };\n        if (n <= k) {\n            double_y(Q, 1, n, false);\n    \
    \        fft_x(Q, 2 * k, false);\n        } else {\n            fft_x(Q, k, false);\n\
    \            double_y(Q, 0, 2 * n, false);\n        }\n        for (int i = 0;\
    \ i < 2 * size; ++i) Q[i] += 1;\n        for (int i = 2 * size; i < 4 * size;\
    \ ++i) Q[i] -= 1;\n\n        std::vector<T> next(4 * size), v(n);\n        for\
    \ (int j = 0; j < 2 * k; ++j) {\n            for (int i = 0; i < n; ++i) v[i]\
    \ = Q[2 * n * j + 2 * i] * Q[2 * n * j + 2 * i + 1];\n            fft(v, true,\
    \ false);\n            for (int i = 1; i < n / 2; ++i) next[n * j + i] = v[i];\n\
    \        }\n        auto p = self(self, n / 2, 2 * k, std::move(next));\n    \
    \    for (int j = 2 * k - 1; j >= 0; --j) {\n            std::copy_n(p.begin()\
    \ + n * j, n / 2, v.begin());\n            std::fill(v.begin() + n / 2, v.end(),\
    \ T(0));\n            fft(v, true, true);\n            for (int i = 0; i < n;\
    \ ++i) {\n                T x = v[i] * W[i];\n                p[2 * n * j + 2\
    \ * i] = Q[2 * n * j + 2 * i + 1] * x;\n                p[2 * n * j + 2 * i +\
    \ 1] = -Q[2 * n * j + 2 * i] * x;\n            }\n        }\n        if (n <=\
    \ k) {\n            fft_x(p, 2 * k, true);\n            double_y(p, 0, n, true);\n\
    \        } else {\n            double_y(p, 0, 2 * n, true);\n            fft_x(p,\
    \ k, true);\n        }\n        return p;\n    };\n    auto p = rec(rec, size,\
    \ 1, std::move(g));\n    p.resize(size);\n    std::reverse(p.begin(), p.end());\n\
    \    p.resize(N);\n    return p;\n}\n\n} // namespace po167\n"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_composition.hpp
  requiredBy: []
  timestamp: '2026-10-22 03:55:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/comp.test.cpp
documentation_of: fps/FPS_composition.hpp
layout: document
redirect_from:
- /library/fps/FPS_composition.hpp
- /library/fps/FPS_composition.hpp.html
title: fps/FPS_composition.hpp
---
