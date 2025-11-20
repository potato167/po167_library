---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_consecutive_linear.hpp
    title: fps/FPS_consecutive_linear.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inv.hpp
    title: fps/FPS_inv.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence
  bundledCode: "#line 1 \"test/fps/consecutive_linear.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence\"\
    \n\n\n#line 2 \"fps/FPS_consecutive_linear.hpp\"\n#include<atcoder/convolution>\n\
    #line 2 \"fps/FPS_inv.hpp\"\n#include <vector>\n#line 4 \"fps/FPS_inv.hpp\"\n\n\
    namespace po167{\n// return 1 / f\ntemplate <class T>\nstd::vector<T> FPS_inv(std::vector<T>\
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
    \ 3 \"fps/FPS_pick_even_odd.hpp\"\n\nnamespace po167{\n// s.t |v| = 2 ^ s (no\
    \ assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T> &v, int odd){\n\
    \    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n    if (odd == 0){\n\
    \        for (int i = 0; i < z; i++){\n            v[i] = (v[i * 2] + v[i * 2\
    \ + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n        T e =\
    \ (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod() / (2\
    \ * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n    \
    \    while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}\n#line\
    \ 5 \"fps/FPS_consecutive_linear.hpp\"\n\nnamespace po167\n{\ntemplate<class T>\n\
    // input A(x)\n// B(x) = 1 / A(x)\n// return {B[l], B[l + 1], ... , B[r - 1]}\n\
    // 0 < r\nstd::vector<T> FPS_Inv_Consecutive(long long l, long long r, std::vector<T>\
    \ A){\n    assert(0 < r);\n    if (l >= r) return {};\n    if (r == 1){\n    \
    \    std::vector<T> res(r - l, 0);\n        res.back() = (T)(1) / (T)(A[0]);\n\
    \        return res;\n    }\n    if (r < (int)A.size() * 4){\n        auto res\
    \ = FPS_inv(A, r);\n        std::vector<T> n_res(r - l);\n        for (int i =\
    \ 0; i < r - l; i++){\n            if (0 <= i + l && i + l < r) n_res[i] = res[i\
    \ + l];\n            else n_res[i] = 0;\n        }\n        return n_res;\n  \
    \  }\n    int d = A.size();\n    int z = 1;\n    while ((1 << z) < d) z++;\n \
    \   std::vector<T> nA(d);\n    for (int i = 0; i < d; i++){\n        nA[i] = A[i]\
    \ * (1 - 2 * (i & 1));\n    }\n    std::vector<T> nC(d);\n    // for (int i =\
    \ 0; i < d; i++) nC[i] = C[i * 2];\n    {\n        A.resize(1 << (z + 1));\n \
    \       atcoder::internal::butterfly(A);\n        for (int i = 0; i < (1 << z);\
    \ i++){\n            A[i * 2] *= A[i * 2 + 1];\n            A[i * 2 + 1] = A[i\
    \ * 2];\n        }\n        FPS_pick_even_odd(A, 0);\n        atcoder::internal::butterfly_inv(A);\n\
    \        T iz = ((T)(1)) / ((T)(1 << z));\n        for (int i = 0; i < d; i++)\
    \ nC[i] = A[i] * iz;\n    }\n    // calc [l - d + 1, r) 1 / C\n    // calc [(l\
    \ - d + 1) / 2, r / 2) 1 / nC\n    long long nl = std::max(0ll, (l - d) / 2);\n\
    \    long long nr = (r + 1) / 2;\n    auto D = FPS_Inv_Consecutive(nl, nr, nC);\n\
    \    std::vector<T> nD(2 * (int)D.size());\n    for (int i = 0; i < (int)D.size();\
    \ i++){\n        nD[i * 2] = D[i];\n    }\n    auto B = atcoder::convolution(nD,\
    \ nA);\n    std::vector<T> res(r - l);\n    for (long long i = l; i < r; i++){\n\
    \        if (i >= 0) res[i - l] = B[i - nl * 2];\n    }\n    return res;\n}\n\
    template<class T>\n// 0 = a[i] * c[0] + a[i - 1] * c[1] + a[i - 2] * c[2] + ...\
    \ + a[i - d] * c[d]\n// a.size() + 1 == c.size()\n// almost c[0] = - 1 \n// return\
    \ {a[l], a[l + 1], ... , a[r - 1]}\nstd::vector<T> Consecutive_Linear(long long\
    \ l, long long r, std::vector<T> a, std::vector<T> c){\n    int d = a.size();\n\
    \    assert(d + 1 == int(c.size()));\n    std::vector<T> P = atcoder::convolution(a,\
    \ c);\n    P.resize(d);\n    std::vector<T> Q = FPS_Inv_Consecutive(l - d, r,\
    \ c);\n    P = atcoder::convolution(P, Q);\n    for (int i = 0; i < r - l; i++){\n\
    \        P[i] = P[i + d];\n    }\n    P.resize(r - l);\n    return P;\n}\n} //\
    \ namespace po167\n#line 5 \"test/fps/consecutive_linear.test.cpp\"\n#include<iostream>\n\
    int main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = atcoder::modint998244353;\n\n    long long d, k, M, num;\n \
    \   std::cin >> d >> k >> M;\n    std::vector<mint> A(d), C(d + 1);\n    for (int\
    \ i = 0; i < d; i++) std::cin >> num, A[i] = num;\n    for (int i = 1; i <= d;\
    \ i++) std::cin >> num, C[i] = num;\n    C[0] = -1;\n    auto ans = po167::Consecutive_Linear(k,\
    \ k + M, A, C);\n    for (int i = 0; i < (int)ans.size(); i++){\n        if (i)\
    \ std::cout << \" \";\n        std::cout << ans[i].val();\n    }\n    std::cout\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence\"\
    \n\n\n#include \"../../fps/FPS_consecutive_linear.hpp\"\n#include<iostream>\n\
    int main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = atcoder::modint998244353;\n\n    long long d, k, M, num;\n \
    \   std::cin >> d >> k >> M;\n    std::vector<mint> A(d), C(d + 1);\n    for (int\
    \ i = 0; i < d; i++) std::cin >> num, A[i] = num;\n    for (int i = 1; i <= d;\
    \ i++) std::cin >> num, C[i] = num;\n    C[0] = -1;\n    auto ans = po167::Consecutive_Linear(k,\
    \ k + M, A, C);\n    for (int i = 0; i < (int)ans.size(); i++){\n        if (i)\
    \ std::cout << \" \";\n        std::cout << ans[i].val();\n    }\n    std::cout\
    \ << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_consecutive_linear.hpp
  - fps/FPS_inv.hpp
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: true
  path: test/fps/consecutive_linear.test.cpp
  requiredBy: []
  timestamp: '2025-11-20 14:15:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/consecutive_linear.test.cpp
layout: document
redirect_from:
- /verify/test/fps/consecutive_linear.test.cpp
- /verify/test/fps/consecutive_linear.test.cpp.html
title: test/fps/consecutive_linear.test.cpp
---
