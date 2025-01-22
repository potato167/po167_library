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
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
  bundledCode: "#line 2 \"modint/mint61.hpp\"\n\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    namespace po167{\nstruct mint61{\n    using u64 = unsigned long long;\n    const\
    \ u64 MOD = (1UL << 61) - 1;\n    const u64 MASK30 = (1UL << 30) - 1;\n    const\
    \ u64 MASK31 = (1UL << 31) - 1;\n    u64  x = 0;\n    u64 calcmod(u64 a){\n  \
    \      u64 au = (a >> 61);\n        u64 ad = (a & MOD);\n        u64 res = au\
    \ + ad;\n        if (res >= MOD) res -= MOD;\n        return res;\n    }\n   \
    \ mint61(long long x_){\n        while (x_ < 0) x_ += MOD;\n        x = calcmod(x_);\n\
    \    }\n    mint61 &operator+=(mint61 b){\n        if ((x += b.x) >= MOD) x -=\
    \ MOD;\n        return *this;\n    }\n    mint61 &operator-=(mint61 b){\n    \
    \    if (x >= b.x) x -= b.x;\n        else{\n            x += MOD;\n         \
    \   x -= b.x;\n        }\n        return *this;\n    }\n    mint61 &operator*=(mint61\
    \ b){\n        u64 au = (x >> 31);\n        u64 ad = (x & MASK31);\n        u64\
    \ bu = (b.x >> 31);\n        u64 bd = (b.x & MASK31);\n        u64 mid = ad *\
    \ bu + au * bd;\n        u64 midu = (mid >> 30);\n        u64 midd = (mid & MASK30);\n\
    \        x = calcmod(au * bu * 2 + midu + (midd << 31) + ad * bd);\n        return\
    \ *this;\n    }\n    friend mint61 operator+(mint61 a, mint61 b){return a += b;}\n\
    \    friend mint61 operator-(mint61 a, mint61 b){return a -= b;}\n    friend mint61\
    \ operator*(mint61 a, mint61 b){return a *= b;}\n    friend bool operator==(mint61\
    \ a, mint61 b){return a.x == b.x;}\n    friend bool operator!=(mint61 a, mint61\
    \ b){return a.x != b.x;}\n};\n}\n"
  code: "#pragma once\n\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    namespace po167{\nstruct mint61{\n    using u64 = unsigned long long;\n    const\
    \ u64 MOD = (1UL << 61) - 1;\n    const u64 MASK30 = (1UL << 30) - 1;\n    const\
    \ u64 MASK31 = (1UL << 31) - 1;\n    u64  x = 0;\n    u64 calcmod(u64 a){\n  \
    \      u64 au = (a >> 61);\n        u64 ad = (a & MOD);\n        u64 res = au\
    \ + ad;\n        if (res >= MOD) res -= MOD;\n        return res;\n    }\n   \
    \ mint61(long long x_){\n        while (x_ < 0) x_ += MOD;\n        x = calcmod(x_);\n\
    \    }\n    mint61 &operator+=(mint61 b){\n        if ((x += b.x) >= MOD) x -=\
    \ MOD;\n        return *this;\n    }\n    mint61 &operator-=(mint61 b){\n    \
    \    if (x >= b.x) x -= b.x;\n        else{\n            x += MOD;\n         \
    \   x -= b.x;\n        }\n        return *this;\n    }\n    mint61 &operator*=(mint61\
    \ b){\n        u64 au = (x >> 31);\n        u64 ad = (x & MASK31);\n        u64\
    \ bu = (b.x >> 31);\n        u64 bd = (b.x & MASK31);\n        u64 mid = ad *\
    \ bu + au * bd;\n        u64 midu = (mid >> 30);\n        u64 midd = (mid & MASK30);\n\
    \        x = calcmod(au * bu * 2 + midu + (midd << 31) + ad * bd);\n        return\
    \ *this;\n    }\n    friend mint61 operator+(mint61 a, mint61 b){return a += b;}\n\
    \    friend mint61 operator-(mint61 a, mint61 b){return a -= b;}\n    friend mint61\
    \ operator*(mint61 a, mint61 b){return a *= b;}\n    friend bool operator==(mint61\
    \ a, mint61 b){return a.x == b.x;}\n    friend bool operator!=(mint61 a, mint61\
    \ b){return a.x != b.x;}\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: modint/mint61.hpp
  requiredBy: []
  timestamp: '2025-01-22 11:47:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: modint/mint61.hpp
layout: document
redirect_from:
- /library/modint/mint61.hpp
- /library/modint/mint61.hpp.html
title: modint/mint61.hpp
---
