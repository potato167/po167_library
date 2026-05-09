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
  bundledCode: "#line 1 \"no_test/bm.hpp\"\ntemplate <typename mint>\nvector<mint>\
    \ BerlekampMassey(const vector<mint> &s) {\n    const int N = (int)s.size();\n\
    \    vector<mint> b, c;\n    b.reserve(N + 1);\n    c.reserve(N + 1);\n    b.push_back(mint(1));\n\
    \    c.push_back(mint(1));\n    mint y = mint(1);\n    for (int ed = 1; ed <=\
    \ N; ed++) {\n        int l = int(c.size()), m = int(b.size());\n        mint\
    \ x = 0;\n        for (int i = 0; i < l; i++) x += c[i] * s[ed - l + i];\n   \
    \     b.emplace_back(mint(0));\n        m++;\n        if (x == mint(0)) continue;\n\
    \        mint freq = x / y;\n        if (l < m) {\n            auto tmp = c;\n\
    \            c.insert(begin(c), m - l, mint(0));\n            for (int i = 0;\
    \ i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];\n            b = tmp;\n   \
    \         y = x;\n        } else {\n            for (int i = 0; i < m; i++) c[l\
    \ - 1 - i] -= freq * b[m - 1 - i];\n        }\n    }\n    reverse(begin(c), end(c));\n\
    \    return c;\n}\n"
  code: "template <typename mint>\nvector<mint> BerlekampMassey(const vector<mint>\
    \ &s) {\n    const int N = (int)s.size();\n    vector<mint> b, c;\n    b.reserve(N\
    \ + 1);\n    c.reserve(N + 1);\n    b.push_back(mint(1));\n    c.push_back(mint(1));\n\
    \    mint y = mint(1);\n    for (int ed = 1; ed <= N; ed++) {\n        int l =\
    \ int(c.size()), m = int(b.size());\n        mint x = 0;\n        for (int i =\
    \ 0; i < l; i++) x += c[i] * s[ed - l + i];\n        b.emplace_back(mint(0));\n\
    \        m++;\n        if (x == mint(0)) continue;\n        mint freq = x / y;\n\
    \        if (l < m) {\n            auto tmp = c;\n            c.insert(begin(c),\
    \ m - l, mint(0));\n            for (int i = 0; i < m; i++) c[m - 1 - i] -= freq\
    \ * b[m - 1 - i];\n            b = tmp;\n            y = x;\n        } else {\n\
    \            for (int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];\n\
    \        }\n    }\n    reverse(begin(c), end(c));\n    return c;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/bm.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/bm.hpp
layout: document
redirect_from:
- /library/no_test/bm.hpp
- /library/no_test/bm.hpp.html
title: no_test/bm.hpp
---
