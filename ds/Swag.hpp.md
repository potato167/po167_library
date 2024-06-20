---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/swag.test.cpp
    title: test/ds/swag.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/Swag.hpp\"\n#include <vector>\n#include <cassert>\n\n\
    namespace po167{\ntemplate<class T, T (*op)(T, T), T (*e)()>\nstruct SWAG\n{\n\
    \    std::vector<std::pair<T, T>> A, B;\n    SWAG(int n = -1){\n        if (n\
    \ > 0) A.reserve(n + 1), B.reserve(n + 1);\n        A.push_back({e(), e()});\n\
    \        B.push_back({e(), e()});\n    }\n    void push(T v){\n        B.push_back({v,\
    \ op(B.back().second, v)});\n    }\n    void pop(){\n        if ((int)A.size()\
    \ == 1){\n            while ((int)B.size() != 1){\n                A.push_back({B.back().first,\
    \ op(B.back().first, A.back().second)});\n                B.pop_back();\n    \
    \        }\n        }\n        assert((int)A.size() != 1);\n        A.pop_back();\n\
    \    }\n    T calc(){\n        return op(A.back().second, B.back().second);\n\
    \    }\n};\n}\n"
  code: "#pragma once\n#include <vector>\n#include <cassert>\n\nnamespace po167{\n\
    template<class T, T (*op)(T, T), T (*e)()>\nstruct SWAG\n{\n    std::vector<std::pair<T,\
    \ T>> A, B;\n    SWAG(int n = -1){\n        if (n > 0) A.reserve(n + 1), B.reserve(n\
    \ + 1);\n        A.push_back({e(), e()});\n        B.push_back({e(), e()});\n\
    \    }\n    void push(T v){\n        B.push_back({v, op(B.back().second, v)});\n\
    \    }\n    void pop(){\n        if ((int)A.size() == 1){\n            while ((int)B.size()\
    \ != 1){\n                A.push_back({B.back().first, op(B.back().first, A.back().second)});\n\
    \                B.pop_back();\n            }\n        }\n        assert((int)A.size()\
    \ != 1);\n        A.pop_back();\n    }\n    T calc(){\n        return op(A.back().second,\
    \ B.back().second);\n    }\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: ds/Swag.hpp
  requiredBy: []
  timestamp: '2024-06-21 05:23:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ds/swag.test.cpp
documentation_of: ds/Swag.hpp
layout: document
redirect_from:
- /library/ds/Swag.hpp
- /library/ds/Swag.hpp.html
title: ds/Swag.hpp
---
