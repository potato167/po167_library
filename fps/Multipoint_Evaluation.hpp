#pragma once
#include <atcoder/convolution>
#include "FPS_inv.hpp"
#include "FPS_Product_Sequence.hpp"

namespace po167{
// return {f(p[0]), f(p[1]), f(p[2]), ... }
// https://codeforces.com/blog/entry/100279
template<class T>
std::vector<T> Multipoint_Evaluation(std::vector<T> f, std::vector<T> p){
    std::reverse(f.begin(), f.end());
    int M = f.size();
    int N = p.size();
    std::vector<std::vector<T>> g(N);
    for (int i = 0; i < N; i++){
        g[i] = {1, p[i] * -1};
    }
    auto tmp = po167::FPS_Product_Sequence(g);
    tmp = po167::FPS_inv(tmp, M);
    tmp = atcoder::convolution(tmp, f);
    tmp.resize(M);
    int size = 1;
    while (size < N) size *= 2;
    std::vector<std::vector<T>> seg(size * 2, {1});
    for (int i = 0; i < N; i++){
        seg[i + size] = g[i];
    }
    for (int i = size - 1; i > 0; i--){
        seg[i] = atcoder::convolution(seg[i * 2], seg[i * 2 + 1]);
    }

    std::vector<T> inv = {1, (T)(1) / (T)(2)};
    // a, b の convolution のうち、l, r の間だけ欲しい
    auto calc = [&](std::vector<T> a, std::vector<T> b, int l, int r) -> std::vector<T> {
        if (l == r) return {};
        if (l < 0) l = 0;
        while ((int)a.size() > r) a.pop_back();
        while ((int)b.size() > r) b.pop_back();
        int lim = (int)a.size() + (int)b.size() - 1;
        lim -= std::min(lim - r, l);
        int z = 0;
        while ((1 << z) < lim) z++;
        a.resize((1 << z), 0);
        b.resize((1 << z), 0);
        atcoder::internal::butterfly(a);
        atcoder::internal::butterfly(b);
        for (int i = 0; i < (1 << z); i++) a[i] *= b[i];
        atcoder::internal::butterfly_inv(a);
        while ((int)inv.size() <= z){
            inv.push_back(inv.back() * inv[1]);
        }
        std::vector<T> d(r - l);
        for (int i = l; i < r; i++) d[i - l] = a[i] * inv[z];
        return d;
    };

    std::vector<T> res(N);
    auto rec = [&](auto self, int ind, std::vector<T> v) -> void {
        if ((int)seg[ind].size() == 1){
            return;
        }
        if (size <= ind){
            res[ind - size] = v.back();
            return;
        }
        self(self, ind * 2, calc(v, seg[ind * 2 + 1], (int)(v.size() - seg[ind * 2].size() + 1) ,(int)v.size()));
        self(self, ind * 2 + 1, calc(v, seg[ind * 2], (int)(v.size() - seg[ind * 2 + 1].size() + 1) ,(int)v.size()));
    };
    rec(rec, 1, tmp);
    return res;
}
}