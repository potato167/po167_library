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
  bundledCode: "#line 1 \"no_test/slope_trick.hpp\"\nnamespace po167{\n    template<class\
    \ T>\n    struct slope_trick{\n        std::priority_queue<T> left_pq;\n     \
    \   std::priority_queue<T,std::vector<T>,std::greater<T>> right_pq;\n        T\
    \ min_f;\n        T add_l,add_r;\n        slope_trick():min_f(0),add_l(0),add_r(0){};\n\
    \n        //f(x)=min(f(i)) i<=x\n        void left_min(){\n            right_pq={};\n\
    \            add_r=0;\n        }\n        //f(x)=min(f(i)) i>=x\n        void\
    \ right_min(){\n            left_pq={};\n            add_l=0;\n        }\n   \
    \     void add_constant_function(T d){\n            min_f+=d;\n        }\n   \
    \     //f(x)<- f(x)+max(x-a,0)\n        void add_x_minus_a(T a){\n           \
    \ a-=add_l;\n            if(!left_pq.empty()){\n                min_f+=std::max(left_pq.top()-a,(T)0);\n\
    \            }\n            left_pq.push(a);\n            right_pq.push(left_pq.top()+add_l-add_r);\n\
    \            left_pq.pop();\n        }\n\n        //f(x) <- f(x)+max(a-x,0)\n\
    \        void add_a_minus_x(T a){\n            a-=add_r;\n            if(!right_pq.empty()){\n\
    \                min_f+=std::max(a-right_pq.top(),(T)0);\n            }\n    \
    \        right_pq.push(a);\n            left_pq.push(right_pq.top()+add_r-add_l);\n\
    \            right_pq.pop();\n        }\n\n        //f(x) <- f(x) + |x-a|\n  \
    \      void add_abs_x_minus_a(T a){\n            add_a_minus_x(a);\n         \
    \   add_x_minus_a(a);\n        }\n\n        //f(x) <- f(x-a)\n        void shift(T\
    \ a){\n            add_l+=a;\n            add_r+=a;\n        }\n\n        //f(x)\
    \ <- min(f(x-i)) i= a~b\n        //need: a<=b\n        void sliding_min(T a,T\
    \ b){\n            assert(a<=b);\n            add_l+=a;\n            add_r+=b;\n\
    \        }\n\n        // return f(x)\n        // O(|pq|)\n        T get(T x){\n\
    \            auto tmp = left_pq;\n            T res = min_f;\n            while\
    \ (!tmp.empty()){\n                res += std::max(T(0), tmp.top() + add_l - x);\n\
    \                tmp.pop();\n            }\n            auto tmp2 = right_pq;\n\
    \            while (!tmp2.empty()){\n                res += std::max(T(0), x -\
    \ tmp2.top() - add_r);\n                tmp2.pop();\n            }\n         \
    \   return res;\n        }\n\n        void merge_and_break(slope_trick &S){\n\
    \            min_f+=S.min_f;\n            T tmp;\n            while(!S.left_pq.empty()){\n\
    \                tmp=S.left_pq.top();\n                S.left_pq.pop();\n    \
    \            add_a_minus_x(S.add_l+tmp);\n            }\n            while(!S.right_pq.empty()){\n\
    \                tmp=S.right_pq.top();\n                S.right_pq.pop();\n  \
    \              add_x_minus_a(S.add_r+tmp);\n            }\n        }\n       \
    \ void merge_and_remain(slope_trick S){\n            merge_and_break(S);\n   \
    \     }\n    };\n}\nusing po167::slope_trick;\n"
  code: "namespace po167{\n    template<class T>\n    struct slope_trick{\n      \
    \  std::priority_queue<T> left_pq;\n        std::priority_queue<T,std::vector<T>,std::greater<T>>\
    \ right_pq;\n        T min_f;\n        T add_l,add_r;\n        slope_trick():min_f(0),add_l(0),add_r(0){};\n\
    \n        //f(x)=min(f(i)) i<=x\n        void left_min(){\n            right_pq={};\n\
    \            add_r=0;\n        }\n        //f(x)=min(f(i)) i>=x\n        void\
    \ right_min(){\n            left_pq={};\n            add_l=0;\n        }\n   \
    \     void add_constant_function(T d){\n            min_f+=d;\n        }\n   \
    \     //f(x)<- f(x)+max(x-a,0)\n        void add_x_minus_a(T a){\n           \
    \ a-=add_l;\n            if(!left_pq.empty()){\n                min_f+=std::max(left_pq.top()-a,(T)0);\n\
    \            }\n            left_pq.push(a);\n            right_pq.push(left_pq.top()+add_l-add_r);\n\
    \            left_pq.pop();\n        }\n\n        //f(x) <- f(x)+max(a-x,0)\n\
    \        void add_a_minus_x(T a){\n            a-=add_r;\n            if(!right_pq.empty()){\n\
    \                min_f+=std::max(a-right_pq.top(),(T)0);\n            }\n    \
    \        right_pq.push(a);\n            left_pq.push(right_pq.top()+add_r-add_l);\n\
    \            right_pq.pop();\n        }\n\n        //f(x) <- f(x) + |x-a|\n  \
    \      void add_abs_x_minus_a(T a){\n            add_a_minus_x(a);\n         \
    \   add_x_minus_a(a);\n        }\n\n        //f(x) <- f(x-a)\n        void shift(T\
    \ a){\n            add_l+=a;\n            add_r+=a;\n        }\n\n        //f(x)\
    \ <- min(f(x-i)) i= a~b\n        //need: a<=b\n        void sliding_min(T a,T\
    \ b){\n            assert(a<=b);\n            add_l+=a;\n            add_r+=b;\n\
    \        }\n\n        // return f(x)\n        // O(|pq|)\n        T get(T x){\n\
    \            auto tmp = left_pq;\n            T res = min_f;\n            while\
    \ (!tmp.empty()){\n                res += std::max(T(0), tmp.top() + add_l - x);\n\
    \                tmp.pop();\n            }\n            auto tmp2 = right_pq;\n\
    \            while (!tmp2.empty()){\n                res += std::max(T(0), x -\
    \ tmp2.top() - add_r);\n                tmp2.pop();\n            }\n         \
    \   return res;\n        }\n\n        void merge_and_break(slope_trick &S){\n\
    \            min_f+=S.min_f;\n            T tmp;\n            while(!S.left_pq.empty()){\n\
    \                tmp=S.left_pq.top();\n                S.left_pq.pop();\n    \
    \            add_a_minus_x(S.add_l+tmp);\n            }\n            while(!S.right_pq.empty()){\n\
    \                tmp=S.right_pq.top();\n                S.right_pq.pop();\n  \
    \              add_x_minus_a(S.add_r+tmp);\n            }\n        }\n       \
    \ void merge_and_remain(slope_trick S){\n            merge_and_break(S);\n   \
    \     }\n    };\n}\nusing po167::slope_trick;\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/slope_trick.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/slope_trick.hpp
layout: document
redirect_from:
- /library/no_test/slope_trick.hpp
- /library/no_test/slope_trick.hpp.html
title: no_test/slope_trick.hpp
---
