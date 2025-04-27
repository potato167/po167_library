---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: ds/Segtree.hpp
    title: ds/Segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/ds/segtree.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\
    \n\n#line 2 \"ds/Segtree.hpp\"\n#include <atcoder/segtree>\n\nnamespace po167{\n\
    template <class S, S (*op)(S, S), S (*e)()>\nstruct segtree : atcoder::segtree<S,\
    \ op, e> {\n    using atcoder::segtree<S, op, e>::segtree;\n    void updr(int\
    \ ind, S x) {\n        this->set(ind, op(this->get(ind), x));\n    }\n    void\
    \ updl(int ind, S x) {\n        this->set(ind, op(x, this->get(ind)));\n    }\n\
    };\n}\n#line 4 \"test/ds/segtree.cpp\"\n#include <iostream>\nusing ll = long long;\n\
    ll op(ll a, ll b){\n    return a + b;\n}\nll e(){\n    return 0ll;\n}\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ int N, Q;\n    std::cin >> N >> Q;\n    std::vector<ll> A(N);\n    for (auto\
    \ &a : A) std::cin >> a;\n    po167::segtree<ll, op, e> seg(A);\n    while (Q--){\n\
    \        int t, a, b;\n        std::cin >> t >> a >> b;\n        if (t == 0){\n\
    \            seg.updl(a, b);\n        }\n        else{\n            std::cout\
    \ << seg.prod(a, b) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../../ds/Segtree.hpp\"\n#include <iostream>\nusing ll = long long;\n\
    ll op(ll a, ll b){\n    return a + b;\n}\nll e(){\n    return 0ll;\n}\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ int N, Q;\n    std::cin >> N >> Q;\n    std::vector<ll> A(N);\n    for (auto\
    \ &a : A) std::cin >> a;\n    po167::segtree<ll, op, e> seg(A);\n    while (Q--){\n\
    \        int t, a, b;\n        std::cin >> t >> a >> b;\n        if (t == 0){\n\
    \            seg.updl(a, b);\n        }\n        else{\n            std::cout\
    \ << seg.prod(a, b) << \"\\n\";\n        }\n    }\n}"
  dependsOn:
  - ds/Segtree.hpp
  isVerificationFile: false
  path: test/ds/segtree.cpp
  requiredBy: []
  timestamp: '2025-04-27 17:28:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/ds/segtree.cpp
layout: document
redirect_from:
- /library/test/ds/segtree.cpp
- /library/test/ds/segtree.cpp.html
title: test/ds/segtree.cpp
---
