#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

namespace po167{
// Nonnegative integer values; C++17, no required CPU extensions.
// Based on the API at:
// https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html
struct bit_vector {
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    static constexpr u32 w = 32;

    // Low 32 bits: data. High 32 bits: number of preceding one-bits.
    std::vector<u64> block;
    u32 n = 0, zeros = 0;

    bit_vector(u32 size = 0) { init(size); }
    void init(u32 size) {
        n = zeros = size;
        block.assign(n / w + 1, 0);
    }
    static u32 popcount(u32 x) {
        x -= (x >> 1) & 0x55555555u;
        x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
        x = (x + (x >> 4)) & 0x0f0f0f0fu;
        return u32(x * 0x01010101u) >> 24;
    }
    u32 get(u32 i) const { return (u32(block[i / w]) >> (i % w)) & 1; }
    void set(u32 i) { block[i / w] |= u64(1) << (i % w); }
    void build() {
        u32 sum = 0;
        for (auto& x : block) {
            u32 bits = u32(x);
            x = (u64(sum) << 32) | bits;
            sum += popcount(bits);
        }
        zeros = n - sum;
    }
    u32 rank1(u32 i) const {
        u64 x = block[i / w];
        return u32(x >> 32) + popcount(u32(x) & ((u32(1) << (i % w)) - 1));
    }
    u32 rank0(u32 i) const { return i - rank1(i); }
};

template <typename T, bool FastKth = true>
struct WaveletMatrix {
    static_assert(std::is_integral<T>::value && !std::is_same<T, bool>::value,
                  "T must be a non-bool integer type");
    using U = typename std::make_unsigned<T>::type;
    using u32 = std::uint32_t;

    int n = 0, lg = 1, mid_h = -1;
    T max_value = 0;
    std::vector<T> a, mid;
    std::vector<bit_vector> bv;

    WaveletMatrix(u32 size) : n(int(size)), a(size) {
        assert(size <= u32((std::numeric_limits<int>::max)()));
    }
    WaveletMatrix(const std::vector<T>& values) : a(values) { build(); }

    void set(u32 i, const T& x) {
        assert(i < a.size() && x >= 0);
        a[i] = x;
    }
    void build() {
        assert(a.size() <= std::size_t((std::numeric_limits<int>::max)()));
        n = int(a.size());
        max_value = 0;
        for (T x : a) {
            assert(x >= 0);
            if (max_value < x) max_value = x;
        }
        lg = 1;
        for (U x = U(max_value); x >>= 1;) ++lg;
        mid.clear();
        mid_h = lg - 2;
        for (u32 x = u32(n); x; x >>= 1) --mid_h;
        bv.assign(lg, bit_vector(u32(n)));
        std::vector<T> cur = a, nxt(n);
        for (int h = lg - 1; h >= 0; --h) {
            // Keep one intermediate order to finish small candidate ranges.
            if constexpr (FastKth) {
                if (h == mid_h) mid = cur;
            }
            auto& b = bv[h];
            for (u32 i = 0; i < u32(n); i += 32) {
                u32 bits = 0, len = (std::min)(u32(32), u32(n) - i);
                for (u32 j = 0; j < len; ++j)
                    bits |= u32((U(cur[i + j]) >> h) & 1) << j;
                b.block[i / 32] = bits;
            }
            b.build();
            if (h == 0) break;
            u32 pos[2] = {0, b.zeros};
            for (T x : cur) nxt[pos[(U(x) >> h) & 1]++] = x;
            cur.swap(nxt);
        }
    }

    std::pair<u32, u32> succ0(int l, int r, int h) const {
        return {bv[h].rank0(l), bv[h].rank0(r)};
    }
    std::pair<u32, u32> succ1(int l, int r, int h) const {
        const auto& b = bv[h];
        return {b.zeros + b.rank1(l), b.zeros + b.rank1(r)};
    }
    T access(u32 k) const {
        assert(k < a.size());
        return a[k];
    }
    T kth_smallest(u32 l, u32 r, u32 k) const {
        assert(l <= r && r <= u32(n) && k < r - l);
        if (r - l == 1) return a[l];
        U res = 0;
        for (int h = lg - 1; h >= 0; --h) {
            if constexpr (FastKth) {
                if (h == mid_h && r - l <= 2)
                    return k ? (std::max)(mid[l], mid[r - 1])
                             : (std::min)(mid[l], mid[r - 1]);
            }
            const auto& b = bv[h];
            u32 l1 = b.rank1(l), r1 = b.rank1(r);
            u32 l0 = l - l1, r0 = r - r1, cnt = r0 - l0;
            bool f = k >= cnt;
            k -= f ? cnt : 0;
            res |= U(f) << h;
            l = f ? b.zeros + l1 : l0;
            r = f ? b.zeros + r1 : r0;
        }
        return T(res);
    }
    T kth_largest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        return kth_smallest(l, r, r - l - k - 1);
    }
    int range_freq(int l, int r, T upper) const {
        assert(0 <= l && l <= r && r <= n);
        if (upper <= 0) return 0;
        if (upper > max_value) return r - l;
        u32 ret = 0;
        for (int h = lg - 1; h >= 0 && l < r; --h) {
            const auto& b = bv[h];
            u32 l1 = b.rank1(l), r1 = b.rank1(r);
            u32 l0 = u32(l) - l1, r0 = u32(r) - r1;
            bool f = (U(upper) >> h) & 1;
            ret += f ? r0 - l0 : 0;
            l = int(f ? b.zeros + l1 : l0);
            r = int(f ? b.zeros + r1 : r0);
        }
        return int(ret);
    }
    int range_freq(int l, int r, T lower, T upper) const {
        return lower < upper ? range_freq(l, r, upper) - range_freq(l, r, lower) : 0;
    }
    // Return T(-1) when no such value exists.
    T prev_value(int l, int r, T upper) const {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }
    T next_value(int l, int r, T lower) const {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }
};
}