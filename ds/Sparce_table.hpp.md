---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/tree/LCA.hpp
    title: graph/tree/LCA.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/sparce_table.test.cpp
    title: test/ds/sparce_table.test.cpp
  - icon: ':x:'
    path: test/graph/tree/jump_tree.test.cpp
    title: test/graph/tree/jump_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/tree/lca_1.test.cpp
    title: test/graph/tree/lca_1.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Sparce_table.hpp\"\n#include <vector>\n#include <cassert>\n\
    namespace po167{\ntemplate<class T, T(*op)(T, T)>\nstruct Sparce_table{\n    int\
    \ n;\n    int depth;\n    std::vector<std::vector<T>> val;\n    void init(std::vector<T>\
    \ &v){\n        depth = 1;\n        n = v.size();\n        while ((1 << depth)\
    \ <= n) depth++;\n        val.resize(depth);\n        val[0] = v;\n        for\
    \ (int i = 1; i < depth; i++){\n            val[i].resize(n);\n            for\
    \ (int j = 0; j <= n - (1 << i); j++){\n                val[i][j] = op(val[i -\
    \ 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n    }\n \
    \   Sparce_table(std::vector<T> v){\n        init(v);\n    }\n    Sparce_table(){}\n\
    \    // 0 <= l < r <= n\n    // if l == r : assert\n    T prod(int l, int r){\n\
    \        assert(0 <= l && l < r && r <= n);\n        int z=31-__builtin_clz(r-l);\n\
    \        return op(val[z][l], val[z][r - (1 << z)]);\n    }\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace po167{\ntemplate<class\
    \ T, T(*op)(T, T)>\nstruct Sparce_table{\n    int n;\n    int depth;\n    std::vector<std::vector<T>>\
    \ val;\n    void init(std::vector<T> &v){\n        depth = 1;\n        n = v.size();\n\
    \        while ((1 << depth) <= n) depth++;\n        val.resize(depth);\n    \
    \    val[0] = v;\n        for (int i = 1; i < depth; i++){\n            val[i].resize(n);\n\
    \            for (int j = 0; j <= n - (1 << i); j++){\n                val[i][j]\
    \ = op(val[i - 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n      \
    \  }\n    }\n    Sparce_table(std::vector<T> v){\n        init(v);\n    }\n  \
    \  Sparce_table(){}\n    // 0 <= l < r <= n\n    // if l == r : assert\n    T\
    \ prod(int l, int r){\n        assert(0 <= l && l < r && r <= n);\n        int\
    \ z=31-__builtin_clz(r-l);\n        return op(val[z][l], val[z][r - (1 << z)]);\n\
    \    }\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: ds/Sparce_table.hpp
  requiredBy:
  - graph/tree/LCA.hpp
  timestamp: '2024-11-20 00:33:35+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/ds/sparce_table.test.cpp
  - test/graph/tree/lca_1.test.cpp
  - test/graph/tree/jump_tree.test.cpp
documentation_of: ds/Sparce_table.hpp
layout: document
redirect_from:
- /library/ds/Sparce_table.hpp
- /library/ds/Sparce_table.hpp.html
title: ds/Sparce_table.hpp
---
