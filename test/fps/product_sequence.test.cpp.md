---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Product_Sequence.hpp
    title: fps/FPS_Product_Sequence.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/product_of_polynomial_sequence
    links:
    - https://judge.yosupo.jp/problem/product_of_polynomial_sequence
  bundledCode: "#line 1 \"test/fps/product_sequence.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/product_of_polynomial_sequence\"\n\n#line 2 \"\
    fps/FPS_Product_Sequence.hpp\"\n#include <vector>\n#include <atcoder/convolution>\n\
    \nnamespace po167{\ntemplate<class T>\nstd::vector<T> FPS_Product_Sequence(std::vector<std::vector<T>>\
    \ f){\n    if (f.empty()) return {1};\n    auto op = [&](auto self,int l, int\
    \ r) -> std::vector<T> {\n        if (l + 1 == r) return f[l];\n        int m\
    \ = (l + r) / 2;\n        return atcoder::convolution(self(self, l, m), self(self,\
    \ m, r));\n    };\n    return op(op, 0, f.size());\n}\n}\n#line 4 \"test/fps/product_sequence.test.cpp\"\
    \n\n#line 6 \"test/fps/product_sequence.test.cpp\"\n#include <iostream>\n\n\n\
    int main(){\n    int N;\n    std::cin >> N;\n    std::vector<std::vector<atcoder::modint998244353>>\
    \ f(N);\n    for (int i = 0; i < N; i++){\n        int d;\n        std::cin >>\
    \ d;\n        f[i].resize(d + 1);\n        for (int j = 0; j <= d; j++){\n   \
    \         int a;\n            std::cin >> a;\n            f[i][j] = a;\n     \
    \   }\n    }\n    auto ans = po167::FPS_Product_Sequence(f);\n    for (int i =\
    \ 0; i < (int)ans.size(); i++){\n        if (i) std::cout << \" \";\n        std::cout\
    \ << ans[i].val();\n    }\n    std::cout << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/product_of_polynomial_sequence\"\
    \n\n#include \"../../fps/FPS_Product_Sequence.hpp\"\n\n#include <vector>\n#include\
    \ <iostream>\n\n\nint main(){\n    int N;\n    std::cin >> N;\n    std::vector<std::vector<atcoder::modint998244353>>\
    \ f(N);\n    for (int i = 0; i < N; i++){\n        int d;\n        std::cin >>\
    \ d;\n        f[i].resize(d + 1);\n        for (int j = 0; j <= d; j++){\n   \
    \         int a;\n            std::cin >> a;\n            f[i][j] = a;\n     \
    \   }\n    }\n    auto ans = po167::FPS_Product_Sequence(f);\n    for (int i =\
    \ 0; i < (int)ans.size(); i++){\n        if (i) std::cout << \" \";\n        std::cout\
    \ << ans[i].val();\n    }\n    std::cout << \"\\n\";\n}"
  dependsOn:
  - fps/FPS_Product_Sequence.hpp
  isVerificationFile: true
  path: test/fps/product_sequence.test.cpp
  requiredBy: []
  timestamp: '2024-06-19 18:48:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fps/product_sequence.test.cpp
layout: document
redirect_from:
- /verify/test/fps/product_sequence.test.cpp
- /verify/test/fps/product_sequence.test.cpp.html
title: test/fps/product_sequence.test.cpp
---
