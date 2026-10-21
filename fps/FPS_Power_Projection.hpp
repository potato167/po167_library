#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include <atcoder/convolution>
#include "../fps/FPS_pick_even_odd.hpp"

namespace po167 {
// Return [x^(g.size()-1)] g(x)f(x)^i for 0 <= i < m.
template<class T>
std::vector<T> Power_Projection(std::vector<T> g, std::vector<T> f, int m) {
    assert(m >= 0);
    if (m == 0) return {};
    assert(!g.empty() && !f.empty() && f[0] == 0);
    const int len = static_cast<int>(g.size()), need = std::min(m, len);
    std::vector<T> ans(m);
    if (need <= 32) {
        int b = 1;
        while (b * b < need) ++b;
        std::vector<std::vector<T>> power(std::min(b, need - 1) + 1);
        f.resize(std::min(len, static_cast<int>(f.size())));
        if (need > 1) power[1] = std::move(f);
        for (int i = 2; i < static_cast<int>(power.size()); ++i) {
            power[i] = atcoder::convolution(power[i - 1], power[1]);
            if (static_cast<int>(power[i].size()) > len) power[i].resize(len);
        }
        for (int j = 0; j < need; j += b) {
            ans[j] = g.back();
            for (int i = 1; i < b && j + i < need; ++i)
                for (int t = 0; t < static_cast<int>(power[i].size()); ++t)
                    ans[j + i] += g[len - 1 - t] * power[i][t];
            if (j + b < need) {
                g = atcoder::convolution(g, power[b]);
                g.resize(len);
            }
        }
        return ans;
    }
    int k = 1, d = 1, cap = 1, ind = len - 1;
    while (k < len) k *= 2;
    while (cap < need) cap *= 2;
    g.resize(k); f.resize(k);
    for (T& x : f) x = -x;
    std::vector<T> a, b, e;
    assert((T::mod() - 1) % (2 * k) == 0);
    std::vector<T> weight(2 * k);
    for (int i = 0; i < k; ++i) weight[2 * i] = 1;
    po167::FPS_pick_even_odd(weight, 1);
    T q = 1;
    while (k > 1) {
        const int dy = d == 1 ? 1 : 2 * d, h = k / 2, nd = std::min(2 * d, cap);
        g.resize(k * dy); f.resize(k * dy);
        // Retain the old y-NTT values and append the missing half.
        if (d > 1) {
            e.resize(d); e[0] = T(d).inv();
            const T root = T(atcoder::internal::primitive_root_constexpr(T::mod())).pow((T::mod() - 1) / dy);
            for (int i = 1; i < d; ++i) e[i] = e[i - 1] * root;
            for (int j = k - 1; j >= 0; --j) for (int t = 0; t < 2; ++t) {
                if (t && !j) continue;
                auto& v = t ? f : g;
                a.assign(v.begin() + j * d, v.begin() + (j + 1) * d);
                atcoder::internal::butterfly_inv(a);
                if (t) a[0] = -a[0]; // Q stores its y^d term at index 0.
                for (int i = 0; i < d; ++i) a[i] *= e[i];
                atcoder::internal::butterfly(a);
                if (j) std::copy_n(v.begin() + j * d, d, v.begin() + j * dy);
                std::copy_n(a.begin(), d, v.begin() + j * dy + d);
            }
        }
        if (k == 2) {
            for (int i = 0; i < dy; ++i) g[i] = g[dy + i] * q - g[i] * f[dy + i];
            q *= q; d = dy;
            break;
        }
        a.clear(); b.clear();
        for (int i = 0; i < dy; ++i) {
            a.resize(2 * k); b.resize(2 * k);
            for (int j = 0; j < k; ++j) { a[j] = g[j * dy + i]; b[j] = j || d == 1 ? f[j * dy + i] : q; }
            atcoder::internal::butterfly(a);
            atcoder::internal::butterfly(b);
            for (int j = 0; j < k; ++j) {
                const T x = b[2 * j], y = b[2 * j + 1];
                const auto u = 1ULL * a[2 * j].val() * y.val();
                const auto v = 1ULL * a[2 * j + 1].val() * x.val();
                const auto z = (u + ((ind & 1) ? 1ULL * T::mod() * T::mod() - v : v)) % T::mod();
                a[j] = ind & 1 ? T::raw(z) * weight[j] : T::raw((z + (z & 1) * T::mod()) >> 1);
                b[j] = x * y;
            }
            a.resize(k); b.resize(k);
            atcoder::internal::butterfly_inv(a);
            atcoder::internal::butterfly_inv(b);
            if (d == 1) for (int j = 0; j < h; ++j) {
                const T x = T(k) * g[2 * j + (ind & 1)], y = T(2 * k) * f[2 * j];
                g[2 * j] = x + a[j]; g[2 * j + 1] = x - a[j];
                f[2 * j] = b[j] + y; f[2 * j + 1] = b[j] - y;
            }
            else for (int j = 0; j < h; ++j) { g[j * dy + i] = a[j]; if (j) f[j * dy + i] = b[j]; }
        }
        q *= T(k) * q;
        if (nd < dy) {
            for (int j = 0; j < h; ++j) {
                a.assign(g.begin() + j * dy, g.begin() + (j + 1) * dy);
                atcoder::internal::butterfly_inv(a);
                a.resize(nd); atcoder::internal::butterfly(a);
                std::copy_n(a.begin(), nd, g.begin() + j * nd);
                if (j) {
                    b.assign(f.begin() + j * dy, f.begin() + (j + 1) * dy);
                    atcoder::internal::butterfly_inv(b);
                    b[0] = b[nd]; b.resize(nd); atcoder::internal::butterfly(b);
                    std::copy_n(b.begin(), nd, f.begin() + j * nd);
                }
            }
            q *= dy;
        }
        k = h; d = nd; ind /= 2;
    }
    g.resize(d);
    atcoder::internal::butterfly_inv(g);
    const T iq = (q * d).inv();
    for (int i = 0; i < need; ++i) ans[i] = g[i] * iq;
    return ans;
}
} // namespace po167