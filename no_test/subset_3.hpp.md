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
  bundledCode: "#line 1 \"no_test/subset_3.hpp\"\n// subset sum\n// input vector<int>\
    \ A, int B\n// return t\n// s.t : t[i] \\in {0, 1}\n// s.t : B = \\sum A[i] *\
    \ t[i]\n// O(|A| \\max(A))\nstd::vector<int> subset_sum(std::vector<int> A, int\
    \ B){\n    int ma = 0;\n    int n = (int)A.size();\n    for (auto a : A) ma =\
    \ std::max(ma, a);\n    int si = 0;\n    while (si != n && B >= A[si]) B -= A[si++];\n\
    \    if (si == n && B > 0) return {};\n    std::vector dp(n - si + 1, std::vector<int>(ma\
    \ * 2 + 1, -1));\n    dp[0][B] = si;\n    for (int i = 0; i < n - si; i++){\n\
    \        // unuse left value\n        for (int j = 0; j <= ma * 2; j++){\n   \
    \         for (int k = dp[i][j] - 1; k >= (i == 0 ? 0 : std::max(0, dp[i - 1][j]));\
    \ k--){\n                if (j + A[k] <= ma * 2){\n                    dp[i][j\
    \ + A[k]] = std::max(dp[i][j + A[k]], k);\n                }\n            }\n\
    \        }\n        // use A[i + si]\n        dp[i + 1] = dp[i];\n        for\
    \ (int j = A[i + si]; j <= ma * 2; j++){\n            dp[i + 1][j - A[i + si]]\
    \ = std::max(dp[i + 1][j - A[i + si]], dp[i + 1][j]);\n        }\n    }\n    if\
    \ (dp[n - si][0] == -1) return {};\n    std::vector<int> res(n);\n    for (int\
    \ i = 0; i < si; i++) res[i] = 1;\n    int x = n - si, y = 0;\n    while (x !=\
    \ 0 || y != B){\n        int j = dp[x][y];\n        if (j != si && A[j] <= y &&\
    \ dp[x][y - A[j]] > j){\n            res[j] ^= 1;\n            y -= A[j];\n  \
    \      }\n        else{\n            x--;\n            if (dp[x][y] != j){\n \
    \               res[x + si] ^= 1;\n                y += A[x + si];\n         \
    \   }\n        }\n    }\n    return res;\n}\n"
  code: "// subset sum\n// input vector<int> A, int B\n// return t\n// s.t : t[i]\
    \ \\in {0, 1}\n// s.t : B = \\sum A[i] * t[i]\n// O(|A| \\max(A))\nstd::vector<int>\
    \ subset_sum(std::vector<int> A, int B){\n    int ma = 0;\n    int n = (int)A.size();\n\
    \    for (auto a : A) ma = std::max(ma, a);\n    int si = 0;\n    while (si !=\
    \ n && B >= A[si]) B -= A[si++];\n    if (si == n && B > 0) return {};\n    std::vector\
    \ dp(n - si + 1, std::vector<int>(ma * 2 + 1, -1));\n    dp[0][B] = si;\n    for\
    \ (int i = 0; i < n - si; i++){\n        // unuse left value\n        for (int\
    \ j = 0; j <= ma * 2; j++){\n            for (int k = dp[i][j] - 1; k >= (i ==\
    \ 0 ? 0 : std::max(0, dp[i - 1][j])); k--){\n                if (j + A[k] <= ma\
    \ * 2){\n                    dp[i][j + A[k]] = std::max(dp[i][j + A[k]], k);\n\
    \                }\n            }\n        }\n        // use A[i + si]\n     \
    \   dp[i + 1] = dp[i];\n        for (int j = A[i + si]; j <= ma * 2; j++){\n \
    \           dp[i + 1][j - A[i + si]] = std::max(dp[i + 1][j - A[i + si]], dp[i\
    \ + 1][j]);\n        }\n    }\n    if (dp[n - si][0] == -1) return {};\n    std::vector<int>\
    \ res(n);\n    for (int i = 0; i < si; i++) res[i] = 1;\n    int x = n - si, y\
    \ = 0;\n    while (x != 0 || y != B){\n        int j = dp[x][y];\n        if (j\
    \ != si && A[j] <= y && dp[x][y - A[j]] > j){\n            res[j] ^= 1;\n    \
    \        y -= A[j];\n        }\n        else{\n            x--;\n            if\
    \ (dp[x][y] != j){\n                res[x + si] ^= 1;\n                y += A[x\
    \ + si];\n            }\n        }\n    }\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: no_test/subset_3.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/subset_3.hpp
layout: document
redirect_from:
- /library/no_test/subset_3.hpp
- /library/no_test/subset_3.hpp.html
title: no_test/subset_3.hpp
---
