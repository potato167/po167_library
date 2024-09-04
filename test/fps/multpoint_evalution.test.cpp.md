---
data:
  _extendedDependsOn:
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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/multipoint_evaluation
    links:
    - https://judge.yosupo.jp/problem/multipoint_evaluation
  bundledCode: "#line 1 \"test/fps/multpoint_evalution.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/multipoint_evaluation\"\n#line 2 \"fps/Multipoint_Evaluation.hpp\"\
    \n#include <atcoder/convolution>\n#line 2 \"fps/FPS_division.hpp\"\n#include <vector>\n\
    #line 4 \"fps/FPS_division.hpp\"\n\n#line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n\
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
    \ 6 \"fps/FPS_division.hpp\"\nnamespace po167{\ntemplate<class T>\n// f = g *\
    \ res.first + res.second\n// |res.first| <= |f| - |g| + 1\n// |res.second| <=\
    \ |g| - 1\nstd::pair<std::vector<T>, std::vector<T>>\nFPS_division(std::vector<T>\
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
    \    return {q, r};\n}\n}\n#line 4 \"fps/Multipoint_Evaluation.hpp\"\n\nnamespace\
    \ po167{\ntemplate <class T>\n// return {f(p[0]), f(p[1]), f(p[2]), ... }\nstd::vector<T>\
    \ Multipoint_Evaluation(\n    std::vector<T> f,\n    std::vector<T> p\n){\n  \
    \  int m = p.size();\n    if (m == 0) return {};\n    if (m == 1){\n        T\
    \ res = 0;\n        T tmp = 1;\n        for (auto x : f) res += tmp * x, tmp *=\
    \ p[0];\n        return {res};\n    }\n    int size = 1;\n    while (size < m)\
    \ size *= 2;\n    std::vector<std::vector<T>> prod(size * 2);\n    for (int i\
    \ = 0; i < size; i++){\n        if (i < m) prod[i + size] = {(T)(-1) * p[i], 1};\n\
    \        else prod[i + size] = {1};\n    }\n    for (int i = size - 1; i > 0;\
    \ i--){\n        prod[i] = atcoder::convolution(prod[i * 2], prod[i * 2 + 1]);\n\
    \    }\n    std::vector<T> res(m);\n    auto calc = [&](auto self, int l, int\
    \ r, int ind, std::vector<T> tmp) -> void {\n        if (m <= l) return;\n   \
    \     if (l + 1 == r){\n            res[l] = tmp[0];\n            return;\n  \
    \      }\n        int mid = (l + r) / 2;\n        self(self, l, mid, ind * 2,\
    \ po167::FPS_division(tmp, prod[ind * 2]).second);\n        self(self, mid, r,\
    \ ind * 2 + 1, po167::FPS_division(tmp, prod[ind * 2 + 1]).second);\n    };calc(calc,\
    \ 0, size, 1, f);\n    return res;\n}\n}\n#line 3 \"test/fps/multpoint_evalution.test.cpp\"\
    \n\n#include <iostream>\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = atcoder::modint998244353;\n\n  \
    \  int N, M;\n    std::cin >> N >> M;\n    std::vector<mint> c(N), p(M);\n   \
    \ int a;\n    for (auto &x : c){\n        std::cin >> a;\n        x = a;\n   \
    \ }\n    for (auto &x : p){\n        std::cin >> a;\n        x = a;\n    }\n \
    \   auto ans = po167::Multipoint_Evaluation(c, p);\n    for (int i = 0; i < (int)ans.size();\
    \ i++){\n        std::cout << ans[i].val() << (i + 1 == (int)ans.size() ? \"\\\
    n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multipoint_evaluation\"\
    \n#include \"../../fps/Multipoint_Evaluation.hpp\"\n\n#include <iostream>\nint\
    \ main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = atcoder::modint998244353;\n\n    int N, M;\n    std::cin >>\
    \ N >> M;\n    std::vector<mint> c(N), p(M);\n    int a;\n    for (auto &x : c){\n\
    \        std::cin >> a;\n        x = a;\n    }\n    for (auto &x : p){\n     \
    \   std::cin >> a;\n        x = a;\n    }\n    auto ans = po167::Multipoint_Evaluation(c,\
    \ p);\n    for (int i = 0; i < (int)ans.size(); i++){\n        std::cout << ans[i].val()\
    \ << (i + 1 == (int)ans.size() ? \"\\n\" : \" \");\n    }\n}"
  dependsOn:
  - fps/Multipoint_Evaluation.hpp
  - fps/FPS_division.hpp
  - fps/FPS_inv.hpp
  isVerificationFile: true
  path: test/fps/multpoint_evalution.test.cpp
  requiredBy: []
  timestamp: '2024-09-05 05:56:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/multpoint_evalution.test.cpp
layout: document
redirect_from:
- /verify/test/fps/multpoint_evalution.test.cpp
- /verify/test/fps/multpoint_evalution.test.cpp.html
title: test/fps/multpoint_evalution.test.cpp
---
