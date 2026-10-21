---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ds/waveletmatrix_1.test.cpp
    title: test/ds/waveletmatrix_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ds/waveletmatrix_2.test.cpp
    title: test/ds/waveletmatrix_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ds/waveletmatrix_3.test.cpp
    title: test/ds/waveletmatrix_3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ds/waveletmatrix_4.test.cpp
    title: test/ds/waveletmatrix_4.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html
  bundledCode: "#line 2 \"ds/WaveletMatrix.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace po167{\n// Nonnegative integer values; C++17, no\
    \ required CPU extensions.\n// Based on the API at:\n// https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html\n\
    struct bit_vector {\n    using u32 = std::uint32_t;\n    using u64 = std::uint64_t;\n\
    \    static constexpr u32 w = 32;\n\n    // Low 32 bits: data. High 32 bits: number\
    \ of preceding one-bits.\n    std::vector<u64> block;\n    u32 n = 0, zeros =\
    \ 0;\n\n    bit_vector(u32 size = 0) { init(size); }\n    void init(u32 size)\
    \ {\n        n = zeros = size;\n        block.assign(n / w + 1, 0);\n    }\n \
    \   static u32 popcount(u32 x) {\n        x -= (x >> 1) & 0x55555555u;\n     \
    \   x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);\n        x = (x + (x >>\
    \ 4)) & 0x0f0f0f0fu;\n        return u32(x * 0x01010101u) >> 24;\n    }\n    u32\
    \ get(u32 i) const { return (u32(block[i / w]) >> (i % w)) & 1; }\n    void set(u32\
    \ i) { block[i / w] |= u64(1) << (i % w); }\n    void build() {\n        u32 sum\
    \ = 0;\n        for (auto& x : block) {\n            u32 bits = u32(x);\n    \
    \        x = (u64(sum) << 32) | bits;\n            sum += popcount(bits);\n  \
    \      }\n        zeros = n - sum;\n    }\n    u32 rank1(u32 i) const {\n    \
    \    u64 x = block[i / w];\n        return u32(x >> 32) + popcount(u32(x) & ((u32(1)\
    \ << (i % w)) - 1));\n    }\n    u32 rank0(u32 i) const { return i - rank1(i);\
    \ }\n};\n\ntemplate <typename T, bool FastKth = true>\nstruct WaveletMatrix {\n\
    \    static_assert(std::is_integral<T>::value && !std::is_same<T, bool>::value,\n\
    \                  \"T must be a non-bool integer type\");\n    using U = typename\
    \ std::make_unsigned<T>::type;\n    using u32 = std::uint32_t;\n\n    int n =\
    \ 0, lg = 1, mid_h = -1;\n    T max_value = 0;\n    std::vector<T> a, mid;\n \
    \   std::vector<bit_vector> bv;\n\n    WaveletMatrix(u32 size) : n(int(size)),\
    \ a(size) {\n        assert(size <= u32((std::numeric_limits<int>::max)()));\n\
    \    }\n    WaveletMatrix(const std::vector<T>& values) : a(values) { build();\
    \ }\n\n    void set(u32 i, const T& x) {\n        assert(i < a.size() && x >=\
    \ 0);\n        a[i] = x;\n    }\n    void build() {\n        assert(a.size() <=\
    \ std::size_t((std::numeric_limits<int>::max)()));\n        n = int(a.size());\n\
    \        max_value = 0;\n        for (T x : a) {\n            assert(x >= 0);\n\
    \            if (max_value < x) max_value = x;\n        }\n        lg = 1;\n \
    \       for (U x = U(max_value); x >>= 1;) ++lg;\n        mid.clear();\n     \
    \   mid_h = lg - 2;\n        for (u32 x = u32(n); x; x >>= 1) --mid_h;\n     \
    \   bv.assign(lg, bit_vector(u32(n)));\n        std::vector<T> cur = a, nxt(n);\n\
    \        for (int h = lg - 1; h >= 0; --h) {\n            // Keep one intermediate\
    \ order to finish small candidate ranges.\n            if constexpr (FastKth)\
    \ {\n                if (h == mid_h) mid = cur;\n            }\n            auto&\
    \ b = bv[h];\n            for (u32 i = 0; i < u32(n); i += 32) {\n           \
    \     u32 bits = 0, len = (std::min)(u32(32), u32(n) - i);\n                for\
    \ (u32 j = 0; j < len; ++j)\n                    bits |= u32((U(cur[i + j]) >>\
    \ h) & 1) << j;\n                b.block[i / 32] = bits;\n            }\n    \
    \        b.build();\n            if (h == 0) break;\n            u32 pos[2] =\
    \ {0, b.zeros};\n            for (T x : cur) nxt[pos[(U(x) >> h) & 1]++] = x;\n\
    \            cur.swap(nxt);\n        }\n    }\n\n    std::pair<u32, u32> succ0(int\
    \ l, int r, int h) const {\n        return {bv[h].rank0(l), bv[h].rank0(r)};\n\
    \    }\n    std::pair<u32, u32> succ1(int l, int r, int h) const {\n        const\
    \ auto& b = bv[h];\n        return {b.zeros + b.rank1(l), b.zeros + b.rank1(r)};\n\
    \    }\n    T access(u32 k) const {\n        assert(k < a.size());\n        return\
    \ a[k];\n    }\n    T kth_smallest(u32 l, u32 r, u32 k) const {\n        assert(l\
    \ <= r && r <= u32(n) && k < r - l);\n        if (r - l == 1) return a[l];\n \
    \       U res = 0;\n        for (int h = lg - 1; h >= 0; --h) {\n            if\
    \ constexpr (FastKth) {\n                if (h == mid_h && r - l <= 2)\n     \
    \               return k ? (std::max)(mid[l], mid[r - 1])\n                  \
    \           : (std::min)(mid[l], mid[r - 1]);\n            }\n            const\
    \ auto& b = bv[h];\n            u32 l1 = b.rank1(l), r1 = b.rank1(r);\n      \
    \      u32 l0 = l - l1, r0 = r - r1, cnt = r0 - l0;\n            bool f = k >=\
    \ cnt;\n            k -= f ? cnt : 0;\n            res |= U(f) << h;\n       \
    \     l = f ? b.zeros + l1 : l0;\n            r = f ? b.zeros + r1 : r0;\n   \
    \     }\n        return T(res);\n    }\n    T kth_largest(int l, int r, int k)\
    \ const {\n        assert(0 <= k && k < r - l);\n        return kth_smallest(l,\
    \ r, r - l - k - 1);\n    }\n    int range_freq(int l, int r, T upper) const {\n\
    \        assert(0 <= l && l <= r && r <= n);\n        if (upper <= 0) return 0;\n\
    \        if (upper > max_value) return r - l;\n        u32 ret = 0;\n        for\
    \ (int h = lg - 1; h >= 0 && l < r; --h) {\n            const auto& b = bv[h];\n\
    \            u32 l1 = b.rank1(l), r1 = b.rank1(r);\n            u32 l0 = u32(l)\
    \ - l1, r0 = u32(r) - r1;\n            bool f = (U(upper) >> h) & 1;\n       \
    \     ret += f ? r0 - l0 : 0;\n            l = int(f ? b.zeros + l1 : l0);\n \
    \           r = int(f ? b.zeros + r1 : r0);\n        }\n        return int(ret);\n\
    \    }\n    int range_freq(int l, int r, T lower, T upper) const {\n        return\
    \ lower < upper ? range_freq(l, r, upper) - range_freq(l, r, lower) : 0;\n   \
    \ }\n    // Return T(-1) when no such value exists.\n    T prev_value(int l, int\
    \ r, T upper) const {\n        int cnt = range_freq(l, r, upper);\n        return\
    \ cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n    }\n    T next_value(int\
    \ l, int r, T lower) const {\n        int cnt = range_freq(l, r, lower);\n   \
    \     return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);\n    }\n};\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n\
    #include <limits>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace po167{\n// Nonnegative integer values; C++17, no required CPU extensions.\n\
    // Based on the API at:\n// https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html\n\
    struct bit_vector {\n    using u32 = std::uint32_t;\n    using u64 = std::uint64_t;\n\
    \    static constexpr u32 w = 32;\n\n    // Low 32 bits: data. High 32 bits: number\
    \ of preceding one-bits.\n    std::vector<u64> block;\n    u32 n = 0, zeros =\
    \ 0;\n\n    bit_vector(u32 size = 0) { init(size); }\n    void init(u32 size)\
    \ {\n        n = zeros = size;\n        block.assign(n / w + 1, 0);\n    }\n \
    \   static u32 popcount(u32 x) {\n        x -= (x >> 1) & 0x55555555u;\n     \
    \   x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);\n        x = (x + (x >>\
    \ 4)) & 0x0f0f0f0fu;\n        return u32(x * 0x01010101u) >> 24;\n    }\n    u32\
    \ get(u32 i) const { return (u32(block[i / w]) >> (i % w)) & 1; }\n    void set(u32\
    \ i) { block[i / w] |= u64(1) << (i % w); }\n    void build() {\n        u32 sum\
    \ = 0;\n        for (auto& x : block) {\n            u32 bits = u32(x);\n    \
    \        x = (u64(sum) << 32) | bits;\n            sum += popcount(bits);\n  \
    \      }\n        zeros = n - sum;\n    }\n    u32 rank1(u32 i) const {\n    \
    \    u64 x = block[i / w];\n        return u32(x >> 32) + popcount(u32(x) & ((u32(1)\
    \ << (i % w)) - 1));\n    }\n    u32 rank0(u32 i) const { return i - rank1(i);\
    \ }\n};\n\ntemplate <typename T, bool FastKth = true>\nstruct WaveletMatrix {\n\
    \    static_assert(std::is_integral<T>::value && !std::is_same<T, bool>::value,\n\
    \                  \"T must be a non-bool integer type\");\n    using U = typename\
    \ std::make_unsigned<T>::type;\n    using u32 = std::uint32_t;\n\n    int n =\
    \ 0, lg = 1, mid_h = -1;\n    T max_value = 0;\n    std::vector<T> a, mid;\n \
    \   std::vector<bit_vector> bv;\n\n    WaveletMatrix(u32 size) : n(int(size)),\
    \ a(size) {\n        assert(size <= u32((std::numeric_limits<int>::max)()));\n\
    \    }\n    WaveletMatrix(const std::vector<T>& values) : a(values) { build();\
    \ }\n\n    void set(u32 i, const T& x) {\n        assert(i < a.size() && x >=\
    \ 0);\n        a[i] = x;\n    }\n    void build() {\n        assert(a.size() <=\
    \ std::size_t((std::numeric_limits<int>::max)()));\n        n = int(a.size());\n\
    \        max_value = 0;\n        for (T x : a) {\n            assert(x >= 0);\n\
    \            if (max_value < x) max_value = x;\n        }\n        lg = 1;\n \
    \       for (U x = U(max_value); x >>= 1;) ++lg;\n        mid.clear();\n     \
    \   mid_h = lg - 2;\n        for (u32 x = u32(n); x; x >>= 1) --mid_h;\n     \
    \   bv.assign(lg, bit_vector(u32(n)));\n        std::vector<T> cur = a, nxt(n);\n\
    \        for (int h = lg - 1; h >= 0; --h) {\n            // Keep one intermediate\
    \ order to finish small candidate ranges.\n            if constexpr (FastKth)\
    \ {\n                if (h == mid_h) mid = cur;\n            }\n            auto&\
    \ b = bv[h];\n            for (u32 i = 0; i < u32(n); i += 32) {\n           \
    \     u32 bits = 0, len = (std::min)(u32(32), u32(n) - i);\n                for\
    \ (u32 j = 0; j < len; ++j)\n                    bits |= u32((U(cur[i + j]) >>\
    \ h) & 1) << j;\n                b.block[i / 32] = bits;\n            }\n    \
    \        b.build();\n            if (h == 0) break;\n            u32 pos[2] =\
    \ {0, b.zeros};\n            for (T x : cur) nxt[pos[(U(x) >> h) & 1]++] = x;\n\
    \            cur.swap(nxt);\n        }\n    }\n\n    std::pair<u32, u32> succ0(int\
    \ l, int r, int h) const {\n        return {bv[h].rank0(l), bv[h].rank0(r)};\n\
    \    }\n    std::pair<u32, u32> succ1(int l, int r, int h) const {\n        const\
    \ auto& b = bv[h];\n        return {b.zeros + b.rank1(l), b.zeros + b.rank1(r)};\n\
    \    }\n    T access(u32 k) const {\n        assert(k < a.size());\n        return\
    \ a[k];\n    }\n    T kth_smallest(u32 l, u32 r, u32 k) const {\n        assert(l\
    \ <= r && r <= u32(n) && k < r - l);\n        if (r - l == 1) return a[l];\n \
    \       U res = 0;\n        for (int h = lg - 1; h >= 0; --h) {\n            if\
    \ constexpr (FastKth) {\n                if (h == mid_h && r - l <= 2)\n     \
    \               return k ? (std::max)(mid[l], mid[r - 1])\n                  \
    \           : (std::min)(mid[l], mid[r - 1]);\n            }\n            const\
    \ auto& b = bv[h];\n            u32 l1 = b.rank1(l), r1 = b.rank1(r);\n      \
    \      u32 l0 = l - l1, r0 = r - r1, cnt = r0 - l0;\n            bool f = k >=\
    \ cnt;\n            k -= f ? cnt : 0;\n            res |= U(f) << h;\n       \
    \     l = f ? b.zeros + l1 : l0;\n            r = f ? b.zeros + r1 : r0;\n   \
    \     }\n        return T(res);\n    }\n    T kth_largest(int l, int r, int k)\
    \ const {\n        assert(0 <= k && k < r - l);\n        return kth_smallest(l,\
    \ r, r - l - k - 1);\n    }\n    int range_freq(int l, int r, T upper) const {\n\
    \        assert(0 <= l && l <= r && r <= n);\n        if (upper <= 0) return 0;\n\
    \        if (upper > max_value) return r - l;\n        u32 ret = 0;\n        for\
    \ (int h = lg - 1; h >= 0 && l < r; --h) {\n            const auto& b = bv[h];\n\
    \            u32 l1 = b.rank1(l), r1 = b.rank1(r);\n            u32 l0 = u32(l)\
    \ - l1, r0 = u32(r) - r1;\n            bool f = (U(upper) >> h) & 1;\n       \
    \     ret += f ? r0 - l0 : 0;\n            l = int(f ? b.zeros + l1 : l0);\n \
    \           r = int(f ? b.zeros + r1 : r0);\n        }\n        return int(ret);\n\
    \    }\n    int range_freq(int l, int r, T lower, T upper) const {\n        return\
    \ lower < upper ? range_freq(l, r, upper) - range_freq(l, r, lower) : 0;\n   \
    \ }\n    // Return T(-1) when no such value exists.\n    T prev_value(int l, int\
    \ r, T upper) const {\n        int cnt = range_freq(l, r, upper);\n        return\
    \ cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n    }\n    T next_value(int\
    \ l, int r, T lower) const {\n        int cnt = range_freq(l, r, lower);\n   \
    \     return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);\n    }\n};\n}"
  dependsOn: []
  isVerificationFile: false
  path: ds/WaveletMatrix.hpp
  requiredBy: []
  timestamp: '2026-10-21 21:31:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ds/waveletmatrix_1.test.cpp
  - test/ds/waveletmatrix_3.test.cpp
  - test/ds/waveletmatrix_4.test.cpp
  - test/ds/waveletmatrix_2.test.cpp
documentation_of: ds/WaveletMatrix.hpp
layout: document
redirect_from:
- /library/ds/WaveletMatrix.hpp
- /library/ds/WaveletMatrix.hpp.html
title: ds/WaveletMatrix.hpp
---
