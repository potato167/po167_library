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
    - https://atcoder.jp/contests/abc326/submissions/47072566
    - https://atcoder.jp/contests/abc326/tasks/abc326_f
  bundledCode: "#line 1 \"no_test/subset_2.hpp\"\n\nnamespace po167{\n// N = len (v)\n\
    // s.t N<64\n// O(2^{N/2})\n// ex if v[2]+v[3]+v[5] = S\n// return 4+8+32\n//\
    \ https://atcoder.jp/contests/abc326/tasks/abc326_f\n\ntemplate<class T>\nstd::vector<std::pair<T,long\
    \ long>> fsss2_sub(std::vector<T> v){\n    int N=v.size();\n    std::vector<std::pair<T,long\
    \ long>> res={{0,0}};\n    for(int i=0;i<N;i++){\n        std::vector<std::pair<T,long\
    \ long>> n_res(1<<(i+1));\n        int l1=0,l2=0;\n        for(int j=0;j<(1<<(i+1));j++){\n\
    \            if(l1==(int)res.size()) n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];\n\
    \            else if(l2==(int)res.size()) n_res[j]=res[l1],l1++;\n           \
    \ else if(res[l1].first<=res[l2].first+v[i]) n_res[j]=res[l1],l1++;\n        \
    \    else n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];\n\
    \        }\n        swap(n_res,res);\n    }\n    return res;\n}\n\ntemplate<class\
    \ T>\nlong long fast_subset_sub_solver_2(std::vector<T> v,T S){\n    int N=v.size();\n\
    \    std::vector<T> X(N/2),Y((N+1)/2);\n    for(int i=0;i<N/2;i++) X[i]=v[i];\n\
    \    for(int i=N/2;i<N;i++) Y[i-N/2]=v[i];\n    auto A=fsss2_sub(X);\n    auto\
    \ B=fsss2_sub(Y);\n    int r=(int)B.size()-1;\n    for(int l=0;l<(int)A.size();l++){\n\
    \        while(r!=0&&A[l].first+B[r].first>S) r--;\n        if(S==A[l].first+B[r].first){\n\
    \            return A[l].second+(B[r].second<<(N/2));\n        }\n    }\n    return\
    \ -1;\n}\n}\n\n// https://atcoder.jp/contests/abc326/submissions/47072566\nvoid\
    \ abc326f(){\n    int N,X,Y;\n    std::cin>>N>>X>>Y;\n    std::vector<int> A(N),D(N+1),S={X,Y};\n\
    \    for(int i=0;i<N;i++) std::cin>>A[i];\n    for(int i=0;i<2;i++){\n       \
    \ std::vector<int> B((N+i)/2);\n        for(int j=0;j<N;j++) if((i+j)&1){\n  \
    \          B[j>>1]=A[j]*2;\n            S[i]+=A[j];\n        }\n        auto res=po167::fast_subset_sub_solver_2(B,S[i]);\n\
    \        if(res==-1){\n            std::cout<<\"No\\n\";\n            return;\n\
    \        }\n        for(int j=0;j<(N+i)/2;j++){\n            if(res&(1ll<<j))\
    \ D[j*2+2-i]=i;\n            else D[j*2+2-i]=i+2;\n        }\n    }\n    std::cout<<\"\
    Yes\\n\";\n    for(int i=0;i<N;i++){\n        std::cout<<(((D[i+1]-D[i]+4)&2)?'R':'L');\n\
    \    }\n    std::cout<<'\\n';\n}\n"
  code: "\nnamespace po167{\n// N = len (v)\n// s.t N<64\n// O(2^{N/2})\n// ex if\
    \ v[2]+v[3]+v[5] = S\n// return 4+8+32\n// https://atcoder.jp/contests/abc326/tasks/abc326_f\n\
    \ntemplate<class T>\nstd::vector<std::pair<T,long long>> fsss2_sub(std::vector<T>\
    \ v){\n    int N=v.size();\n    std::vector<std::pair<T,long long>> res={{0,0}};\n\
    \    for(int i=0;i<N;i++){\n        std::vector<std::pair<T,long long>> n_res(1<<(i+1));\n\
    \        int l1=0,l2=0;\n        for(int j=0;j<(1<<(i+1));j++){\n            if(l1==(int)res.size())\
    \ n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];\n      \
    \      else if(l2==(int)res.size()) n_res[j]=res[l1],l1++;\n            else if(res[l1].first<=res[l2].first+v[i])\
    \ n_res[j]=res[l1],l1++;\n            else n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];\n\
    \        }\n        swap(n_res,res);\n    }\n    return res;\n}\n\ntemplate<class\
    \ T>\nlong long fast_subset_sub_solver_2(std::vector<T> v,T S){\n    int N=v.size();\n\
    \    std::vector<T> X(N/2),Y((N+1)/2);\n    for(int i=0;i<N/2;i++) X[i]=v[i];\n\
    \    for(int i=N/2;i<N;i++) Y[i-N/2]=v[i];\n    auto A=fsss2_sub(X);\n    auto\
    \ B=fsss2_sub(Y);\n    int r=(int)B.size()-1;\n    for(int l=0;l<(int)A.size();l++){\n\
    \        while(r!=0&&A[l].first+B[r].first>S) r--;\n        if(S==A[l].first+B[r].first){\n\
    \            return A[l].second+(B[r].second<<(N/2));\n        }\n    }\n    return\
    \ -1;\n}\n}\n\n// https://atcoder.jp/contests/abc326/submissions/47072566\nvoid\
    \ abc326f(){\n    int N,X,Y;\n    std::cin>>N>>X>>Y;\n    std::vector<int> A(N),D(N+1),S={X,Y};\n\
    \    for(int i=0;i<N;i++) std::cin>>A[i];\n    for(int i=0;i<2;i++){\n       \
    \ std::vector<int> B((N+i)/2);\n        for(int j=0;j<N;j++) if((i+j)&1){\n  \
    \          B[j>>1]=A[j]*2;\n            S[i]+=A[j];\n        }\n        auto res=po167::fast_subset_sub_solver_2(B,S[i]);\n\
    \        if(res==-1){\n            std::cout<<\"No\\n\";\n            return;\n\
    \        }\n        for(int j=0;j<(N+i)/2;j++){\n            if(res&(1ll<<j))\
    \ D[j*2+2-i]=i;\n            else D[j*2+2-i]=i+2;\n        }\n    }\n    std::cout<<\"\
    Yes\\n\";\n    for(int i=0;i<N;i++){\n        std::cout<<(((D[i+1]-D[i]+4)&2)?'R':'L');\n\
    \    }\n    std::cout<<'\\n';\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/subset_2.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/subset_2.hpp
layout: document
redirect_from:
- /library/no_test/subset_2.hpp
- /library/no_test/subset_2.hpp.html
title: no_test/subset_2.hpp
---
