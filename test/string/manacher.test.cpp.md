---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/Manacher.hpp
    title: string/Manacher.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"test/string/manacher.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n#line 2 \"string/Manacher.hpp\"\n#include <vector>\n#include <string>\n\n\n\
    // https://snuke.hatenablog.com/entry/2014/12/02/235837\nnamespace po167{\ntemplate<class\
    \ T>\n\n// input  : abaab\n// output : 1 0 3 0 1 4 1 0 1\nstd::vector<int> Manacher(std::vector<T>\
    \ &v){\n    int N = v.size();\n    std::vector<int> res(N * 2 + 1);\n    int i\
    \ = 0, j = 0;\n    while (i < N * 2 + 1){\n        while (i - j >= 0 && i + j\
    \ < N * 2 + 1 \n            && (((i + j) & 1) == 0 || v[(i - j) / 2] == v[(i +\
    \ j) / 2])) j++;\n        res[i] = j;\n        int k = 1;\n        while (i -\
    \ k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], k++;\n        i += k,\
    \ j -= k;\n    }\n    res.pop_back();\n    res.erase(res.begin());\n    for (auto\
    \ &x : res) x--;\n    return res;\n}\n\n// input  : abaab\n// output : 1 0 3 0\
    \ 1 4 1 0 1\nstd::vector<int> Manacher(std::string &s){\n    std::vector<int>\
    \ v(s.size());\n    for (int i = 0; i < (int)s.size(); i++) v[i] = s[i];\n   \
    \ return Manacher(v);\n}\n}\n#line 3 \"test/string/manacher.test.cpp\"\n#include\
    \ <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    \n    std::string S;\n    std::cin >> S;\n    auto res = po167::Manacher(S);\n\
    \    for (int i = 0; i < (int)res.size(); i++){\n        std::cout << res[i] <<\
    \ ((int)(res.size()) == i + 1 ? \"\\n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n#include \"../../string/Manacher.hpp\"\n#include <iostream>\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ std::string S;\n    std::cin >> S;\n    auto res = po167::Manacher(S);\n   \
    \ for (int i = 0; i < (int)res.size(); i++){\n        std::cout << res[i] << ((int)(res.size())\
    \ == i + 1 ? \"\\n\" : \" \");\n    }\n}"
  dependsOn:
  - string/Manacher.hpp
  isVerificationFile: true
  path: test/string/manacher.test.cpp
  requiredBy: []
  timestamp: '2025-04-15 19:14:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/string/manacher.test.cpp
layout: document
redirect_from:
- /verify/test/string/manacher.test.cpp
- /verify/test/string/manacher.test.cpp.html
title: test/string/manacher.test.cpp
---
