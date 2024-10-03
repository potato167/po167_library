---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/doubling_rmq.test.cpp
    title: test/ds/doubling_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Doubling.hpp\"\n#include <vector>\n#include <cassert>\n\
    namespace po167{\n\ntemplate<class T, T(*op)(T, T)>\nstruct Doubling_op{\n   \
    \ struct result{\n        long long times;\n        int ind;\n        T val;\n\
    \    };\n    int n;\n    int depth;\n    std::vector<std::vector<int>> index;\n\
    \    std::vector<std::vector<T>> val;\n    Doubling_op(std::vector<int> p, std::vector<T>\
    \ v, long long lim = (1ll << 60) - 1){\n        n = p.size();\n        for (auto\
    \ x : p) assert(0 <= x && x < n);\n        assert(n == (int)v.size());\n     \
    \   depth = 1;\n        while ((1ll << depth) <= lim) depth++;\n        index.resize(depth);\n\
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
    \    }\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\nnamespace po167{\n\n\
    template<class T, T(*op)(T, T)>\nstruct Doubling_op{\n    struct result{\n   \
    \     long long times;\n        int ind;\n        T val;\n    };\n    int n;\n\
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
    \    }\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/Doubling.hpp
  requiredBy: []
  timestamp: '2024-10-04 03:24:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ds/doubling_rmq.test.cpp
documentation_of: ds/Doubling.hpp
layout: document
redirect_from:
- /library/ds/Doubling.hpp
- /library/ds/Doubling.hpp.html
title: ds/Doubling.hpp
---
