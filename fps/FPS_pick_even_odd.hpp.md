---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Boston_Mori.hpp
    title: "\u30DC\u30B9\u30BF\u30F3\u68EE\u6CD5"
  - icon: ':heavy_check_mark:'
    path: fps/FPS_Power_Projection.hpp
    title: fps/FPS_Power_Projection.hpp
  - icon: ':heavy_check_mark:'
    path: fps/FPS_inverse.hpp
    title: fps/FPS_inverse.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fps/comp_inverse.test.cpp
    title: test/fps/comp_inverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/fps/linear_kth.test.cpp
    title: test/fps/linear_kth.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps/FPS_pick_even_odd.hpp\"\n#include <vector>\n\nnamespace\
    \ po167{\n// s.t |v| = 2 ^ s (no assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T>\
    \ &v, int odd){\n    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n  \
    \  if (odd == 0){\n        for (int i = 0; i < z; i++){\n            v[i] = (v[i\
    \ * 2] + v[i * 2 + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n\
    \        T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()\
    \ / (2 * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n\
    \        while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}\n"
  code: "#pragma once\n#include <vector>\n\nnamespace po167{\n// s.t |v| = 2 ^ s (no\
    \ assert)\ntemplate<class T>\nvoid FPS_pick_even_odd(std::vector<T> &v, int odd){\n\
    \    int z = v.size() / 2;\n    T half = (T)(1) / (T)(2);\n    if (odd == 0){\n\
    \        for (int i = 0; i < z; i++){\n            v[i] = (v[i * 2] + v[i * 2\
    \ + 1]) * half;\n        }\n        v.resize(z);\n    } else {\n        T e =\
    \ (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod() / (2\
    \ * z));\n        T ie = T(1) / e;\n        std::vector<T> es = {half};\n    \
    \    while ((int)es.size() != z){\n            std::vector<T> n_es((int)es.size()\
    \ * 2);\n            for (int i = 0; i < (int)es.size(); i++){\n             \
    \   n_es[i * 2] = (es[i]);\n                n_es[i * 2 + 1] = (es[i] * ie);\n\
    \            }\n            ie *= ie;\n            std::swap(n_es, es);\n    \
    \    }\n        for (int i = 0; i < z; i ++){\n            v[i] = (v[i * 2] -\
    \ v[i * 2 + 1]) * es[i];\n        }\n        v.resize(z);\n    }\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: fps/FPS_pick_even_odd.hpp
  requiredBy:
  - fps/FPS_Power_Projection.hpp
  - fps/FPS_Boston_Mori.hpp
  - fps/FPS_inverse.hpp
  timestamp: '2024-06-19 15:49:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fps/comp_inverse.test.cpp
  - test/fps/linear_kth.test.cpp
documentation_of: fps/FPS_pick_even_odd.hpp
layout: document
redirect_from:
- /library/fps/FPS_pick_even_odd.hpp
- /library/fps/FPS_pick_even_odd.hpp.html
title: fps/FPS_pick_even_odd.hpp
---
