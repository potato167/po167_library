---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/MinCostPerfectMatching.hpp
    title: graph/MinCostPerfectMatching.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/assignment
    links:
    - https://judge.yosupo.jp/problem/assignment
  bundledCode: "#line 1 \"test/graph/min_cost_perfect_matching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#line 2 \"graph/MinCostPerfectMatching.hpp\"\
    \n#include <algorithm>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace po167{\n// Input:  n x n cost matrix a\n// Output: {min_{p in S_n}\
    \ sum_i a[i][p[i]], p}\ntemplate <class T>\nstd::pair<long long, std::vector<int>>\
    \ min_cost_perfect_matching(\n    const std::vector<std::vector<T>>& a\n) {\n\
    \    const long long INF = std::numeric_limits<long long>::max() / 4;\n    int\
    \ n = (int)a.size();\n    if (n == 0) return {0, {}};\n    if (n == 1) return\
    \ {(long long)a[0][0], {0}};\n\n    std::vector<const T*> c(n);\n    for (int\
    \ i = 0; i < n; i++) c[i] = a[i].data();\n    std::vector<int> match(n, -1), inv(n,\
    \ -1), cnt(n);\n    std::vector<long long> v(n);\n\n    // Column reduction\n\
    \    std::vector<int> bestrow(n);\n    for (int j = 0; j < n; j++) v[j] = c[0][j];\n\
    \    for (int i = 1; i < n; i++) {\n        const T* row = c[i];\n        for\
    \ (int j = 0; j < n; j++) {\n            if ((long long)row[j] < v[j]) {\n   \
    \             v[j] = row[j];\n                bestrow[j] = i;\n            }\n\
    \        }\n    }\n    for (int j = 0; j < n; j++) {\n        int i = c[j][j]\
    \ == v[j] ? j : bestrow[j];\n        cnt[i]++;\n        if (match[i] == -1) {\n\
    \            match[i] = j;\n            inv[j] = i;\n        }\n    }\n\n    //\
    \ Reduction transfer\n    for (int i = 0; i < n; i++) if (cnt[i] == 1) {\n   \
    \     long long best = INF;\n        const T* row = c[i];\n        int assigned\
    \ = match[i];\n        for (int j = 0; j < n; j++) if (j != assigned)\n      \
    \      best = std::min(best, (long long)row[j] - v[j]);\n        v[assigned] -=\
    \ best;\n    }\n\n    // Augmenting row reduction\n    for (int rep = 0; rep <\
    \ 2; rep++) {\n        for (int i = 0; i < n; i++) if (match[i] == -1) {\n   \
    \         long long u1 = INF, u2 = INF;\n            int j1 = -1;\n          \
    \  const T* row = c[i];\n            for (int j = 0; j < n; j++) {\n         \
    \       long long u = (long long)row[j] - v[j];\n                if (u < u1 ||\
    \ (u == u1 && j1 != -1 && inv[j1] != -1)) {\n                    u2 = u1;\n  \
    \                  u1 = u;\n                    j1 = j;\n                } else\
    \ {\n                    u2 = std::min(u2, u);\n                }\n          \
    \  }\n            if (u1 < u2) v[j1] -= u2 - u1;\n            if (inv[j1] != -1)\
    \ match[inv[j1]] = -1;\n            match[i] = j1;\n            inv[j1] = i;\n\
    \        }\n    }\n\n    // Shortest augmenting paths\n    std::vector<long long>\
    \ dist(n);\n    std::vector<int> pred(n), cols(n);\n    for (int j = 0; j < n;\
    \ j++) cols[j] = j;\n\n    for (int root = 0; root < n; root++) if (match[root]\
    \ == -1) {\n        const T* row = c[root];\n        for (int j = 0; j < n; j++)\
    \ {\n            dist[j] = (long long)row[j] - v[j];\n            pred[j] = root;\n\
    \        }\n        int scanned = 0, labeled = 0, last = 0, free_col = -1;\n \
    \       while (free_col == -1) {\n            if (scanned == labeled) {\n    \
    \            last = scanned;\n                long long best = dist[cols[scanned]];\n\
    \                for (int k = scanned; k < n; k++) {\n                    int\
    \ j = cols[k];\n                    if (dist[j] <= best) {\n                 \
    \       if (dist[j] < best) best = dist[j], labeled = scanned;\n             \
    \           std::swap(cols[k], cols[labeled++]);\n                    }\n    \
    \            }\n                for (int k = scanned; k < labeled; k++)\n    \
    \                if (inv[cols[k]] == -1) {\n                        free_col =\
    \ cols[k];\n                        break;\n                    }\n          \
    \      if (free_col != -1) break;\n            }\n\n            int j1 = cols[scanned++],\
    \ i = inv[j1];\n            const T* row = c[i];\n            long long prev =\
    \ dist[j1];\n            long long offset = prev - ((long long)row[j1] - v[j1]);\n\
    \            for (int k = labeled; k < n; k++) {\n                int j = cols[k];\n\
    \                long long nd = offset + (long long)row[j] - v[j];\n         \
    \       if (nd < dist[j]) {\n                    dist[j] = nd;\n             \
    \       pred[j] = i;\n                    if (nd == prev) {\n                \
    \        if (inv[j] == -1) {\n                            free_col = j;\n    \
    \                        break;\n                        }\n                 \
    \       std::swap(cols[k], cols[labeled++]);\n                    }\n        \
    \        }\n            }\n        }\n\n        for (int k = 0; k < last; k++)\
    \ {\n            int j = cols[k];\n            v[j] += dist[j] - dist[free_col];\n\
    \        }\n        while (free_col != -1) {\n            int i = pred[free_col];\n\
    \            int old = match[i];\n            match[i] = free_col;\n         \
    \   inv[free_col] = i;\n            free_col = old;\n        }\n    }\n\n    long\
    \ long sum = 0;\n    for (int i = 0; i < n; i++) sum += (long long)c[i][match[i]];\n\
    \    return {sum, std::move(match)};\n}\n}\n#line 4 \"test/graph/min_cost_perfect_matching.test.cpp\"\
    \n\n#include<iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector a(n,\
    \ std::vector<long long>(n));\n    for (int i = 0; i < n; i++){\n        for (int\
    \ j = 0; j < n; j++){\n            std::cin >> a[i][j];\n        }\n    }\n  \
    \  auto ans = po167::min_cost_perfect_matching(a);\n    std::cout << ans.first\
    \ << \"\\n\";\n    for (int i = 0; i < n; i++){\n        std::cout << ans.second[i]\
    \ << (i + 1 == n ? \"\\n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#include\
    \ \"graph/MinCostPerfectMatching.hpp\"\n\n#include<iostream>\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n;\n\
    \    std::cin >> n;\n    std::vector a(n, std::vector<long long>(n));\n    for\
    \ (int i = 0; i < n; i++){\n        for (int j = 0; j < n; j++){\n           \
    \ std::cin >> a[i][j];\n        }\n    }\n    auto ans = po167::min_cost_perfect_matching(a);\n\
    \    std::cout << ans.first << \"\\n\";\n    for (int i = 0; i < n; i++){\n  \
    \      std::cout << ans.second[i] << (i + 1 == n ? \"\\n\" : \" \");\n    }\n}"
  dependsOn:
  - graph/MinCostPerfectMatching.hpp
  isVerificationFile: true
  path: test/graph/min_cost_perfect_matching.test.cpp
  requiredBy: []
  timestamp: '2026-10-21 22:10:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/min_cost_perfect_matching.test.cpp
layout: document
redirect_from:
- /verify/test/graph/min_cost_perfect_matching.test.cpp
- /verify/test/graph/min_cost_perfect_matching.test.cpp.html
title: test/graph/min_cost_perfect_matching.test.cpp
---
