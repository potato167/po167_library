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
    - https://atcoder.jp/contests/arc153/tasks/arc153_d
    - https://codeforces.com/contest/1188/problem/D
  bundledCode: "#line 1 \"no_test/minimize_digit_sum.hpp\"\nnamespace po167{\n// min\
    \ sum_{i} digit_sum(A[i]+x) (base D)\n// st 0<=x,A[i]\n//    D>=2\n// O(ND log_{D}{max(A)})\
    \ ?\n// arc153_d\nusing ans_ty=long long;\ntemplate<const int D,class F>\nans_ty\
    \ Minimize_sum_of_digit_sums(\n    std::vector<F> A\n){\n    const ans_ty INF_=1e15;\n\
    \    int N=A.size();\n    std::vector<ans_ty> res(N+1,INF_),n_res(N+1);\n    std::vector<F>\
    \ n_A(N);\n    std::vector<int> rem(N);\n    res[0]=0;\n    bool ok=1;\n    while(ok){\n\
    \        ok=0;\n        int ind=0;\n        ans_ty val=0;\n        for(int i=0;i<N;i++){\n\
    \            if(A[i]) ok=1;\n            rem[i]=D-1-A[i]%D;\n            A[i]/=D;\n\
    \            val+=D-1-rem[i];\n        }\n        n_res[0]=INF_;\n        for(int\
    \ c=0;c<D;c++){\n            n_res[ind]=std::min(n_res[ind],val+res[0]);\n   \
    \         for(int i=0;i<N;i++){\n                if(rem[i]==c){\n            \
    \        val-=D;\n                    n_A[ind]=A[i];\n                    ind++;\n\
    \                    n_res[ind]=INF_;\n                }\n                val++;\n\
    \                n_res[ind]=std::min(n_res[ind],val+res[i+1]);\n            }\n\
    \        }\n        std::swap(n_A,A);\n        std::swap(n_res,res);\n    }\n\
    \    return res[0];\n}\n}\n/*\n//https://atcoder.jp/contests/arc153/tasks/arc153_d\n\
    void arc153d(){\n    int N;\n    std::cin>>N;\n    std::vector<int> A(N);\n  \
    \  for(int i=0;i<N;i++) std::cin>>A[i];\n    std::cout<<po167::Minimize_sum_of_digit_sums<10>(A)<<\"\
    \\n\";\n}\n*/\n\n/*\n// Div1 572 D\n//https://codeforces.com/contest/1188/problem/D\n\
    void div1_572_D(){\n    int N;\n    std::cin>>N;\n    std::vector<long long> A(N);\n\
    \    long long M=0;\n    for(int i=0;i<N;i++) std::cin>>A[i],M=std::max(M,A[i]);\n\
    \    for(int i=0;i<N;i++) A[i]=M-A[i];\n    std::cout<<po167::Minimize_sum_of_digit_sums<2>(A)<<\"\
    \\n\";\n}\n*/\n"
  code: "namespace po167{\n// min sum_{i} digit_sum(A[i]+x) (base D)\n// st 0<=x,A[i]\n\
    //    D>=2\n// O(ND log_{D}{max(A)}) ?\n// arc153_d\nusing ans_ty=long long;\n\
    template<const int D,class F>\nans_ty Minimize_sum_of_digit_sums(\n    std::vector<F>\
    \ A\n){\n    const ans_ty INF_=1e15;\n    int N=A.size();\n    std::vector<ans_ty>\
    \ res(N+1,INF_),n_res(N+1);\n    std::vector<F> n_A(N);\n    std::vector<int>\
    \ rem(N);\n    res[0]=0;\n    bool ok=1;\n    while(ok){\n        ok=0;\n    \
    \    int ind=0;\n        ans_ty val=0;\n        for(int i=0;i<N;i++){\n      \
    \      if(A[i]) ok=1;\n            rem[i]=D-1-A[i]%D;\n            A[i]/=D;\n\
    \            val+=D-1-rem[i];\n        }\n        n_res[0]=INF_;\n        for(int\
    \ c=0;c<D;c++){\n            n_res[ind]=std::min(n_res[ind],val+res[0]);\n   \
    \         for(int i=0;i<N;i++){\n                if(rem[i]==c){\n            \
    \        val-=D;\n                    n_A[ind]=A[i];\n                    ind++;\n\
    \                    n_res[ind]=INF_;\n                }\n                val++;\n\
    \                n_res[ind]=std::min(n_res[ind],val+res[i+1]);\n            }\n\
    \        }\n        std::swap(n_A,A);\n        std::swap(n_res,res);\n    }\n\
    \    return res[0];\n}\n}\n/*\n//https://atcoder.jp/contests/arc153/tasks/arc153_d\n\
    void arc153d(){\n    int N;\n    std::cin>>N;\n    std::vector<int> A(N);\n  \
    \  for(int i=0;i<N;i++) std::cin>>A[i];\n    std::cout<<po167::Minimize_sum_of_digit_sums<10>(A)<<\"\
    \\n\";\n}\n*/\n\n/*\n// Div1 572 D\n//https://codeforces.com/contest/1188/problem/D\n\
    void div1_572_D(){\n    int N;\n    std::cin>>N;\n    std::vector<long long> A(N);\n\
    \    long long M=0;\n    for(int i=0;i<N;i++) std::cin>>A[i],M=std::max(M,A[i]);\n\
    \    for(int i=0;i<N;i++) A[i]=M-A[i];\n    std::cout<<po167::Minimize_sum_of_digit_sums<2>(A)<<\"\
    \\n\";\n}\n*/"
  dependsOn: []
  isVerificationFile: false
  path: no_test/minimize_digit_sum.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/minimize_digit_sum.hpp
layout: document
redirect_from:
- /library/no_test/minimize_digit_sum.hpp
- /library/no_test/minimize_digit_sum.hpp.html
title: no_test/minimize_digit_sum.hpp
---
