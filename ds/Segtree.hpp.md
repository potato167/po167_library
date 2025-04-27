---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/ds/segtree.cpp
    title: test/ds/segtree.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Segtree.hpp\"\n#include <atcoder/segtree>\n\nnamespace\
    \ po167{\ntemplate <class S, S (*op)(S, S), S (*e)()>\nstruct segtree : atcoder::segtree<S,\
    \ op, e> {\n    using atcoder::segtree<S, op, e>::segtree;\n    void updr(int\
    \ ind, S x) {\n        this->set(ind, op(this->get(ind), x));\n    }\n    void\
    \ updl(int ind, S x) {\n        this->set(ind, op(x, this->get(ind)));\n    }\n\
    };\n}\n"
  code: "#pragma once\n#include <atcoder/segtree>\n\nnamespace po167{\ntemplate <class\
    \ S, S (*op)(S, S), S (*e)()>\nstruct segtree : atcoder::segtree<S, op, e> {\n\
    \    using atcoder::segtree<S, op, e>::segtree;\n    void updr(int ind, S x) {\n\
    \        this->set(ind, op(this->get(ind), x));\n    }\n    void updl(int ind,\
    \ S x) {\n        this->set(ind, op(x, this->get(ind)));\n    }\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: ds/Segtree.hpp
  requiredBy:
  - test/ds/segtree.cpp
  timestamp: '2025-04-27 17:28:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/Segtree.hpp
layout: document
redirect_from:
- /library/ds/Segtree.hpp
- /library/ds/Segtree.hpp.html
title: ds/Segtree.hpp
---
