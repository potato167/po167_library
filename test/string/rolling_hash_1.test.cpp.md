---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint/mint61.hpp
    title: modint/mint61.hpp
  - icon: ':heavy_check_mark:'
    path: string/Rolling_Hash.hpp
    title: string/Rolling_Hash.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/string/rolling_hash_1.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/zalgorithm\"\n#line 2 \"modint/mint61.hpp\"\n\n\
    // https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\nnamespace po167{\nstruct\
    \ mint61{\n    using u64 = unsigned long long;\n    static constexpr u64 MOD =\
    \ (1ULL << 61) - 1;\n    static constexpr u64 MASK30 = (1ULL << 30) - 1;\n   \
    \ static constexpr u64 MASK31 = (1ULL << 31) - 1;\n    u64  x;\n    u64 calcmod(u64\
    \ a){\n        u64 au = (a >> 61);\n        u64 ad = (a & MOD);\n        u64 res\
    \ = au + ad;\n        if (res >= MOD) res -= MOD;\n        return res;\n    }\n\
    \    mint61(){ x = 0;}\n    mint61(long long x_){\n        while (x_ < 0) x_ +=\
    \ MOD;\n        x = calcmod(x_);\n    }\n    mint61 &operator+=(mint61 b){\n \
    \       if ((x += b.x) >= MOD) x -= MOD;\n        return *this;\n    }\n    mint61\
    \ &operator-=(mint61 b){\n        if (x >= b.x) x -= b.x;\n        else{\n   \
    \         x += MOD;\n            x -= b.x;\n        }\n        return *this;\n\
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
    \ const {\n        return hash[r] - hash[l] * pow[r - l];\n    }\n};\n}\n#line\
    \ 3 \"test/string/rolling_hash_1.test.cpp\"\n#include <iostream>\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    \n   \
    \ std::string S;\n    std::cin >> S;\n    int N = S.size();\n    po167::RollingHash\
    \ H(S);\n    std::cout << N;\n    for (int i = 1; i < N; i++){\n        int a\
    \ = 0, b = N - i + 1;\n        while (b - a > 1){\n            int m = (a + b)\
    \ / 2;\n            if (H.get(0, m) == H.get(i, i + m)) a = m;\n            else\
    \ b = m;\n        }\n        std::cout << \" \" << a;\n    }\n    std::cout <<\
    \ \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include\
    \ \"../../string/Rolling_Hash.hpp\"\n#include <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    \n    std::string S;\n    std::cin >> S;\n  \
    \  int N = S.size();\n    po167::RollingHash H(S);\n    std::cout << N;\n    for\
    \ (int i = 1; i < N; i++){\n        int a = 0, b = N - i + 1;\n        while (b\
    \ - a > 1){\n            int m = (a + b) / 2;\n            if (H.get(0, m) ==\
    \ H.get(i, i + m)) a = m;\n            else b = m;\n        }\n        std::cout\
    \ << \" \" << a;\n    }\n    std::cout << \"\\n\";\n}"
  dependsOn:
  - string/Rolling_Hash.hpp
  - modint/mint61.hpp
  isVerificationFile: true
  path: test/string/rolling_hash_1.test.cpp
  requiredBy: []
  timestamp: '2025-04-27 17:28:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/string/rolling_hash_1.test.cpp
layout: document
redirect_from:
- /verify/test/string/rolling_hash_1.test.cpp
- /verify/test/string/rolling_hash_1.test.cpp.html
title: test/string/rolling_hash_1.test.cpp
---
