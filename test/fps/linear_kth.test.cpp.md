---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Boston_Mori.hpp
    title: "\u30DC\u30B9\u30BF\u30F3\u68EE\u6CD5"
  - icon: ':heavy_check_mark:'
    path: fps/FPS_extend.hpp
    title: fps/FPS_extend.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "#line 1 \"test/fps/linear_kth.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#line 2 \"fps/FPS_Boston_Mori.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    #include <cassert>\n#line 4 \"fps/FPS_extend.hpp\"\n\nnamespace po167{\n// in\
    \  : DFT(v) (len(v) = z)\n// out : DFT(v) (len(v) = 2 * z)\ntemplate<class T>\n\
    void FPS_extend(std::vector<T> &v){\n    int z = v.size();\n    T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n    auto cp = v;\n    atcoder::internal::butterfly_inv(cp);\n \
    \   T tmp = (T)(1) / (T)(z);\n    for (int i = 0; i < z; i++){\n        cp[i]\
    \ *= tmp;\n        tmp *= e;\n    }\n    atcoder::internal::butterfly(cp);\n \
    \   for (int i = 0; i < z; i++) v.push_back(cp[i]);\n};\n}\n#line 3 \"fps/FPS_pick_even_odd.hpp\"\
    \n\nnamespace po167{\n// s.t |v| = 2 ^ s (no assert)\ntemplate<class T>\nvoid\
    \ FPS_pick_even_odd(std::vector<T> &v, int odd){\n    int z = v.size() / 2;\n\
    \    T half = (T)(1) / (T)(2);\n    if (odd == 0){\n        for (int i = 0; i\
    \ < z; i++){\n            v[i] = (v[i * 2] + v[i * 2 + 1]) * half;\n        }\n\
    \        v.resize(z);\n    } else {\n        T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n\
    \        while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}\n#line\
    \ 7 \"fps/FPS_Boston_Mori.hpp\"\n\nnamespace po167{\n// return [x^k] P(x) / Q(x)\n\
    template<class T>\nT Boston_Mori(long long k, std::vector<T> P, std::vector<T>\
    \ Q){\n    assert(!Q.empty() && Q[0] != 0);\n    int z = 1;\n    while (z < (int)std::max(P.size(),\
    \ Q.size())) z *= 2;\n    P.resize(z * 2, 0);\n    Q.resize(z * 2, 0);\n    atcoder::internal::butterfly(P);\n\
    \    atcoder::internal::butterfly(Q);\n\n    // fast\n    while (k){\n       \
    \ // Q(-x)\n        std::vector<T> Q_n(z * 2);\n        for (int i = 0; i < z;\
    \ i++){\n            Q_n[i * 2] = Q[i * 2 + 1];\n            Q_n[i * 2 + 1] =\
    \ Q[i * 2];\n        }\n        for (int i = 0; i < z * 2; i++){\n           \
    \ P[i] *= Q_n[i];\n            Q[i] *= Q_n[i];\n        }\n        FPS_pick_even_odd(P,\
    \ k & 1);\n        FPS_pick_even_odd(Q, 0);\n        k /= 2;\n        if (k ==\
    \ 0) break;\n        FPS_extend(P);\n        FPS_extend(Q);\n    }\n    T SP =\
    \ 0, SQ = 0;\n    for (int i = 0; i < z; i++) SP += P[i], SQ += Q[i];\n    return\
    \ SP / SQ;\n\n    // simple\n    /*\n    while (k){\n        auto n_Q = Q;\n \
    \       for (int i = 0; i < int(Q.size()); i++){\n            if (i & 1) n_Q[i]\
    \ *= -1;\n        }\n        auto n_P = atcoder::convolution(P, n_Q);\n      \
    \  n_Q = atcoder::convolution(Q, n_Q);\n        for (int i = 0; i < int(Q.size());\
    \ i++){\n            Q[i] = n_Q[i * 2];\n        }\n        P.clear();\n     \
    \   for (int i = (k & 1); i < int(n_P.size()); i += 2){\n            P.push_back(n_P[i]);\n\
    \        }\n        k >>= 1;\n    }\n    return P[0] / Q[0];\n    */\n}\n\ntemplate<class\
    \ T>\n// 0 = a[i] * c[0] + a[i - 1] * c[1] + a[i - 2] * c[2] + ... + a[i - d]\
    \ * c[d]\n// a.size() + 1 == c.size()\n// c[0] = - 1 ?\n// return a[k]\nT Kth_Linear(long\
    \ long k, std::vector<T> a, std::vector<T> c){\n    int d = a.size();\n    assert(d\
    \ + 1 == int(c.size()));\n    std::vector<T> P = atcoder::convolution(a, c);\n\
    \    P.resize(d);\n    return Boston_Mori(k, P, c);\n}\n};\n#line 4 \"test/fps/linear_kth.test.cpp\"\
    \n\n#line 6 \"test/fps/linear_kth.test.cpp\"\n#include <iostream>\n\nint main(){\n\
    \    using mint = atcoder::modint998244353;\n    int d;\n    long long k;\n  \
    \  std::cin >> d >> k;\n    std::vector<mint> a(d), c(d + 1, -1);\n    int mem;\n\
    \    for (int i = 0; i < d; i++) std::cin >> mem, a[i] = mem;\n    for (int i\
    \ = 1; i <= d; i++) std::cin >> mem, c[i] = mem;\n    std::cout << po167::Kth_Linear(k,\
    \ a, c).val() << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include \"../../fps/FPS_Boston_Mori.hpp\"\n\n#include <vector>\n#include\
    \ <iostream>\n\nint main(){\n    using mint = atcoder::modint998244353;\n    int\
    \ d;\n    long long k;\n    std::cin >> d >> k;\n    std::vector<mint> a(d), c(d\
    \ + 1, -1);\n    int mem;\n    for (int i = 0; i < d; i++) std::cin >> mem, a[i]\
    \ = mem;\n    for (int i = 1; i <= d; i++) std::cin >> mem, c[i] = mem;\n    std::cout\
    \ << po167::Kth_Linear(k, a, c).val() << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_Boston_Mori.hpp
  - fps/FPS_extend.hpp
  - fps/FPS_pick_even_odd.hpp
  isVerificationFile: true
  path: test/fps/linear_kth.test.cpp
  requiredBy: []
  timestamp: '2024-06-19 15:49:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/linear_kth.test.cpp
layout: document
redirect_from:
- /verify/test/fps/linear_kth.test.cpp
- /verify/test/fps/linear_kth.test.cpp.html
title: test/fps/linear_kth.test.cpp
---
