#pragma once
#include <vector>
#include <atcoder/convolution>

#include "../fps/FPS_pick_even_odd.hpp"

namespace po167{
// n = |g|
// return 
// for i = 0, 1, ... , m - 1
//     [x ^ {n - 1}] g(x) f(x) ^ i
template<class T>
std::vector<T> Power_Projection(std::vector<T> g, std::vector<T> f, int m){
    int ind = (int)g.size() - 1;
    int n = 1;
    while(n < (int)g.size()) n *= 2;
    f.reserve(4 * n);
    g.reserve(4 * n);
    g.resize(n, 0);
    f.resize(n, 0);
    std::vector<T> hold_f(n), hold_g(n);
    // g(x) / (y - f(x))
    for (auto &x : f) x *= -1;
    int nk = n;
    T iz = (T)(1) / (T)(2 * n);
    while (nk != 1){
        hold_g = g;
        hold_f = f;
        // n -> 4 * n
        g.resize(4 * n);
        f.resize(4 * n);
        for (int i = n / nk - 1; i >= 0; i--){
            for (int j = nk - 1; j >= 0; j--){
                g[i * nk * 2 + j] = g[i * nk + j];
                if (i) g[i * nk + j] = 0;
                f[i * nk * 2 + j] = f[i * nk + j];
                if (i) f[i * nk + j] = 0;
            }
        }
        // tran
        atcoder::internal::butterfly(g);
        atcoder::internal::butterfly(f);
        for (int i = 0; i < 2 * n; i++){
            g[i * 2] *= f[i * 2 + 1];
            g[i * 2 + 1] *= f[i * 2];
            f[i * 2] *= f[i * 2 + 1];
            f[i * 2 + 1] = f[i * 2];
        }
        FPS_pick_even_odd(g, (ind & 1));
        FPS_pick_even_odd(f, 0);
        atcoder::internal::butterfly_inv(g);
        atcoder::internal::butterfly_inv(f);
        for (auto &x : g) x *= iz;
        for (auto &x : f) x *= iz;
        // y ^ nk
        for (int i = 0; i < n; i++){
            if ((ind + i + 1) & 1)
                g[n + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_g[i];
            if ((i & 1) == 0)
                f[n + (i / nk) * nk + (i & (nk - 1)) / 2] += hold_f[i] * 2;
        }
        nk /= 2;
        for (int i = 0; i < n; i++){
            g[i] = g[(i / nk) * nk * 2 + (i & (nk - 1))];
            f[i] = f[(i / nk) * nk * 2 + (i & (nk - 1))];
        }
        g.resize(n);
        f.resize(n);
        ind /= 2;
    }
    f.push_back(1);
    std::reverse(g.begin(), g.end());
    std::reverse(f.begin(), f.end());
    g.resize(m);
    std::vector<T> ans = atcoder::convolution(g, FPS_inv(f, m));
    ans.resize(m);
    return ans;
}
}