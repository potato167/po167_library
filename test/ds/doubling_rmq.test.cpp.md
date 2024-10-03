---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/Doubling.hpp
    title: ds/Doubling.hpp
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
  bundledCode: "#line 1 \"test/ds/doubling_rmq.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
    \n\n#line 2 \"ds/Doubling.hpp\"\n#include <vector>\n#include <cassert>\nnamespace\
    \ po167{\n\ntemplate<class T, T(*op)(T, T)>\nstruct Doubling_op{\n    struct result{\n\
    \        long long times;\n        int ind;\n        T val;\n    };\n    int n;\n\
    \    int depth;\n    std::vector<std::vector<int>> index;\n    std::vector<std::vector<T>>\
    \ val;\n    Doubling_op(std::vector<int> p, std::vector<T> v, long long lim =\
    \ (1ll << 60) - 1){\n        n = p.size();\n        for (auto x : p) assert(0\
    \ <= x && x < n);\n        assert(n == (int)v.size());\n        depth = 1;\n \
    \       while ((1ll << depth) <= lim) depth++;\n        index.resize(depth);\n\
    \        val.resize(depth);\n        index[0] = p;\n        val[0] = v;\n    \
    \    for (int i = 1; i < depth; i++){\n            index[i].resize(n);\n     \
    \       val[i].resize(n);\n            for (int j = 0; j < n; j++){\n        \
    \        int tmp = index[i - 1][j];\n                index[i][j] = index[i - 1][tmp];\n\
    \                val[i][j] = op(val[i - 1][j], val[i - 1][tmp]);\n           \
    \ }\n        }\n    }\n    result query(int start_ind, T start_val, long long\
    \ times){\n        assert(0 <= start_ind && start_ind < n);\n        assert(0\
    \ <= times && times < (1ll << depth));\n        int i = 0;\n        long long\
    \ TIMES = times;\n        while (times){\n            if (times & 1){\n      \
    \          start_val = op(start_val, val[i][start_ind]);\n                start_ind\
    \ = index[i][start_ind];\n            }\n            i++;\n            times >>=\
    \ 1;\n        }\n        return {TIMES, start_ind, start_val};\n    }\n    result\
    \ max_right(int start_ind, T start_val, auto f){\n        if (!f(start_val)) return\
    \ {-1, start_ind, start_val};\n        long long times = 0;\n        for (int\
    \ d = depth - 1; d >= 0; d--){\n            if (f(op(start_val, val[d][start_ind]))){\n\
    \                start_val = op(start_val, val[d][start_ind]);\n             \
    \   start_ind = index[d][start_ind];\n                times += (1ll << d);\n \
    \           }\n        }\n        return {times, start_ind, start_val};\n    }\n\
    };\n\nstruct Doubling{\n    int n;\n    int depth;\n    std::vector<std::vector<int>>\
    \ index;\n    Doubling(std::vector<int> p, long long lim = (1ll << 60) - 1){\n\
    \        n = p.size();\n        for (auto x : p) assert(0 <= x && x < n);\n  \
    \      depth = 1;\n        while ((1ll << depth) <= lim) depth++;\n        index.resize(depth);\n\
    \        index[0] = p;\n        for (int i = 1; i < depth; i++){\n           \
    \ index[i].resize(n);\n            for (int j = 0; j < n; j++){\n            \
    \    index[i][j] = index[i - 1][index[i - 1][j]];\n            }\n        }\n\
    \    }\n    int query(int ind, long long times){\n        assert(0 <= ind && ind\
    \ < n);\n        assert(0 <= times && times < (1ll << depth));\n        int i\
    \ = 0;\n        while (times){\n            if (times & 1) ind = index[i][ind];\n\
    \            i++;\n            times >>= 1;\n        }\n        return ind;\n\
    \    }\n};\n}\n#line 4 \"test/ds/doubling_rmq.test.cpp\"\n\nint op(int a, int\
    \ b){\n    return std::min(a, b);\n}\n\n#include <iostream>\n\nint main(){\n \
    \   std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int N,\
    \ Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N), P(N);\n    for (int\
    \ i = 0; i < N; i++){\n        std::cin >> A[i];\n        P[i] = std::min(i +\
    \ 1, N - 1);\n    }\n    po167::Doubling_op<int, op> D(P, A, N);\n    while (Q--){\n\
    \        int l, r;\n        std::cin >> l >> r;\n        std::cout << D.query(l,\
    \ 1 << 30, r - l).val << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../ds/Doubling.hpp\"\n\nint op(int a, int b){\n    return std::min(a, b);\n\
    }\n\n#include <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int>\
    \ A(N), P(N);\n    for (int i = 0; i < N; i++){\n        std::cin >> A[i];\n \
    \       P[i] = std::min(i + 1, N - 1);\n    }\n    po167::Doubling_op<int, op>\
    \ D(P, A, N);\n    while (Q--){\n        int l, r;\n        std::cin >> l >> r;\n\
    \        std::cout << D.query(l, 1 << 30, r - l).val << \"\\n\";\n    }\n}"
  dependsOn:
  - ds/Doubling.hpp
  isVerificationFile: true
  path: test/ds/doubling_rmq.test.cpp
  requiredBy: []
  timestamp: '2024-10-04 03:24:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ds/doubling_rmq.test.cpp
layout: document
redirect_from:
- /verify/test/ds/doubling_rmq.test.cpp
- /verify/test/ds/doubling_rmq.test.cpp.html
title: test/ds/doubling_rmq.test.cpp
---
