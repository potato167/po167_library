---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint/mint61.hpp
    title: modint/mint61.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/rolling_hash_1.test.cpp
    title: test/string/rolling_hash_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/string/rolling_hash_2.test.cpp
    title: test/string/rolling_hash_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modint/mint61.hpp\"\n\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    namespace po167{\nstruct mint61{\n    using u64 = unsigned long long;\n    static\
    \ constexpr u64 MOD = (1ULL << 61) - 1;\n    static constexpr u64 MASK30 = (1ULL\
    \ << 30) - 1;\n    static constexpr u64 MASK31 = (1ULL << 31) - 1;\n    u64  x;\n\
    \    u64 calcmod(u64 a){\n        u64 au = (a >> 61);\n        u64 ad = (a & MOD);\n\
    \        u64 res = au + ad;\n        if (res >= MOD) res -= MOD;\n        return\
    \ res;\n    }\n    mint61(){ x = 0;}\n    mint61(long long x_){\n        while\
    \ (x_ < 0) x_ += MOD;\n        x = calcmod(x_);\n    }\n    mint61 &operator+=(mint61\
    \ b){\n        if ((x += b.x) >= MOD) x -= MOD;\n        return *this;\n    }\n\
    \    mint61 &operator-=(mint61 b){\n        if (x >= b.x) x -= b.x;\n        else{\n\
    \            x += MOD;\n            x -= b.x;\n        }\n        return *this;\n\
    \    }\n    mint61 &operator*=(mint61 b){\n        u64 au = (x >> 31);\n     \
    \   u64 ad = (x & MASK31);\n        u64 bu = (b.x >> 31);\n        u64 bd = (b.x\
    \ & MASK31);\n        u64 mid = ad * bu + au * bd;\n        u64 midu = (mid >>\
    \ 30);\n        u64 midd = (mid & MASK30);\n        x = calcmod(au * bu * 2 +\
    \ midu + (midd << 31) + ad * bd);\n        return *this;\n    }\n    friend mint61\
    \ operator+(mint61 a, mint61 b){return a += b;}\n    friend mint61 operator-(mint61\
    \ a, mint61 b){return a -= b;}\n    friend mint61 operator*(mint61 a, mint61 b){return\
    \ a *= b;}\n    friend bool operator==(mint61 a, mint61 b){return a.x == b.x;}\n\
    \    friend bool operator!=(mint61 a, mint61 b){return a.x != b.x;}\n    mint61\
    \ pow(long long e) const {\n        mint61 r = 1,b =*this;\n        if (e < 0)\
    \ e = MOD - 1 + e % (MOD - 1);\n        while (e){\n            if (e & 1) r *=\
    \ b;\n            b *= b;\n            e >>= 1;\n        }\n        return r;\n\
    \    }\n};\n}\n#line 3 \"string/Rolling_Hash.hpp\"\n#include <random>\n#include\
    \ <string>\n#include <vector>\n\nnamespace po167{\nstruct RollingHash {\n    using\
    \ u64 = uint64_t;\n    static inline const mint61 base = std::mt19937_64{std::random_device{}()}();\n\
    \    int n;\n    std::vector<mint61> hash, pow;\n    RollingHash(const std::string&\
    \ s): n(s.size()), hash(n + 1), pow(n + 1, 1) {\n        for (int i = 0; i < n;\
    \ i++) {\n            pow[i + 1] = pow[i] * base;\n            hash[i + 1] = hash[i]\
    \ * base + s[i];\n        }\n    }\n    template<class T>\n    RollingHash(const\
    \ std::vector<T> &v): n(v.size()), hash(n + 1), pow(n + 1, 1) {\n        for (int\
    \ i = 0; i < n; i++){\n            pow[i + 1] = pow[i] * base;\n            hash[i\
    \ + 1] = hash[i] * base + v[i];\n        }\n    }\n    mint61 get(int l, int r)\
    \ const {\n        return hash[r] - hash[l] * pow[r - l];\n    }\n};\n}\n"
  code: "#pragma once\n#include \"../modint/mint61.hpp\"\n#include <random>\n#include\
    \ <string>\n#include <vector>\n\nnamespace po167{\nstruct RollingHash {\n    using\
    \ u64 = uint64_t;\n    static inline const mint61 base = std::mt19937_64{std::random_device{}()}();\n\
    \    int n;\n    std::vector<mint61> hash, pow;\n    RollingHash(const std::string&\
    \ s): n(s.size()), hash(n + 1), pow(n + 1, 1) {\n        for (int i = 0; i < n;\
    \ i++) {\n            pow[i + 1] = pow[i] * base;\n            hash[i + 1] = hash[i]\
    \ * base + s[i];\n        }\n    }\n    template<class T>\n    RollingHash(const\
    \ std::vector<T> &v): n(v.size()), hash(n + 1), pow(n + 1, 1) {\n        for (int\
    \ i = 0; i < n; i++){\n            pow[i + 1] = pow[i] * base;\n            hash[i\
    \ + 1] = hash[i] * base + v[i];\n        }\n    }\n    mint61 get(int l, int r)\
    \ const {\n        return hash[r] - hash[l] * pow[r - l];\n    }\n};\n}"
  dependsOn:
  - modint/mint61.hpp
  isVerificationFile: false
  path: string/Rolling_Hash.hpp
  requiredBy: []
  timestamp: '2025-04-27 17:28:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/rolling_hash_2.test.cpp
  - test/string/rolling_hash_1.test.cpp
documentation_of: string/Rolling_Hash.hpp
layout: document
redirect_from:
- /library/string/Rolling_Hash.hpp
- /library/string/Rolling_Hash.hpp.html
title: string/Rolling_Hash.hpp
---
