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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: po167_library/fps/FPS_division.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <atcoder/convolution>\n#include \"po167_library/fps/FPS_division.hpp\"\
    \n\nnamespace po167{\ntemplate <class T>\n// return {f(p[0]), f(p[1]), f(p[2]),\
    \ ... }\nstd::vector<T> Multipoint_Evaluation(\n    std::vector<T> f,\n    std::vector<T>\
    \ p\n){\n    int m = p.size();\n    if (m == 0) return {};\n    if (m == 1){\n\
    \        T res = 0;\n        T tmp = 1;\n        for (auto x : f) res += tmp *\
    \ x, tmp *= p[0];\n        return {res};\n    }\n    int size = 1;\n    while\
    \ (size < m) size *= 2;\n    std::vector<std::vector<T>> prod(size * 2);\n   \
    \ for (int i = 0; i < size; i++){\n        if (i < m) prod[i + size] = {(T)(-1)\
    \ * p[i], 1};\n        else prod[i + size] = {1};\n    }\n    for (int i = size\
    \ - 1; i > 0; i--){\n        prod[i] = atcoder::convolution(prod[i * 2], prod[i\
    \ * 2 + 1]);\n    }\n    std::vector<T> res(m);\n    auto calc = [&](auto self,\
    \ int l, int r, int ind, std::vector<T> tmp) -> void {\n        if (m <= l) return;\n\
    \        if (l + 1 == r){\n            res[l] = tmp[0];\n            return;\n\
    \        }\n        int mid = (l + r) / 2;\n        self(self, l, mid, ind * 2,\
    \ po167::FPS_division(tmp, prod[ind * 2]).second);\n        self(self, mid, r,\
    \ ind * 2 + 1, po167::FPS_division(tmp, prod[ind * 2 + 1]).second);\n    };calc(calc,\
    \ 0, size, 1, f);\n    return res;\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/Multipoint_Evaluation.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fps/Multipoint_Evaluation.hpp
layout: document
redirect_from:
- /library/fps/Multipoint_Evaluation.hpp
- /library/fps/Multipoint_Evaluation.hpp.html
title: fps/Multipoint_Evaluation.hpp
---
