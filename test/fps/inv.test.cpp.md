---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "#line 1 \"test/fps/inv.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n#line 2 \"fps/FPS_inv.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \nnamespace po167{\n// return 1 / f\ntemplate <class T>\nstd::vector<T> FPS_inv(std::vector<T>\
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
    \ 3 \"test/fps/inv.test.cpp\"\n\n#line 5 \"test/fps/inv.test.cpp\"\n#include <iostream>\n\
    #include <atcoder/modint>\n\nint main(){\n    using mint = atcoder::modint998244353;\n\
    \    int N;\n    std::cin >> N;\n    std::vector<mint> A(N);\n    for (int i =\
    \ 0; i < N; i++){\n        int a;\n        std::cin >> a;\n        A[i] = a;\n\
    \    }\n    A = po167::FPS_inv(A, N);\n    for (int i = 0; i < N; i++){\n    \
    \    std::cout << A[i].val() << \" \";\n    }\n    std::cout << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n#include \"../../fps/FPS_inv.hpp\"\n\n#include <vector>\n#include <iostream>\n\
    #include <atcoder/modint>\n\nint main(){\n    using mint = atcoder::modint998244353;\n\
    \    int N;\n    std::cin >> N;\n    std::vector<mint> A(N);\n    for (int i =\
    \ 0; i < N; i++){\n        int a;\n        std::cin >> a;\n        A[i] = a;\n\
    \    }\n    A = po167::FPS_inv(A, N);\n    for (int i = 0; i < N; i++){\n    \
    \    std::cout << A[i].val() << \" \";\n    }\n    std::cout << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_inv.hpp
  isVerificationFile: true
  path: test/fps/inv.test.cpp
  requiredBy: []
  timestamp: '2024-06-19 01:08:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/inv.test.cpp
layout: document
redirect_from:
- /verify/test/fps/inv.test.cpp
- /verify/test/fps/inv.test.cpp.html
title: test/fps/inv.test.cpp
---
