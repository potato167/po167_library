#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <atcoder/convolution>

namespace po167 {

// N = |g|, g[0] = 0.
// return { [x^i] f(g(x)) : 0 <= i < N }.
// https://maspypy.github.io/library/poly/composition.hpp
template<class T>
std::vector<T> FPS_comp(std::vector<T> f, std::vector<T> g) {
    int N = g.size(), size = 1;
    if (!N) return {};
    assert(g[0] == T(0));
    if (f.empty()) return std::vector<T>(N);
    if (N == 1) return {f[0]};
    while (size < N) size *= 2;
    assert((T::mod() - 1) % (2 * size) == 0);
    f.resize(size);
    g.resize(4 * size);
    for (int i = 0; i < N; ++i) g[i] = -g[i];

    // Forward / inverse NTT, or its transpose.
    auto fft = [](std::vector<T>& a, bool inverse, bool transpose) {
        if (inverse && transpose) std::reverse(a.begin() + 1, a.end());
        if (inverse != transpose) atcoder::internal::butterfly_inv(a);
        else atcoder::internal::butterfly(a);
        if (!inverse && transpose) std::reverse(a.begin() + 1, a.end());
        if (inverse) {
            T scale = T(T::mod() - (T::mod() - 1) / int(a.size()));
            for (auto &x : a) x *= scale;
        }
    };
    std::vector<T> W(size);
    W[0] = 1;
    static const atcoder::internal::fft_info<T> info;
    for (int m = 1, h = 2; m < size; m *= 2, ++h) {
        for (int i = 0; i < m; ++i) W[m + i] = W[i] * info.iroot[h];
    }

    auto rec = [&](auto&& self, int n, int k, std::vector<T> Q) -> std::vector<T> {
        if (n == 1) {
            std::reverse(f.begin(), f.end());
            fft(f, true, true);
            T scale = T(1) / T(k);
            std::vector<T> p(4 * size);
            for (int i = 0; i < k; ++i) p[2 * i] = f[i] * scale;
            return p;
        }
        auto double_y = [&](std::vector<T>& a, int l, int r, bool transpose) {
            std::vector<T> v(k);
            T z = T(1) / W[k / 2];
            for (int i = l; i < r; ++i) {
                for (int j = 0; j < k; ++j) v[j] = a[2 * n * (j + (transpose ? k : 0)) + i];
                fft(v, !transpose, transpose);
                T power = 1;
                for (int j = 1; j < k; ++j) {
                    power *= z;
                    v[j] *= power;
                }
                fft(v, transpose, transpose);
                for (int j = 0; j < k; ++j) {
                    if (transpose) a[2 * n * j + i] += v[j];
                    else a[2 * n * (k + j) + i] = v[j];
                }
            }
        };
        auto fft_x = [&](std::vector<T>& a, int count, bool transpose) {
            std::vector<T> v(2 * n);
            for (int j = 0; j < count; ++j) {
                std::copy_n(a.begin() + 2 * n * j, 2 * n, v.begin());
                fft(v, false, transpose);
                std::copy(v.begin(), v.end(), a.begin() + 2 * n * j);
            }
        };
        if (n <= k) {
            double_y(Q, 1, n, false);
            fft_x(Q, 2 * k, false);
        } else {
            fft_x(Q, k, false);
            double_y(Q, 0, 2 * n, false);
        }
        for (int i = 0; i < 2 * size; ++i) Q[i] += 1;
        for (int i = 2 * size; i < 4 * size; ++i) Q[i] -= 1;

        std::vector<T> next(4 * size), v(n);
        for (int j = 0; j < 2 * k; ++j) {
            for (int i = 0; i < n; ++i) v[i] = Q[2 * n * j + 2 * i] * Q[2 * n * j + 2 * i + 1];
            fft(v, true, false);
            for (int i = 1; i < n / 2; ++i) next[n * j + i] = v[i];
        }
        auto p = self(self, n / 2, 2 * k, std::move(next));
        for (int j = 2 * k - 1; j >= 0; --j) {
            std::copy_n(p.begin() + n * j, n / 2, v.begin());
            std::fill(v.begin() + n / 2, v.end(), T(0));
            fft(v, true, true);
            for (int i = 0; i < n; ++i) {
                T x = v[i] * W[i];
                p[2 * n * j + 2 * i] = Q[2 * n * j + 2 * i + 1] * x;
                p[2 * n * j + 2 * i + 1] = -Q[2 * n * j + 2 * i] * x;
            }
        }
        if (n <= k) {
            fft_x(p, 2 * k, true);
            double_y(p, 0, n, true);
        } else {
            double_y(p, 0, 2 * n, true);
            fft_x(p, k, true);
        }
        return p;
    };
    auto p = rec(rec, size, 1, std::move(g));
    p.resize(size);
    std::reverse(p.begin(), p.end());
    p.resize(N);
    return p;
}

} // namespace po167
