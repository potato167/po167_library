---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1856/problem/E2
    - https://codeforces.com/contest/1856/submission/219130190
  bundledCode: "#line 1 \"no_test/subset_1.hpp\"\n\n// S=sum(p)\n// O(S*sqrt(S)/w)\n\
    // s.t\n// S<_max_len(=1e6+1)\n// 0<=p[i]\n\n//\u30A2\u30F3\u30C0\u30FC\u30D0\u30FC\
    \u3092\u5148\u982D\u306B\u3059\u308B\u306E\u306F\u3084\u3070\u3044\u3089\u3057\
    \u3044\n\n//https://codeforces.com/contest/1856/problem/E2\n//https://codeforces.com/contest/1856/submission/219130190\n\
    #include<vector>\nconst int _max_len=4e6+1;\ntemplate<int _len=1>\nstd::vector<bool>\
    \ fast_subset_sub_solver(std::vector<int> &p,int sum=-1){\n    if(sum==-1){\n\
    \        sum=0;\n        for(auto x:p){\n            assert(x>=0);\n         \
    \   sum+=x;\n        }\n    }\n    assert(sum<=_max_len);\n    if(sum>=_len){\n\
    \        return fast_subset_sub_solver<std::min(_max_len,2*_len)>(p,sum);\n  \
    \  }\n    for(auto x:p) assert(x>=0);\n    std::bitset<_len> dp;\n    std::vector<int>\
    \ q(sum+1);\n    for(auto x:p) q[x]++;\n    dp[0]=1;\n    for(int i=1;i<=sum;i++){\n\
    \        if(q[i]>=1){\n            if(0==(q[i]&1)) q[i]--,dp=(dp|(dp<<i));\n \
    \           q[i]--,dp=(dp|(dp<<i));\n            if(i*2<=sum&&2<=q[i]) q[i*2]+=q[i]/2;\n\
    \        }\n    }\n    std::vector<bool> res(sum+1);\n    for(int i=0;i<=sum;i++)\
    \ res[i]=dp[i];\n    return res;\n}\n"
  code: "\n// S=sum(p)\n// O(S*sqrt(S)/w)\n// s.t\n// S<_max_len(=1e6+1)\n// 0<=p[i]\n\
    \n//\u30A2\u30F3\u30C0\u30FC\u30D0\u30FC\u3092\u5148\u982D\u306B\u3059\u308B\u306E\
    \u306F\u3084\u3070\u3044\u3089\u3057\u3044\n\n//https://codeforces.com/contest/1856/problem/E2\n\
    //https://codeforces.com/contest/1856/submission/219130190\n#include<vector>\n\
    const int _max_len=4e6+1;\ntemplate<int _len=1>\nstd::vector<bool> fast_subset_sub_solver(std::vector<int>\
    \ &p,int sum=-1){\n    if(sum==-1){\n        sum=0;\n        for(auto x:p){\n\
    \            assert(x>=0);\n            sum+=x;\n        }\n    }\n    assert(sum<=_max_len);\n\
    \    if(sum>=_len){\n        return fast_subset_sub_solver<std::min(_max_len,2*_len)>(p,sum);\n\
    \    }\n    for(auto x:p) assert(x>=0);\n    std::bitset<_len> dp;\n    std::vector<int>\
    \ q(sum+1);\n    for(auto x:p) q[x]++;\n    dp[0]=1;\n    for(int i=1;i<=sum;i++){\n\
    \        if(q[i]>=1){\n            if(0==(q[i]&1)) q[i]--,dp=(dp|(dp<<i));\n \
    \           q[i]--,dp=(dp|(dp<<i));\n            if(i*2<=sum&&2<=q[i]) q[i*2]+=q[i]/2;\n\
    \        }\n    }\n    std::vector<bool> res(sum+1);\n    for(int i=0;i<=sum;i++)\
    \ res[i]=dp[i];\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: no_test/subset_1.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/subset_1.hpp
layout: document
redirect_from:
- /library/no_test/subset_1.hpp
- /library/no_test/subset_1.hpp.html
title: no_test/subset_1.hpp
---
