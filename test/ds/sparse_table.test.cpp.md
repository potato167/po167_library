---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/Sparse_table.hpp
    title: ds/Sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/ds/sparse_table.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
    \n#line 2 \"ds/Sparse_table.hpp\"\n#include <vector>\n#include <cassert>\nnamespace\
    \ po167{\ntemplate<class T, T(*op)(T, T)>\nstruct Sparse_table{\n    int n;\n\
    \    int depth;\n    std::vector<std::vector<T>> val;\n    void init(std::vector<T>\
    \ &v){\n        depth = 1;\n        n = v.size();\n        while ((1 << depth)\
    \ <= n) depth++;\n        val.resize(depth);\n        val[0] = v;\n        for\
    \ (int i = 1; i < depth; i++){\n            val[i].resize(n);\n            for\
    \ (int j = 0; j <= n - (1 << i); j++){\n                val[i][j] = op(val[i -\
    \ 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n    }\n \
    \   Sparse_table(std::vector<T> v){\n        init(v);\n    }\n    Sparse_table(){}\n\
    \    // 0 <= l < r <= n\n    // if l == r : assert\n    T prod(int l, int r){\n\
    \        assert(0 <= l && l < r && r <= n);\n        int z=31-__builtin_clz(r-l);\n\
    \        return op(val[z][l], val[z][r - (1 << z)]);\n    }\n};\n}\n#line 3 \"\
    test/ds/sparse_table.test.cpp\"\n#include <iostream>\n\nint op(int a, int b){\n\
    \    return std::min(a, b);\n}\n\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int>\
    \ A(N);\n    for (auto &a : A) std::cin >> a;\n    po167::Sparse_table<int, op>\
    \ table(A);\n    while (Q--){\n        int l, r;\n        std::cin >> l >> r;\n\
    \        std::cout << table.prod(l, r) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    ../../ds/Sparse_table.hpp\"\n#include <iostream>\n\nint op(int a, int b){\n  \
    \  return std::min(a, b);\n}\n\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int>\
    \ A(N);\n    for (auto &a : A) std::cin >> a;\n    po167::Sparse_table<int, op>\
    \ table(A);\n    while (Q--){\n        int l, r;\n        std::cin >> l >> r;\n\
    \        std::cout << table.prod(l, r) << \"\\n\";\n    }\n}"
  dependsOn:
  - ds/Sparse_table.hpp
  isVerificationFile: true
  path: test/ds/sparse_table.test.cpp
  requiredBy: []
  timestamp: '2025-01-11 23:26:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ds/sparse_table.test.cpp
layout: document
redirect_from:
- /verify/test/ds/sparse_table.test.cpp
- /verify/test/ds/sparse_table.test.cpp.html
title: test/ds/sparse_table.test.cpp
---
