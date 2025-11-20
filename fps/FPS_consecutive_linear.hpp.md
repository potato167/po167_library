---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: po167_library/fps/FPS_inv.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include<atcoder/convolution>\n#include \"po167_library/fps/FPS_inv.hpp\"\
    \nnamespace po167\n{\ntemplate<class T>\n// input A(x)\n// B(x) = 1 / A(x)\n//\
    \ return {B[l], B[l + 1], ... , B[r - 1]}\n// 0 < r\nstd::vector<T> FPS_Inv_Consecutive(long\
    \ long l, long long r, std::vector<T> A){\n    assert(0 < r);\n    if (l >= r)\
    \ return {};\n    if (r == 1){\n        std::vector<T> res(r - l, 0);\n      \
    \  res.back() = (T)(1) / (T)(A[0]);\n        return res;\n    }\n    if (r < (int)A.size()\
    \ * 4){\n        auto res = FPS_inv(A, r);\n        for (int i = 0; i < r; i++){\n\
    \            if (i + l < r) res[i] = res[i + l];\n            else res[i] = 0;\n\
    \        }\n        res.resize(r - l);\n        return res;\n    }\n    int d\
    \ = A.size();\n    int z = 1;\n    while ((1 << z) < d) z++;\n    std::vector<T>\
    \ nA(d);\n    for (int i = 0; i < d; i++){\n        nA[i] = A[i] * (1 - 2 * (i\
    \ & 1));\n    }\n    std::vector<T> nC(d);\n    // for (int i = 0; i < d; i++)\
    \ nC[i] = C[i * 2];\n    {\n        A.resize(1 << (z + 1));\n        atcoder::internal::butterfly(A);\n\
    \        for (int i = 0; i < (1 << z); i++){\n            A[i * 2] *= A[i * 2\
    \ + 1];\n            A[i * 2 + 1] = A[i * 2];\n        }\n        FPS_pick_even_odd(A,\
    \ 0);\n        atcoder::internal::butterfly_inv(A);\n        mint iz = ((mint)(1\
    \ << z)).inv();\n        for (int i = 0; i < d; i++) nC[i] = A[i] * iz;\n    }\n\
    \    // calc [l - d + 1, r) 1 / C\n    // calc [(l - d + 1) / 2, r / 2) 1 / nC\n\
    \    long long nl = std::max(0ll, (l - d) / 2);\n    long long nr = (r + 1) /\
    \ 2;\n    auto D = FPS_Inv_Consecutive(nl, nr, nC);\n    std::vector<T> nD(2 *\
    \ (int)D.size());\n    for (int i = 0; i < (int)D.size(); i++){\n        nD[i\
    \ * 2] = D[i];\n    }\n    auto B = atcoder::convolution(nD, nA);\n    std::vector<T>\
    \ res(r - l);\n    for (long long i = l; i < r; i++){\n        if (i >= 0) res[i\
    \ - l] = B[i - nl * 2];\n    }\n    return res;\n}\ntemplate<class T>\n// 0 =\
    \ a[i] * c[0] + a[i - 1] * c[1] + a[i - 2] * c[2] + ... + a[i - d] * c[d]\n//\
    \ a.size() + 1 == c.size()\n// almost c[0] = - 1 \n// return {a[l], a[l + 1],\
    \ ... , a[r - 1]}\nstd::vector<T> Consecutive_Linear(long long l, long long r,\
    \ std::vector<T> a, std::vector<T> c){\n    int d = a.size();\n    assert(d +\
    \ 1 == int(c.size()));\n    std::vector<T> P = atcoder::convolution(a, c);\n \
    \   P.resize(d);\n    std::vector<T> Q = FPS_Inv_Consecutive(l - d, r, c);\n \
    \   P = atcoder::convolution(P, Q);\n    for (int i = 0; i < r - l; i++){\n  \
    \      P[i] = P[i + d];\n    }\n    P.resize(r - l);\n    return P;\n}\n} // namespace\
    \ po167"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_consecutive_linear.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/FPS_consecutive_linear.hpp
layout: document
redirect_from:
- /library/fps/FPS_consecutive_linear.hpp
- /library/fps/FPS_consecutive_linear.hpp.html
title: fps/FPS_consecutive_linear.hpp
---
