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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: po167_library/fps/FPS_Product_Sequence.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"po167_library/fps/FPS_Product_Sequence.hpp\"\n#include\
    \ \"po167_library/fps/Multipoint_Evaluation.hpp\"\n#include \"po167_library/fps/FPS_add.hpp\"\
    \n\nnamespace po167{\ntemplate<class T>\n// \u30E9\u30B0\u30E9\u30F3\u30B8\u30E5\
    \u306E\u591A\u9805\u5F0F\u88DC\u5B8C\n// f(X[i]) = Y[i] \u3067\u3042\u308B f \u3092\
    \u8FD4\u3059\nstd::vector<T> Polynomial_Interpolation(std::vector<int> X, std::vector<T>\
    \ Y){\n    int N = X.size();\n    assert(Y.size() == X.size());\n    if (N ==\
    \ 0) return {};\n    {\n        auto Z = X;\n        std::sort(Z.begin(), Z.end());\n\
    \        for (int i = 0; i < N - 1; i++){\n            assert(Z[i] != Z[i + 1]);\n\
    \        }\n    }\n    std::vector<std::vector<T>> p(N);\n    for (int i = 0;\
    \ i < N; i++) p[i] = {-X[i], 1};\n    auto g = FPS_Product_Sequence(p);\n    for\
    \ (int i = 0; i < N; i++){\n        g[i] = g[i + 1] * (i + 1);\n    }\n    g.pop_back();\n\
    \    std::vector<T> xt(N);\n    for (int i = 0; i < N; i++) xt[i] = X[i];\n  \
    \  auto Z = Multipoint_Evaluation(g, xt);\n    auto rec = [&](auto self, int l,\
    \ int r) -> std::pair<std::vector<T>, std::vector<T>> {\n        if (l + 1 ==\
    \ r){\n            return {{Y[l] / Z[l]}, {-X[l], 1}};\n        }\n        int\
    \ m = (l + r) / 2;\n        auto L = self(self, l, m);\n        auto R = self(self,\
    \ m, r);\n        auto D = atcoder::convolution(L.second, R.second);\n       \
    \ auto U = atcoder::convolution(L.second, R.first);\n        FPS_add(U, atcoder::convolution(L.first,\
    \ R.second));\n        return {U, D};\n    };\n    return rec(rec, 0, N).first;\n\
    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: fps/Polynomial_Interpolation.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/Polynomial_Interpolation.hpp
layout: document
redirect_from:
- /library/fps/Polynomial_Interpolation.hpp
- /library/fps/Polynomial_Interpolation.hpp.html
title: fps/Polynomial_Interpolation.hpp
---
