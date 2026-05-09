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
  bundledCode: "#line 1 \"no_test/mobius.hpp\"\n//Mobius(n)= 0  exists p n|p*p\n//\
    \         =-1  if n=p_1*p_2*...*p_{2a+1}\n//         = 1  if n=p_1*p_2*...*p_{2a}\n\
    std::vector<int> Mobius(int N){\n    std::vector<int> p(N+1,-2);\n    p[1]=1;\n\
    \    for(int i=2;i<=N;i++){\n        if(p[i]!=-2) continue;\n        p[i]=-1;\n\
    \        for(int j=i*2;j<=N;j+=i){\n            if(p[j]==-2) p[j]=-1;\n      \
    \      else p[j]*=-1;\n        }\n        if(N/i<i) continue;\n        for(int\
    \ j=i*i;j<=N;j+=i*i) p[j]=0;\n    }\n    for(int i=1;i<=N;i++){\n        if(p[i]==-2)\
    \ p[i]=-1;\n    }\n    return p;\n}\n"
  code: "//Mobius(n)= 0  exists p n|p*p\n//         =-1  if n=p_1*p_2*...*p_{2a+1}\n\
    //         = 1  if n=p_1*p_2*...*p_{2a}\nstd::vector<int> Mobius(int N){\n   \
    \ std::vector<int> p(N+1,-2);\n    p[1]=1;\n    for(int i=2;i<=N;i++){\n     \
    \   if(p[i]!=-2) continue;\n        p[i]=-1;\n        for(int j=i*2;j<=N;j+=i){\n\
    \            if(p[j]==-2) p[j]=-1;\n            else p[j]*=-1;\n        }\n  \
    \      if(N/i<i) continue;\n        for(int j=i*i;j<=N;j+=i*i) p[j]=0;\n    }\n\
    \    for(int i=1;i<=N;i++){\n        if(p[i]==-2) p[i]=-1;\n    }\n    return\
    \ p;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/mobius.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/mobius.hpp
layout: document
redirect_from:
- /library/no_test/mobius.hpp
- /library/no_test/mobius.hpp.html
title: no_test/mobius.hpp
---
