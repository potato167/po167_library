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
    - https://onlinejudge.u-aizu.ac.jp/status/users/potato167/submissions/1/GRL_3_A/judge/6651994/C++17
  bundledCode: "#line 1 \"no_test/low_link.hpp\"\nnamespace po167{\nstd::vector<std::vector<int>>\
    \ Lowlink(std::vector<std::vector<int>> &G){\n    int n=G.size();\n    std::vector<std::vector<int>>\
    \ p(2,std::vector<int>(n,-1));\n    std::vector<int> front(n);\n    int k=1;\n\
    \    std::vector<int> ind(n);\n    std::stack<int> s;\n    s.push(0);p[0][0]=0,p[1][0]=0;\n\
    \    while(!s.empty()){\n        int a=s.top();\n        while(true){\n      \
    \      if(ind[a]==(int)(G[a].size())){\n                p[1][front[a]]=std::min(p[1][front[a]],p[1][a]);\n\
    \                s.pop();\n                break;\n            }\n           \
    \ int b=G[a][ind[a]];\n            ind[a]++;\n            if(p[0][b]==-1){\n \
    \               p[0][b]=k;\n                p[1][b]=k;\n                front[b]=a;\n\
    \                k++;\n                s.push(b);\n                break;\n  \
    \          }\n            else if(front[a]!=b){\n                if(p[1][a]>p[0][b])\
    \ p[1][a]=p[0][b];\n            }\n        }\n    }\n    p.push_back(front);\n\
    \    return p;\n}\n\nstd::vector<std::pair<int,int>> bridges(std::vector<std::vector<int>>\
    \ G){\n    int n=G.size();\n    auto p=Lowlink(G);\n    std::vector<std::pair<int,int>>\
    \ ans;\n    for(int i=0;i<n;i++){\n        for(int j:G[i]){\n            if(p[0][i]<p[0][j]&&p[0][i]<p[1][j]){\n\
    \                ans.push_back({i,j});\n            }\n        }\n    }\n    return\
    \ ans;\n}\n//https://onlinejudge.u-aizu.ac.jp/status/users/potato167/submissions/1/GRL_3_A/judge/6651994/C++17\n\
    std::vector<int> Articulation_Points(std::vector<std::vector<int>> G){\n    int\
    \ n=G.size();\n    auto p=Lowlink(G);\n    std::vector<int> ans;\n    int tmp=0;\n\
    \    for(auto x:G[0]){\n        if(p[2][x]==0) tmp++;\n    }\n    if(tmp>=2) ans.push_back(0);\n\
    \    for(int i=1;i<n;i++){\n        for(int j:G[i]){\n            if(i==p[2][j]&&p[0][i]<=p[1][j]){\n\
    \                ans.push_back(i);\n                break;\n            }\n  \
    \      }\n    }\n    return ans;\n}\n}\n"
  code: "namespace po167{\nstd::vector<std::vector<int>> Lowlink(std::vector<std::vector<int>>\
    \ &G){\n    int n=G.size();\n    std::vector<std::vector<int>> p(2,std::vector<int>(n,-1));\n\
    \    std::vector<int> front(n);\n    int k=1;\n    std::vector<int> ind(n);\n\
    \    std::stack<int> s;\n    s.push(0);p[0][0]=0,p[1][0]=0;\n    while(!s.empty()){\n\
    \        int a=s.top();\n        while(true){\n            if(ind[a]==(int)(G[a].size())){\n\
    \                p[1][front[a]]=std::min(p[1][front[a]],p[1][a]);\n          \
    \      s.pop();\n                break;\n            }\n            int b=G[a][ind[a]];\n\
    \            ind[a]++;\n            if(p[0][b]==-1){\n                p[0][b]=k;\n\
    \                p[1][b]=k;\n                front[b]=a;\n                k++;\n\
    \                s.push(b);\n                break;\n            }\n         \
    \   else if(front[a]!=b){\n                if(p[1][a]>p[0][b]) p[1][a]=p[0][b];\n\
    \            }\n        }\n    }\n    p.push_back(front);\n    return p;\n}\n\n\
    std::vector<std::pair<int,int>> bridges(std::vector<std::vector<int>> G){\n  \
    \  int n=G.size();\n    auto p=Lowlink(G);\n    std::vector<std::pair<int,int>>\
    \ ans;\n    for(int i=0;i<n;i++){\n        for(int j:G[i]){\n            if(p[0][i]<p[0][j]&&p[0][i]<p[1][j]){\n\
    \                ans.push_back({i,j});\n            }\n        }\n    }\n    return\
    \ ans;\n}\n//https://onlinejudge.u-aizu.ac.jp/status/users/potato167/submissions/1/GRL_3_A/judge/6651994/C++17\n\
    std::vector<int> Articulation_Points(std::vector<std::vector<int>> G){\n    int\
    \ n=G.size();\n    auto p=Lowlink(G);\n    std::vector<int> ans;\n    int tmp=0;\n\
    \    for(auto x:G[0]){\n        if(p[2][x]==0) tmp++;\n    }\n    if(tmp>=2) ans.push_back(0);\n\
    \    for(int i=1;i<n;i++){\n        for(int j:G[i]){\n            if(i==p[2][j]&&p[0][i]<=p[1][j]){\n\
    \                ans.push_back(i);\n                break;\n            }\n  \
    \      }\n    }\n    return ans;\n}\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/low_link.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/low_link.hpp
layout: document
redirect_from:
- /library/no_test/low_link.hpp
- /library/no_test/low_link.hpp.html
title: no_test/low_link.hpp
---
