---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_online_convolution.hpp
    title: fps/FPS_online_convolution.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/fps/online_fps.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\
    \n\n\n#line 2 \"fps/FPS_online_convolution.hpp\"\n#include <atcoder/convolution>\n\
    \nnamespace po167{\n    template<class T>\n    struct FPS_online_convolution{\n\
    \        std::vector<T> f, g, h;\n        std::vector<std::vector<T>> f_inv, g_inv;\n\
    \        int p;\n        FPS_online_convolution() : f(0), g(0), h(0), p(0){}\n\
    \        T query(T fi, T gi){\n            if (p == 0){\n                f = {fi};\n\
    \                g = {gi};\n                h = {fi * gi};\n                return\
    \ h[p++];\n            }\n            int z = 0;\n            while ((p & (1 <<\
    \ z)) == 0) z++;\n            if (p == (1 << z)){\n                f.resize(p\
    \ * 2, 0);\n                g.resize(p * 2, 0);\n                h.resize(p *\
    \ 2, 0);\n            }\n            f[p] = fi;\n            g[p] = gi;\n    \
    \        int l = p - (1 << z);\n            int m = p;\n            int r = p\
    \ + (1 << z);\n            // [l, m) -> [m, r)\n            std::vector<T> tmp3(r\
    \ - l);\n            if (l == 0){\n                f_inv.push_back({});\n    \
    \            g_inv.push_back({});\n            }\n            for (int rp = 0;\
    \ rp < 2; rp++){\n                std::swap(f, g);\n                std::swap(f_inv,\
    \ g_inv);\n                if (l == 0 && rp == 1) break;\n                std::vector<T>\
    \ tmp1(r - l), tmp2(r - l);\n                for (int i = l; i < m; i++){\n  \
    \                  tmp1[i - l] = f[i];\n                }\n                atcoder::internal::butterfly(tmp1);\n\
    \                if (l == 0) {\n                    for (int i = 0; i < r - l;\
    \ i++) {\n                        if (i == 0) continue;\n                    \
    \    if (m <= i) break;\n                        tmp2[i] = g[i];\n           \
    \         }\n                    atcoder::internal::butterfly(tmp2);\n       \
    \         }\n                else{\n                    if (g_inv[z].empty()){\n\
    \                        g_inv[z].resize((1 << (z + 1)));\n                  \
    \      for (int i = 0; i < (1 << (z + 1)); i++){\n                           \
    \ if (i) g_inv[z][i] = g[i];\n                            else g_inv[z][i] = 0;\n\
    \                        }\n                        atcoder::internal::butterfly(g_inv[z]);\n\
    \                    }\n                    tmp2 = g_inv[z];\n               \
    \ }\n                for (int i = 0; i < r - l; i++) tmp3[i] += tmp1[i] * tmp2[i];\n\
    \            }\n            atcoder::internal::butterfly_inv(tmp3);\n        \
    \    T iz = (T)(1) / (T)(r - l);\n            for (int i = m; i < r; i++) h[i]\
    \ += tmp3[i - l] * iz;\n            h[p] += f[0] * g[p];\n            h[p] +=\
    \ f[p] * g[0];\n            return h[p++];\n        }\n    };\n}\n#line 5 \"test/fps/online_fps.test.cpp\"\
    \n\n\n#include <iostream>\nusing mint = atcoder::modint998244353;\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ N, M;\n    std::cin >> N >> M;\n    int X = N + M - 1;\n    std::vector<int>\
    \ A(X), B(X);\n    for (int i = 0; i < N; i++) std::cin >> A[i];\n    for (int\
    \ i = 0; i < M; i++) std::cin >> B[i];\n    po167::FPS_online_convolution<mint>\
    \ oc;\n    for (int i = 0; i < X; i++){\n        if (i) std::cout << \" \";\n\
    \        std::cout << oc.query(A[i], B[i]).val();\n    }\n    std::cout << \"\\\
    n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n\n\
    #include \"../../fps/FPS_online_convolution.hpp\"\n\n\n#include <iostream>\nusing\
    \ mint = atcoder::modint998244353;\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int N, M;\n    std::cin >> N >> M;\n    int\
    \ X = N + M - 1;\n    std::vector<int> A(X), B(X);\n    for (int i = 0; i < N;\
    \ i++) std::cin >> A[i];\n    for (int i = 0; i < M; i++) std::cin >> B[i];\n\
    \    po167::FPS_online_convolution<mint> oc;\n    for (int i = 0; i < X; i++){\n\
    \        if (i) std::cout << \" \";\n        std::cout << oc.query(A[i], B[i]).val();\n\
    \    }\n    std::cout << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_online_convolution.hpp
  isVerificationFile: true
  path: test/fps/online_fps.test.cpp
  requiredBy: []
  timestamp: '2025-10-29 08:13:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/online_fps.test.cpp
layout: document
redirect_from:
- /verify/test/fps/online_fps.test.cpp
- /verify/test/fps/online_fps.test.cpp.html
title: test/fps/online_fps.test.cpp
---
