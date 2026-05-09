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
  bundledCode: "#line 1 \"no_test/candy.hpp\"\nvector<ll> candy(vector<ll> v, int\
    \ K){\n    int N = v.size();\n    vector<int> L(N), R(N);\n    rep(i, 0, N) L[i]\
    \ = i - 1, R[i] = i + 1;\n    auto del = [&](int ind) -> void {\n        if (ind\
    \ == -1 || ind == N) return;\n        if (L[ind] == -1){\n            if (R[ind]\
    \ != N) L[R[ind]] = -1;\n        }\n        else{\n            if (R[ind] == N)\
    \ R[L[ind]] = N;\n            else{\n                int l = L[ind];\n       \
    \         int r = R[ind];\n                R[l] = r;\n                L[r] = l;\n\
    \            }\n        }\n        R[ind] = -1;\n    };\n    vector<ll> ans =\
    \ {0};\n    priority_queue<pair<ll, int>> pq;\n    rep(i, 0, N) pq.push({v[i],\
    \ i});\n    rep(rp, 0, (N + 1) / 2){\n    \tif ((int)ans.size() > K) break;\n\
    \        while (true){\n            auto [val, ind] = pq.top();\n            pq.pop();\n\
    \            if (R[ind] == -1 || v[ind] != val){\n                continue;\n\
    \            }\n            ans.push_back(ans.back() + val);\n            int\
    \ l = L[ind];\n            int r = R[ind];\n            del(ind);\n          \
    \  if (l == -1 || r == N){\n                del(l), del(r);\n            }\n \
    \           else{\n                del(r);\n                v[l] = v[l] - v[ind]\
    \ + v[r];\n                pq.push({v[l], l});\n            }\n            break;\n\
    \        }\n    }\n    return ans;\n}\n"
  code: "vector<ll> candy(vector<ll> v, int K){\n    int N = v.size();\n    vector<int>\
    \ L(N), R(N);\n    rep(i, 0, N) L[i] = i - 1, R[i] = i + 1;\n    auto del = [&](int\
    \ ind) -> void {\n        if (ind == -1 || ind == N) return;\n        if (L[ind]\
    \ == -1){\n            if (R[ind] != N) L[R[ind]] = -1;\n        }\n        else{\n\
    \            if (R[ind] == N) R[L[ind]] = N;\n            else{\n            \
    \    int l = L[ind];\n                int r = R[ind];\n                R[l] =\
    \ r;\n                L[r] = l;\n            }\n        }\n        R[ind] = -1;\n\
    \    };\n    vector<ll> ans = {0};\n    priority_queue<pair<ll, int>> pq;\n  \
    \  rep(i, 0, N) pq.push({v[i], i});\n    rep(rp, 0, (N + 1) / 2){\n    \tif ((int)ans.size()\
    \ > K) break;\n        while (true){\n            auto [val, ind] = pq.top();\n\
    \            pq.pop();\n            if (R[ind] == -1 || v[ind] != val){\n    \
    \            continue;\n            }\n            ans.push_back(ans.back() +\
    \ val);\n            int l = L[ind];\n            int r = R[ind];\n          \
    \  del(ind);\n            if (l == -1 || r == N){\n                del(l), del(r);\n\
    \            }\n            else{\n                del(r);\n                v[l]\
    \ = v[l] - v[ind] + v[r];\n                pq.push({v[l], l});\n            }\n\
    \            break;\n        }\n    }\n    return ans;\n}"
  dependsOn: []
  isVerificationFile: false
  path: no_test/candy.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/candy.hpp
layout: document
redirect_from:
- /library/no_test/candy.hpp
- /library/no_test/candy.hpp.html
title: no_test/candy.hpp
---
