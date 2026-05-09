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
  bundledCode: "#line 1 \"no_test/undo_uf.hpp\"\nnamespace po167{\n    struct UFtree_undo{\n\
    \        int _n,ind;\n        std::vector<int> wei;\n        std::vector<int>\
    \ q;\n        int component;\n        UFtree_undo(int n):_n(n),ind(0),wei(n),component(n),par(n){\n\
    \            for(int i=0;i<n;i++){\n                wei[i]=1,par[i]=i;\n     \
    \       }\n        }\n        int undo(){\n            if(ind==0) return 0;\n\
    \            component++;\n            ind--;\n            wei[par[q[ind]]]-=wei[q[ind]];\n\
    \            par[q[ind]]=q[ind];\n            return 1;\n        }\n        void\
    \ rollback(int times){\n            int tmp=1;\n            while(tmp!=0&&times!=0){\n\
    \                tmp=undo();\n                times--;\n            }\n      \
    \  }\n        void intialize(){\n            while(ind) undo();\n        }\n \
    \       //\u6839\u3063\u3053\u3092\u8FD4\u3059\n        int root(int a){\n   \
    \         assert(0<=a&&a<_n);\n            if(a==par[a]) return a;\n         \
    \   return root(par[a]);\n        }\n        //true\u306A\u30891,false\u306A\u3089\
    0\n        int same(int a,int b){\n            assert(0<=a&&a<_n);\n         \
    \   assert(0<=b&&b<_n);\n            if(root(a)==root(b)) return 1;\n        \
    \    else return 0;\n        }\n        //a,b\u304C\u9055\u3046\u6839\u3063\u3053\
    \u306E\u5143\u306A\u3089\u7D50\u5408\u3059\u308B,\u7D50\u5408\u3057\u305F\u3089\
    true\u3092\u8FD4\u3059\n        bool unite(int a,int b){\n            a=root(a),b=root(b);\n\
    \            if(a==b) return false;\n            if(wei[a]<wei[b]) std::swap(a,b);\n\
    \            par[b]=a;\n            if(ind==(int)(q.size())) q.push_back(b);\n\
    \            else q[ind]=b;\n            ind++;\n            wei[a]+=wei[b];\n\
    \            component--;\n            return true;\n        }\n        int size(int\
    \ a){\n            return wei[root(a)];\n        }\n    private:\n        std::vector<int>\
    \ par;\n    };\n}\nusing po167::UFtree_undo;\n"
  code: "namespace po167{\n    struct UFtree_undo{\n        int _n,ind;\n        std::vector<int>\
    \ wei;\n        std::vector<int> q;\n        int component;\n        UFtree_undo(int\
    \ n):_n(n),ind(0),wei(n),component(n),par(n){\n            for(int i=0;i<n;i++){\n\
    \                wei[i]=1,par[i]=i;\n            }\n        }\n        int undo(){\n\
    \            if(ind==0) return 0;\n            component++;\n            ind--;\n\
    \            wei[par[q[ind]]]-=wei[q[ind]];\n            par[q[ind]]=q[ind];\n\
    \            return 1;\n        }\n        void rollback(int times){\n       \
    \     int tmp=1;\n            while(tmp!=0&&times!=0){\n                tmp=undo();\n\
    \                times--;\n            }\n        }\n        void intialize(){\n\
    \            while(ind) undo();\n        }\n        //\u6839\u3063\u3053\u3092\
    \u8FD4\u3059\n        int root(int a){\n            assert(0<=a&&a<_n);\n    \
    \        if(a==par[a]) return a;\n            return root(par[a]);\n        }\n\
    \        //true\u306A\u30891,false\u306A\u30890\n        int same(int a,int b){\n\
    \            assert(0<=a&&a<_n);\n            assert(0<=b&&b<_n);\n          \
    \  if(root(a)==root(b)) return 1;\n            else return 0;\n        }\n   \
    \     //a,b\u304C\u9055\u3046\u6839\u3063\u3053\u306E\u5143\u306A\u3089\u7D50\u5408\
    \u3059\u308B,\u7D50\u5408\u3057\u305F\u3089true\u3092\u8FD4\u3059\n        bool\
    \ unite(int a,int b){\n            a=root(a),b=root(b);\n            if(a==b)\
    \ return false;\n            if(wei[a]<wei[b]) std::swap(a,b);\n            par[b]=a;\n\
    \            if(ind==(int)(q.size())) q.push_back(b);\n            else q[ind]=b;\n\
    \            ind++;\n            wei[a]+=wei[b];\n            component--;\n \
    \           return true;\n        }\n        int size(int a){\n            return\
    \ wei[root(a)];\n        }\n    private:\n        std::vector<int> par;\n    };\n\
    }\nusing po167::UFtree_undo;\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/undo_uf.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/undo_uf.hpp
layout: document
redirect_from:
- /library/no_test/undo_uf.hpp
- /library/no_test/undo_uf.hpp.html
title: no_test/undo_uf.hpp
---
