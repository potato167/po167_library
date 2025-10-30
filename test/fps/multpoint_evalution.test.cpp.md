---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Product_Sequence.hpp
    title: fps/FPS_Product_Sequence.hpp
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
    \n#include <atcoder/convolution>\n#line 2 \"fps/FPS_inv.hpp\"\n#include <vector>\n\
    #line 4 \"fps/FPS_inv.hpp\"\n\nnamespace po167{\n// return 1 / f\ntemplate <class\
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
    \    return g;\n}\n}\n#line 4 \"fps/FPS_Product_Sequence.hpp\"\n\nnamespace po167{\n\
    template<class T>\nstd::vector<T> FPS_Product_Sequence(std::vector<std::vector<T>>\
    \ f){\n    if (f.empty()) return {1};\n    auto op = [&](auto self,int l, int\
    \ r) -> std::vector<T> {\n        if (l + 1 == r) return f[l];\n        int m\
    \ = (l + r) / 2;\n        return atcoder::convolution(self(self, l, m), self(self,\
    \ m, r));\n    };\n    return op(op, 0, f.size());\n}\n}\n#line 5 \"fps/Multipoint_Evaluation.hpp\"\
    \n\nnamespace po167{\n// return {f(p[0]), f(p[1]), f(p[2]), ... }\n// https://codeforces.com/blog/entry/100279\n\
    template<class T>\nstd::vector<T> Multipoint_Evaluation(std::vector<T> f, std::vector<T>\
    \ p){\n    std::reverse(f.begin(), f.end());\n    int M = f.size();\n    int N\
    \ = p.size();\n    std::vector<std::vector<T>> g(N);\n    for (int i = 0; i <\
    \ N; i++){\n        g[i] = {1, p[i] * -1};\n    }\n    auto tmp = po167::FPS_Product_Sequence(g);\n\
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
    \    };\n    rec(rec, 1, tmp);\n    return res;\n}\n}\n#line 3 \"test/fps/multpoint_evalution.test.cpp\"\
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
  - fps/FPS_inv.hpp
  - fps/FPS_Product_Sequence.hpp
  isVerificationFile: true
  path: test/fps/multpoint_evalution.test.cpp
  requiredBy: []
  timestamp: '2025-10-30 10:13:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/multpoint_evalution.test.cpp
layout: document
redirect_from:
- /verify/test/fps/multpoint_evalution.test.cpp
- /verify/test/fps/multpoint_evalution.test.cpp.html
title: test/fps/multpoint_evalution.test.cpp
---
