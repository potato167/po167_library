---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: graph/tree/Auxiliary_Tree.hpp
    title: graph/tree/Auxiliary_Tree.hpp
  - icon: ':heavy_check_mark:'
    path: graph/tree/LCA.hpp
    title: graph/tree/LCA.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/sparse_table.test.cpp
    title: test/ds/sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/tree/jump_tree.test.cpp
    title: test/graph/tree/jump_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/tree/lca_1.test.cpp
    title: test/graph/tree/lca_1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Sparse_table.hpp\"\n#include <vector>\n#include <cassert>\n\
    namespace po167{\ntemplate<class T, T(*op)(T, T)>\nstruct Sparse_table{\n    int\
    \ n;\n    int depth;\n    std::vector<std::vector<T>> val;\n    void init(std::vector<T>\
    \ &v){\n        depth = 1;\n        n = v.size();\n        while ((1 << depth)\
    \ <= n) depth++;\n        val.resize(depth);\n        val[0] = v;\n        for\
    \ (int i = 1; i < depth; i++){\n            val[i].resize(n);\n            for\
    \ (int j = 0; j <= n - (1 << i); j++){\n                val[i][j] = op(val[i -\
    \ 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n    }\n \
    \   Sparse_table(std::vector<T> v){\n        init(v);\n    }\n    Sparse_table(){}\n\
    \    // 0 <= l < r <= n\n    // if l == r : assert\n    T prod(int l, int r){\n\
    \        assert(0 <= l && l < r && r <= n);\n        int z=31-__builtin_clz(r-l);\n\
    \        return op(val[z][l], val[z][r - (1 << z)]);\n    }\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace po167{\ntemplate<class\
    \ T, T(*op)(T, T)>\nstruct Sparse_table{\n    int n;\n    int depth;\n    std::vector<std::vector<T>>\
    \ val;\n    void init(std::vector<T> &v){\n        depth = 1;\n        n = v.size();\n\
    \        while ((1 << depth) <= n) depth++;\n        val.resize(depth);\n    \
    \    val[0] = v;\n        for (int i = 1; i < depth; i++){\n            val[i].resize(n);\n\
    \            for (int j = 0; j <= n - (1 << i); j++){\n                val[i][j]\
    \ = op(val[i - 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n      \
    \  }\n    }\n    Sparse_table(std::vector<T> v){\n        init(v);\n    }\n  \
    \  Sparse_table(){}\n    // 0 <= l < r <= n\n    // if l == r : assert\n    T\
    \ prod(int l, int r){\n        assert(0 <= l && l < r && r <= n);\n        int\
    \ z=31-__builtin_clz(r-l);\n        return op(val[z][l], val[z][r - (1 << z)]);\n\
    \    }\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: ds/Sparse_table.hpp
  requiredBy:
  - graph/tree/Auxiliary_Tree.hpp
  - graph/tree/LCA.hpp
  timestamp: '2025-01-11 23:26:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ds/sparse_table.test.cpp
  - test/graph/tree/jump_tree.test.cpp
  - test/graph/tree/lca_1.test.cpp
documentation_of: ds/Sparse_table.hpp
layout: document
redirect_from:
- /library/ds/Sparse_table.hpp
- /library/ds/Sparse_table.hpp.html
title: ds/Sparse_table.hpp
---
