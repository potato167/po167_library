#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <atcoder/convolution>

namespace po167 {

// c[k] = sum_{i+j=k} a[i] * b[j] (mod pmod), 0 <= c[k] < pmod.
// 1 <= pmod, |a| + |b| - 1 <= 2^24 (unless an input is empty).
// After normalization to [0, pmod), each integer coefficient must be
// < 754974721 * 167772161 * 469762049.
// This is automatic for pmod <= 2^31 - 1 under the length bound above.
inline std::vector<long long> convolution_any_mod(
    std::vector<long long> a, std::vector<long long> b, long long pmod) {
    assert(pmod >= 1);
    if (a.empty() || b.empty()) return {};
    assert(a.size() + b.size() - 1 <= (1 << 24));
    int n = (int)a.size(), m = (int)b.size(), s = n + m - 1;
    if (pmod == 1) return std::vector<long long>(s);

    constexpr long long m0 = 754974721, m1 = 167772161, m2 = 469762049;
    if (pmod == m0) return atcoder::convolution<m0>(a, b);
    if (pmod == m1) return atcoder::convolution<m1>(a, b);
    if (pmod == m2) return atcoder::convolution<m2>(a, b);
    if (pmod == 998244353 && s <= (1 << 23))
        return atcoder::convolution<998244353>(a, b);

    for (auto &x : a) if (x < 0 || x >= pmod) {
        x %= pmod;
        if (x < 0) x += pmod;
    }
    for (auto &x : b) if (x < 0 || x >= pmod) {
        x %= pmod;
        if (x < 0) x += pmod;
    }
    if (std::min(n, m) <= 256) {
        std::vector<long long> c(s);
        for (int k = 0; k < s; ++k) {
            __int128 sum = 0;
            for (int i = std::max(0, k - m + 1); i < std::min(n, k + 1); ++i)
                sum += (__int128)a[i] * b[k - i];
            c[k] = (long long)(sum % pmod);
        }
        return c;
    }

    auto conv = [&](auto zero) {
        using mint = decltype(zero);
        return atcoder::convolution(std::vector<mint>(a.begin(), a.end()),
                                    std::vector<mint>(b.begin(), b.end()));
    };
    auto c0 = conv(atcoder::static_modint<m0>());
    auto c1 = conv(atcoder::static_modint<m1>());
    auto c2 = conv(atcoder::static_modint<m2>());
    std::vector<long long> c(s);
    long long m01 = m0 * m1 % pmod;
    // 95869806 = m0^(-1) mod m1, 187290749 = (m0*m1)^(-1) mod m2.
    for (int i = 0; i < s; ++i) {
        long long x = (c1[i].val() - (long long)c0[i].val()) * 95869806 % m1;
        if (x < 0) x += m1;
        x = c0[i].val() + m0 * x;
        long long y = (c2[i].val() - x % m2) * 187290749 % m2;
        if (y < 0) y += m2;
        c[i] = pmod <= 2147483647
            ? (x + m01 * y) % pmod
            : (long long)((x + (__int128)m01 * y) % pmod);
    }
    return c;
}

template<class T>
std::vector<T> convolution_mint(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    std::vector<long long> A(a.size()), B(b.size());
    for (int i = 0; i < (int)a.size(); ++i) A[i] = a[i].val();
    for (int i = 0; i < (int)b.size(); ++i) B[i] = b[i].val();
    auto c = convolution_any_mod(std::move(A), std::move(B), T::mod());
    return std::vector<T>(c.begin(), c.end());
}

} // namespace po167