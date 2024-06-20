---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/Swag.hpp
    title: ds/Swag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/ds/swag.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 2 \"ds/Swag.hpp\"\n#include <vector>\n#include <cassert>\n\nnamespace\
    \ po167{\ntemplate<class T, T (*op)(T, T), T (*e)()>\nstruct SWAG\n{\n    std::vector<std::pair<T,\
    \ T>> A, B;\n    SWAG(int n = -1){\n        if (n > 0) A.reserve(n + 1), B.reserve(n\
    \ + 1);\n        A.push_back({e(), e()});\n        B.push_back({e(), e()});\n\
    \    }\n    void push(T v){\n        B.push_back({v, op(B.back().second, v)});\n\
    \    }\n    void pop(){\n        if ((int)A.size() == 1){\n            while ((int)B.size()\
    \ != 1){\n                A.push_back({B.back().first, op(B.back().first, A.back().second)});\n\
    \                B.pop_back();\n            }\n        }\n        assert((int)A.size()\
    \ != 1);\n        A.pop_back();\n    }\n    T calc(){\n        return op(A.back().second,\
    \ B.back().second);\n    }\n};\n}\n#line 4 \"test/ds/swag.test.cpp\"\n\n#line\
    \ 6 \"test/ds/swag.test.cpp\"\n#include <iostream>\n#include <atcoder/modint>\n\
    \nusing mint = atcoder::modint998244353;\nusing F = std::pair<mint, mint>;\nF\
    \ e(){\n    return {1, 0};\n}\n\nF op(F l, F r){\n    return {l.first * r.first,\
    \ l.second * r.first + r.second};\n}\n\nint main(){\n    int Q;\n    std::cin\
    \ >> Q;\n    po167::SWAG<F, op, e> S(Q);\n    while (Q--){\n        int t;\n \
    \       std::cin >> t;\n        if (t == 0){\n            int a, b;\n        \
    \    std::cin >> a >> b;\n            S.push({a, b});\n        }\n        if (t\
    \ == 1){\n            S.pop();\n        }\n        if (t == 2){\n            int\
    \ x;\n            std::cin >> x;\n            F tmp = S.calc();\n            std::cout\
    \ << (tmp.first * x + tmp.second).val() << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"../..//ds/Swag.hpp\"\n\n#include <vector>\n#include <iostream>\n\
    #include <atcoder/modint>\n\nusing mint = atcoder::modint998244353;\nusing F =\
    \ std::pair<mint, mint>;\nF e(){\n    return {1, 0};\n}\n\nF op(F l, F r){\n \
    \   return {l.first * r.first, l.second * r.first + r.second};\n}\n\nint main(){\n\
    \    int Q;\n    std::cin >> Q;\n    po167::SWAG<F, op, e> S(Q);\n    while (Q--){\n\
    \        int t;\n        std::cin >> t;\n        if (t == 0){\n            int\
    \ a, b;\n            std::cin >> a >> b;\n            S.push({a, b});\n      \
    \  }\n        if (t == 1){\n            S.pop();\n        }\n        if (t ==\
    \ 2){\n            int x;\n            std::cin >> x;\n            F tmp = S.calc();\n\
    \            std::cout << (tmp.first * x + tmp.second).val() << \"\\n\";\n   \
    \     }\n    }\n}"
  dependsOn:
  - ds/Swag.hpp
  isVerificationFile: true
  path: test/ds/swag.test.cpp
  requiredBy: []
  timestamp: '2024-06-21 05:23:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ds/swag.test.cpp
layout: document
redirect_from:
- /verify/test/ds/swag.test.cpp
- /verify/test/ds/swag.test.cpp.html
title: test/ds/swag.test.cpp
---
