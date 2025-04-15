---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/manacher.test.cpp
    title: test/string/manacher.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://snuke.hatenablog.com/entry/2014/12/02/235837
  bundledCode: "#line 2 \"string/Manacher.hpp\"\n#include <vector>\n#include <string>\n\
    \n\n// https://snuke.hatenablog.com/entry/2014/12/02/235837\nnamespace po167{\n\
    template<class T>\n\n// input  : abaab\n// output : 1 0 3 0 1 4 1 0 1\nstd::vector<int>\
    \ Manacher(std::vector<T> &v){\n    int N = v.size();\n    std::vector<int> res(N\
    \ * 2 + 1);\n    int i = 0, j = 0;\n    while (i < N * 2 + 1){\n        while\
    \ (i - j >= 0 && i + j < N * 2 + 1 \n            && (((i + j) & 1) == 0 || v[(i\
    \ - j) / 2] == v[(i + j) / 2])) j++;\n        res[i] = j;\n        int k = 1;\n\
    \        while (i - k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], k++;\n\
    \        i += k, j -= k;\n    }\n    res.pop_back();\n    res.erase(res.begin());\n\
    \    for (auto &x : res) x--;\n    return res;\n}\n\n// input  : abaab\n// output\
    \ : 1 0 3 0 1 4 1 0 1\nstd::vector<int> Manacher(std::string &s){\n    std::vector<int>\
    \ v(s.size());\n    for (int i = 0; i < (int)s.size(); i++) v[i] = s[i];\n   \
    \ return Manacher(v);\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <string>\n\n\n// https://snuke.hatenablog.com/entry/2014/12/02/235837\n\
    namespace po167{\ntemplate<class T>\n\n// input  : abaab\n// output : 1 0 3 0\
    \ 1 4 1 0 1\nstd::vector<int> Manacher(std::vector<T> &v){\n    int N = v.size();\n\
    \    std::vector<int> res(N * 2 + 1);\n    int i = 0, j = 0;\n    while (i < N\
    \ * 2 + 1){\n        while (i - j >= 0 && i + j < N * 2 + 1 \n            && (((i\
    \ + j) & 1) == 0 || v[(i - j) / 2] == v[(i + j) / 2])) j++;\n        res[i] =\
    \ j;\n        int k = 1;\n        while (i - k >= 0 && k + res[i - k] < j) res[i\
    \ + k] = res[i - k], k++;\n        i += k, j -= k;\n    }\n    res.pop_back();\n\
    \    res.erase(res.begin());\n    for (auto &x : res) x--;\n    return res;\n\
    }\n\n// input  : abaab\n// output : 1 0 3 0 1 4 1 0 1\nstd::vector<int> Manacher(std::string\
    \ &s){\n    std::vector<int> v(s.size());\n    for (int i = 0; i < (int)s.size();\
    \ i++) v[i] = s[i];\n    return Manacher(v);\n}\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/Manacher.hpp
  requiredBy: []
  timestamp: '2025-04-15 19:14:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/manacher.test.cpp
documentation_of: string/Manacher.hpp
layout: document
redirect_from:
- /library/string/Manacher.hpp
- /library/string/Manacher.hpp.html
title: string/Manacher.hpp
---
