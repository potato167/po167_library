#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <atcoder/convolution>
#include "FPS_inv.hpp"

namespace po167 {
namespace internal {

// Q(0) != 0, 0 < r; [x^i]P(x)/Q(x) = 0 (i < 0).
// return { [x^i]P(x)/Q(x) : l <= i < r }.
template<class T>
std::vector<T> fps_div_consecutive(long long l, long long r,
                                  std::vector<T> P, std::vector<T> Q) {
    assert(0 < r);
    if (l >= r) return {};
    assert(!Q.empty() && Q[0] != T(0));
    std::vector<T> res(r - l);
    if (P.empty()) return res;
    while (Q.size() > 1 && Q.back() == T(0)) Q.pop_back();
    while (P.size() > 1 && P.back() == T(0)) P.pop_back();
    int p = P.size(), q = Q.size();
    long long L = std::max(0LL, l);
    if (p == 1 && P[0] == T(0)) return res;
    if (q == 1) {
        T inv = T(1) / Q[0];
        for (long long i = L; i < r && i < p; ++i) res[i - l] = P[i] * inv;
        return res;
    }
    if (r <= 4LL * q) {
        auto B = FPS_inv(std::move(Q), int(r));
        if (p > 1) {
            P.resize(std::min<long long>(p, r));
            B = atcoder::convolution(std::move(P), std::move(B));
        }
        T scale = p == 1 ? P[0] : T(1);
        for (long long i = L; i < r; ++i) res[i - l] = B[i] * scale;
        return res;
    }
    int h = p + q - 1, n = 1;
    while (n < q - 1 || 2LL * n < r - L + h - 1) n *= 2;
    assert((T::mod() - 1) % (2 * n) == 0);
    T top = q == n + 1 ? Q.back() * Q.back() * T(1 - 2 * (n & 1)) : T(0);
    Q.resize(2 * n);
    atcoder::internal::butterfly(Q);

    // C(x^2) = Q_original(x) Q_original(-x).
    std::vector<T> C(n);
    for (int i = 0; i < n; ++i) C[i] = Q[2 * i] * Q[2 * i + 1];
    atcoder::internal::butterfly_inv(C);
    C.resize(q);
    T inv_n = T(1) / T(n);
    for (auto &x : C) x *= inv_n;
    if (q == n + 1) {
        C[0] -= top;
        C[n] = top;
    }
    long long nl = std::max(0LL, (L - h + 2) / 2), nr = r / 2 + r % 2;
    auto D = fps_div_consecutive(nl, nr, std::vector<T>{T(1)}, std::move(C));
    D.resize(n);
    atcoder::internal::butterfly(D);

    // P(x) Q_original(-x) D(x^2) mod (x^(2n) - 1).
    if (p > 1) {
        P.resize(2 * n);
        atcoder::internal::butterfly(P);
        for (int i = 0; i < 2 * n; ++i) Q[i] *= P[i ^ 1];
    }
    for (int i = 0; i < n; ++i) {
        std::swap(Q[2 * i], Q[2 * i + 1]);
        Q[2 * i] *= D[i];
        Q[2 * i + 1] *= D[i];
    }
    atcoder::internal::butterfly_inv(Q);
    T scale = (p == 1 ? P[0] : T(1)) / T(2 * n);
    for (long long i = L; i < r; ++i) res[i - l] = Q[i - 2 * nl] * scale;
    return res;
}

} // namespace internal

// A(0) != 0, 0 < r; B(x) = 1/A(x), B_i = 0 (i < 0).
// return { B_l, B_(l+1), ..., B_(r-1) }.
template<class T>
std::vector<T> FPS_Inv_Consecutive(long long l, long long r, std::vector<T> A) {
    return internal::fps_div_consecutive(l, r, std::vector<T>{T(1)}, std::move(A));
}

// d = |a|, |c| = d+1, c[0] != 0, 0 < r.
// sum_{j=0}^d c[j] a[i-j] = 0 (i >= d); a[i] = 0 (i < 0).
// return { a[l], a[l+1], ..., a[r-1] }.
template<class T>
std::vector<T> Consecutive_Linear(long long l, long long r,
                                 std::vector<T> a, std::vector<T> c) {
    assert(0 < r && a.size() + 1 == c.size() && c[0] != T(0));
    if (l >= r) return {};
    int d = a.size();
    if (r <= d) {
        std::vector<T> res(r - l);
        for (long long i = std::max(0LL, l); i < r; ++i) res[i - l] = a[i];
        return res;
    }
    a = atcoder::convolution(a, c);
    a.resize(d);
    return internal::fps_div_consecutive(l, r, std::move(a), std::move(c));
}

} // namespace po167