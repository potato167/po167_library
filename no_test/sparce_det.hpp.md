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
    - https://ikatakos.com/pot/programming_algorithm/number_theory/barlekamp_massey
    - https://nyaannyaan.github.io/library/matrix/black-box-linear-algebra.hpp
  bundledCode: "#line 1 \"no_test/sparce_det.hpp\"\nnamespace po167{\nstd::random_device\
    \ po_seed_gen;\nstd::mt19937 po_random_gen(po_seed_gen());\nlong long randLong(long\
    \ long l = 0, long long r = (1ll << 62)){\n    return std::uniform_int_distribution<long\
    \ long>(l, r - 1)(po_random_gen);\n}\ntemplate<class T>\nstd::vector<T> rand_vec(int\
    \ sz, long long l =0, long long r = (1ll << 62)){\n    std::vector<T> res(sz);\n\
    \    for(auto &x: res) x = T(randLong(l, r));\n    return res;\n}\n\n//https://ikatakos.com/pot/programming_algorithm/number_theory/barlekamp_massey\n\
    template<class T>\nstd::vector<T> Berlekamp_Massey(std::vector<T> s){\n    std::vector<T>\
    \ C={1}, B={1};\n    int L = 0;\n    int m = 1;\n    T b = 1;\n    for (int n\
    \ = 0; n < int(s.size()); n++){\n        T d = 0;\n        for (int j = 0; j <\
    \ L + 1; j++){\n            d += C[j] * s[n - j];\n        }\n        if (d ==\
    \ 0){\n            m++;\n            continue;\n        }\n        T iv = d /\
    \ b;\n        if (2 * L <= n){\n            auto tC = C;\n            while (int(C.size())\
    \ <= n + 1 - L) C.push_back(0);\n            for (int i = 0; i < int(B.size());\
    \ i++) C[i + m] -= iv * B[i];\n            B = tC;\n            L = n + 1 - L;\n\
    \            b = d;\n            m = 1;\n        }\n        else{\n          \
    \  for(int i = 0; i < int(B.size()); i++){\n                C[i + m] -= iv * B[i];\n\
    \            }\n            m++;\n        }\n    }\n    return C;\n}\n\n// https://nyaannyaan.github.io/library/matrix/black-box-linear-algebra.hpp\n\
    \ntemplate<class T>\nT det_sparse_matrix(std::vector<std::vector<T>> A, T mj =\
    \ 0){\n    int n = A.size();\n    std::vector<T> D;\n    struct pos_mat{\n   \
    \     int x;\n        int y;\n        T val;\n    };\n    std::vector<pos_mat>\
    \ p;\n    for (int i = 0; i < n; i++){\n        for(int j = 0; j < n; j++) if\
    \ (A[i][j] != mj) {\n            p.push_back({i, j, A[i][j] - mj});\n        }\n\
    \    }\n    while (true){\n        while (true){\n            D = rand_vec<T>(n);\n\
    \            bool ok = 1;\n            for (auto x: D) if (x == 0) ok = 0;\n \
    \           if (ok) break;\n        }\n        std::vector<pos_mat> AD = p;\n\
    \        for (int i = 0; i < int(AD.size()); i++) AD[i].val *= D[AD[i].y];\n \
    \       std::vector<T> u = rand_vec<T>(n), v = rand_vec<T>(n);\n        std::vector<T>\
    \ b(n);\n        std::vector<T> a(2 * n + 1);\n        b = u;\n        for (int\
    \  i = 0; i < 2 * n + 1; i++){\n            T sum = 0;\n            for (int j\
    \ = 0; j < n; j++){\n                sum += u[j] * D[j];\n                a[i]\
    \ += u[j] * v[j];\n            }\n            sum *= mj;\n            for (int\
    \ j = 0; j < n; j++){\n                u[j] = sum;\n            }\n          \
    \  for (pos_mat tmp: AD){\n                u[tmp.x] += tmp.val * b[tmp.y]; \n\
    \            }\n            b = u;\n        }\n        auto mp = Berlekamp_Massey(a);\n\
    \        if (mp.back() == 0) return 0;\n        if (int(mp.size()) != n + 1) continue;\n\
    \        T res = mp.back();\n        if (n & 1) res *= -1;\n        T tmp = 1;\n\
    \        for (auto d: D) tmp *= d;\n        return res / tmp;\n    }\n}\n}\n"
  code: "namespace po167{\nstd::random_device po_seed_gen;\nstd::mt19937 po_random_gen(po_seed_gen());\n\
    long long randLong(long long l = 0, long long r = (1ll << 62)){\n    return std::uniform_int_distribution<long\
    \ long>(l, r - 1)(po_random_gen);\n}\ntemplate<class T>\nstd::vector<T> rand_vec(int\
    \ sz, long long l =0, long long r = (1ll << 62)){\n    std::vector<T> res(sz);\n\
    \    for(auto &x: res) x = T(randLong(l, r));\n    return res;\n}\n\n//https://ikatakos.com/pot/programming_algorithm/number_theory/barlekamp_massey\n\
    template<class T>\nstd::vector<T> Berlekamp_Massey(std::vector<T> s){\n    std::vector<T>\
    \ C={1}, B={1};\n    int L = 0;\n    int m = 1;\n    T b = 1;\n    for (int n\
    \ = 0; n < int(s.size()); n++){\n        T d = 0;\n        for (int j = 0; j <\
    \ L + 1; j++){\n            d += C[j] * s[n - j];\n        }\n        if (d ==\
    \ 0){\n            m++;\n            continue;\n        }\n        T iv = d /\
    \ b;\n        if (2 * L <= n){\n            auto tC = C;\n            while (int(C.size())\
    \ <= n + 1 - L) C.push_back(0);\n            for (int i = 0; i < int(B.size());\
    \ i++) C[i + m] -= iv * B[i];\n            B = tC;\n            L = n + 1 - L;\n\
    \            b = d;\n            m = 1;\n        }\n        else{\n          \
    \  for(int i = 0; i < int(B.size()); i++){\n                C[i + m] -= iv * B[i];\n\
    \            }\n            m++;\n        }\n    }\n    return C;\n}\n\n// https://nyaannyaan.github.io/library/matrix/black-box-linear-algebra.hpp\n\
    \ntemplate<class T>\nT det_sparse_matrix(std::vector<std::vector<T>> A, T mj =\
    \ 0){\n    int n = A.size();\n    std::vector<T> D;\n    struct pos_mat{\n   \
    \     int x;\n        int y;\n        T val;\n    };\n    std::vector<pos_mat>\
    \ p;\n    for (int i = 0; i < n; i++){\n        for(int j = 0; j < n; j++) if\
    \ (A[i][j] != mj) {\n            p.push_back({i, j, A[i][j] - mj});\n        }\n\
    \    }\n    while (true){\n        while (true){\n            D = rand_vec<T>(n);\n\
    \            bool ok = 1;\n            for (auto x: D) if (x == 0) ok = 0;\n \
    \           if (ok) break;\n        }\n        std::vector<pos_mat> AD = p;\n\
    \        for (int i = 0; i < int(AD.size()); i++) AD[i].val *= D[AD[i].y];\n \
    \       std::vector<T> u = rand_vec<T>(n), v = rand_vec<T>(n);\n        std::vector<T>\
    \ b(n);\n        std::vector<T> a(2 * n + 1);\n        b = u;\n        for (int\
    \  i = 0; i < 2 * n + 1; i++){\n            T sum = 0;\n            for (int j\
    \ = 0; j < n; j++){\n                sum += u[j] * D[j];\n                a[i]\
    \ += u[j] * v[j];\n            }\n            sum *= mj;\n            for (int\
    \ j = 0; j < n; j++){\n                u[j] = sum;\n            }\n          \
    \  for (pos_mat tmp: AD){\n                u[tmp.x] += tmp.val * b[tmp.y]; \n\
    \            }\n            b = u;\n        }\n        auto mp = Berlekamp_Massey(a);\n\
    \        if (mp.back() == 0) return 0;\n        if (int(mp.size()) != n + 1) continue;\n\
    \        T res = mp.back();\n        if (n & 1) res *= -1;\n        T tmp = 1;\n\
    \        for (auto d: D) tmp *= d;\n        return res / tmp;\n    }\n}\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/sparce_det.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/sparce_det.hpp
layout: document
redirect_from:
- /library/no_test/sparce_det.hpp
- /library/no_test/sparce_det.hpp.html
title: no_test/sparce_det.hpp
---
