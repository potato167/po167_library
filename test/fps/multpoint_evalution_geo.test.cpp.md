---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_cyclic_convolution.hpp
    title: fps/FPS_cyclic_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: fps/Multipoint_Evaluation_Geo.hpp
    title: fps/Multipoint_Evaluation_Geo.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence
    links:
    - https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence
  bundledCode: "#line 1 \"test/fps/multpoint_evalution_geo.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence\"\
    \n#line 2 \"fps/FPS_cyclic_convolution.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \nnamespace po167{\n// |f| = |g| = 2 ^ n\ntemplate<class T>\nstd::vector<T> FPS_cyclic_convolution(std::vector<T>\
    \ f, std::vector<T> g){\n    atcoder::internal::butterfly(f);\n    atcoder::internal::butterfly(g);\n\
    \    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];\n    atcoder::internal::butterfly_inv(f);\n\
    \    T iz = (T)(1) / (T)(f.size());\n    for (int i = 0; i < (int)f.size(); i++)\
    \ f[i] *= iz;\n    return f;\n}\n}\n#line 2 \"fps/Multipoint_Evaluation_Geo.hpp\"\
    \nnamespace po167{\n// return {f(ar^0), f(ar^1), f(ar^2), ... f(ar^{len - 1})}\n\
    template <class T>\nstd::vector<T> Multipoint_Evaluation_Geo(\n    std::vector<T>\
    \ f,\n    T a, T r, int len = -1\n){\n    if (len == -1) len = f.size();\n   \
    \ if (r == 0){\n        T tmp = 1;\n        std::vector<T> res(len, f[0]);\n \
    \       for (int i = 1; i < (int)f.size(); i++){\n            tmp *= a;\n    \
    \        res[0] += tmp * f[i];\n        }\n        return res;\n    }\n    /*\n\
    \    X[k] = sum (fi * (ar^k)^i)\n         = sum (fi * a^i * r^{ki})\n        \
    \ = sum (fi * a^i * r^t[k + i] * r^-t[k] * r^-t[i])\n         = r^-t[k] sum r^t[k\
    \ + i](fi * a^i * r^-t[i])\n    */\n    int n = f.size();\n    T invr = (T)(1)\
    \ / (T)(r);\n    T tmp = 1, tmpr1 = 1, tmpr2 = 1;\n    for (int i = 0; i < n;\
    \ i++){\n        f[i] *= tmp * tmpr2;\n        tmpr2 *= tmpr1;\n        tmpr1\
    \ *= invr;\n        tmp *= a;\n    }\n    std::vector<T> g(n + len - 1);\n   \
    \ tmpr1 = 1, tmpr2 = 1;\n    for (int i = 0; i < n + len - 1; i++){\n        g[i]\
    \ = tmpr2;\n        tmpr2 *= tmpr1;\n        tmpr1 *= r;\n    }\n    std::reverse(f.begin(),\
    \ f.end());\n    int size = 1;\n    while (size < n + len - 1) size *= 2;\n  \
    \  f.resize(size);\n    g.resize(size);\n    f = po167::FPS_cyclic_convolution(f,\
    \ g);\n    std::vector<T> res(len);\n    for (int i = n - 1; i < n + len - 1;\
    \ i++){\n        res[i - n + 1] = f[i];\n    }\n    tmpr1 = 1, tmpr2 = 1;\n  \
    \  for (int i = 0; i < len; i++){\n        res[i] *= tmpr2;\n        tmpr2 *=\
    \ tmpr1;\n        tmpr1 *= invr;\n    }\n    return res;\n}\n}\n#line 3 \"test/fps/multpoint_evalution_geo.test.cpp\"\
    \n\n#include <iostream>\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = atcoder::modint998244353;\n\n  \
    \  int N, M, a, r;\n    std::cin >> N >> M >> a >> r;\n    std::vector<mint> c(N);\n\
    \    int b;\n    for (auto &x : c){\n        std::cin >> b;\n        x = b;\n\
    \    }\n    auto ans = po167::Multipoint_Evaluation_Geo(c, (mint)(a), (mint)(r),\
    \ M);\n    for (int i = 0; i < (int)ans.size(); i++){\n        std::cout << ans[i].val()\
    \ << (i + 1 == (int)ans.size() ? \"\\n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence\"\
    \n#include \"../../fps/Multipoint_Evaluation_Geo.hpp\"\n\n#include <iostream>\n\
    int main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = atcoder::modint998244353;\n\n    int N, M, a, r;\n    std::cin\
    \ >> N >> M >> a >> r;\n    std::vector<mint> c(N);\n    int b;\n    for (auto\
    \ &x : c){\n        std::cin >> b;\n        x = b;\n    }\n    auto ans = po167::Multipoint_Evaluation_Geo(c,\
    \ (mint)(a), (mint)(r), M);\n    for (int i = 0; i < (int)ans.size(); i++){\n\
    \        std::cout << ans[i].val() << (i + 1 == (int)ans.size() ? \"\\n\" : \"\
    \ \");\n    }\n}"
  dependsOn:
  - fps/Multipoint_Evaluation_Geo.hpp
  - fps/FPS_cyclic_convolution.hpp
  isVerificationFile: true
  path: test/fps/multpoint_evalution_geo.test.cpp
  requiredBy: []
  timestamp: '2024-09-05 20:11:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/multpoint_evalution_geo.test.cpp
layout: document
redirect_from:
- /verify/test/fps/multpoint_evalution_geo.test.cpp
- /verify/test/fps/multpoint_evalution_geo.test.cpp.html
title: test/fps/multpoint_evalution_geo.test.cpp
---
