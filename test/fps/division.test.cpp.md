---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_division.hpp
    title: fps/FPS_division.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/division_of_polynomials
    links:
    - https://judge.yosupo.jp/problem/division_of_polynomials
  bundledCode: "#line 1 \"test/fps/division.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/division_of_polynomials\"\
    \n\n#line 2 \"fps/FPS_division.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate <class\
    \ T>\nstd::vector<T> FPS_inv(std::vector<T> f, int len = -1){\n    if (len ==\
    \ -1) len = f.size();\n    assert(f[0] != 0);\n    std::vector<T> g = {1 / f[0]};\n\
    \    int s = 1;\n    while(s < len){\n        // g = 2g_s - f(g_s)^2 (mod x ^\
    \ (2 * s))\n        // g = g - (fg - 1)g\n        // (fg - 1) = 0 (mod x ^ (s))\n\
    \        std::vector<T> n_g(s * 2, 0);\n        std::vector<T> f_s(s * 2, 0);\n\
    \        g.resize(s * 2);\n        for (int i = 0; i < s * 2; i++){\n        \
    \    if (int(f.size()) > i) f_s[i] = f[i];\n            n_g[i] = g[i];\n     \
    \   }\n        atcoder::internal::butterfly(g);\n        atcoder::internal::butterfly(f_s);\n\
    \        for (int i = 0; i < s * 2; i++){\n            f_s[i] *= g[i];\n     \
    \   }\n        atcoder::internal::butterfly_inv(f_s);\n        T iz = 1 / (T)(s\
    \ * 2);\n        for (int i = s; i < s * 2; i++){\n            f_s[i] *= iz;\n\
    \        }\n        for (int i = 0; i < s; i++){\n            f_s[i] = 0;\n  \
    \      }\n        atcoder::internal::butterfly(f_s);\n        for (int i = 0;\
    \ i < s * 2; i++){\n            f_s[i] *= g[i];\n        }\n        atcoder::internal::butterfly_inv(f_s);\n\
    \        for (int i = s; i < s * 2; i++){\n            n_g[i] -= f_s[i] * iz;\n\
    \        }\n        std::swap(n_g, g);\n        s *= 2;\n    }\n    g.resize(len);\n\
    \    return g;\n}\n}\n#line 6 \"fps/FPS_division.hpp\"\nnamespace po167{\ntemplate<class\
    \ T>\n// f = g * res.first + res.second\n// |res.first| <= |f| - |g| + 1\n// |res.second|\
    \ <= |g| - 1\nstd::pair<std::vector<T>, std::vector<T>>\nFPS_division(std::vector<T>\
    \ f, std::vector<T> g){\n    while (!f.empty() && f.back() == 0) f.pop_back();\n\
    \    assert(!f.empty());\n    assert(!g.empty() && g.back() != 0);\n    if (f.size()\
    \ < g.size()){\n        return {{}, f};\n    }\n    // rev(f) / rev(g) = rev(q)\
    \ (mod x ^ {|f| - |g| + 1})\n    std::vector<T> r = f;\n    std::reverse(f.begin(),\
    \ f.end());\n    std::reverse(g.begin(), g.end());\n    int z = (int)f.size()\
    \ - (int)g.size() + 1;\n    f.resize(z);\n    std::vector<T> q = atcoder::convolution(f,\
    \ FPS_inv(g, z));\n    q.resize(z);\n    std::reverse(g.begin(), g.end());\n \
    \   std::reverse(q.begin(), q.end());\n    f = atcoder::convolution(q, g);\n \
    \   for (int i = 0; i < (int)f.size(); i++) r[i] -= f[i];\n    while (!q.empty()\
    \ && q.back() == 0) q.pop_back();\n    while (!r.empty() && r.back() == 0) r.pop_back();\n\
    \    return {q, r};\n}\n}\n#line 4 \"test/fps/division.test.cpp\"\n\n#line 6 \"\
    test/fps/division.test.cpp\"\n#include <iostream>\n#include <atcoder/modint>\n\
    \nint main(){\n    int N, M, a;\n    std::cin >> N >> M;\n    std::vector<atcoder::modint998244353>\
    \ f(N), g(M);\n    for (int i = 0; i < N; i++){\n        std::cin >> a;\n    \
    \    f[i] = a;\n    }\n    for (int i = 0; i < M; i++){\n        std::cin >> a;\n\
    \        g[i] = a;\n    }\n    auto ans = po167::FPS_division(f, g);\n    std::cout\
    \ << ans.first.size() << \" \" << ans.second.size() << \"\\n\";\n    for (int\
    \ i = 0; i < (int)ans.first.size(); i++){\n        if (i) std::cout << \" \";\n\
    \        std::cout << ans.first[i].val();\n    }\n    std::cout << \"\\n\";\n\
    \    for (int i = 0; i < (int)ans.second.size(); i++){\n        if (i) std::cout\
    \ << \" \";\n        std::cout << ans.second[i].val();\n    }\n    std::cout <<\
    \ \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/division_of_polynomials\"\
    \n\n#include \"../../fps/FPS_division.hpp\"\n\n#include <vector>\n#include <iostream>\n\
    #include <atcoder/modint>\n\nint main(){\n    int N, M, a;\n    std::cin >> N\
    \ >> M;\n    std::vector<atcoder::modint998244353> f(N), g(M);\n    for (int i\
    \ = 0; i < N; i++){\n        std::cin >> a;\n        f[i] = a;\n    }\n    for\
    \ (int i = 0; i < M; i++){\n        std::cin >> a;\n        g[i] = a;\n    }\n\
    \    auto ans = po167::FPS_division(f, g);\n    std::cout << ans.first.size()\
    \ << \" \" << ans.second.size() << \"\\n\";\n    for (int i = 0; i < (int)ans.first.size();\
    \ i++){\n        if (i) std::cout << \" \";\n        std::cout << ans.first[i].val();\n\
    \    }\n    std::cout << \"\\n\";\n    for (int i = 0; i < (int)ans.second.size();\
    \ i++){\n        if (i) std::cout << \" \";\n        std::cout << ans.second[i].val();\n\
    \    }\n    std::cout << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_division.hpp
  - fps/FPS_inv.hpp
  isVerificationFile: true
  path: test/fps/division.test.cpp
  requiredBy: []
  timestamp: '2024-06-22 20:46:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/division.test.cpp
layout: document
redirect_from:
- /verify/test/fps/division.test.cpp
- /verify/test/fps/division.test.cpp.html
title: test/fps/division.test.cpp
---
