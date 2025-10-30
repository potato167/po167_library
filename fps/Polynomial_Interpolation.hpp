#pragma once
#include "FPS_Product_Sequence.hpp"
#include "Multipoint_Evaluation.hpp"
#include "FPS_add.hpp"

namespace po167{
template<class T>
// ラグランジュの多項式補完
// f(X[i]) = Y[i] である f を返す
std::vector<T> Polynomial_Interpolation(std::vector<int> X, std::vector<T> Y){
    int N = X.size();
    assert(Y.size() == X.size());
    if (N == 0) return {};
    {
        auto Z = X;
        std::sort(Z.begin(), Z.end());
        for (int i = 0; i < N - 1; i++){
            assert(Z[i] != Z[i + 1]);
        }
    }
    std::vector<std::vector<T>> p(N);
    for (int i = 0; i < N; i++) p[i] = {-X[i], 1};
    auto g = FPS_Product_Sequence(p);
    for (int i = 0; i < N; i++){
        g[i] = g[i + 1] * (i + 1);
    }
    g.pop_back();
    std::vector<T> xt(N);
    for (int i = 0; i < N; i++) xt[i] = X[i];
    auto Z = Multipoint_Evaluation(g, xt);
    std::vector<T> inv = {1, (T)(1) / (T)(2)};
    auto rec = [&](auto self, int l, int r) -> std::pair<std::vector<T>, std::vector<T>> {
        if (l + 1 == r){
            return {{Y[l] / Z[l]}, {-X[l], 1}};
        }
        int m = (l + r) / 2;
        auto [Lf, Ls] = self(self, l, m);
        auto [Rf, Rs] = self(self, m, r);
        int mx_size = r - l + 1;
        if (mx_size < 128){
            auto D = atcoder::convolution(Ls, Rs);
            auto U = atcoder::convolution(Ls, Rf);
            FPS_add(U, atcoder::convolution(Lf, Rs));
            return {U, D};
        }
        int z = 0;
        while ((1 << z) < mx_size) z++;
        while (int(inv.size()) <= z) inv.push_back(inv.back() * inv[1]);
        Lf.resize(1 << z, 0);
        Ls.resize(1 << z, 0);
        Rf.resize(1 << z, 0);
        Rs.resize(1 << z, 0);
        atcoder::internal::butterfly(Lf);
        atcoder::internal::butterfly(Ls);
        atcoder::internal::butterfly(Rf);
        atcoder::internal::butterfly(Rs);
        std::vector<T> D(1 << z), U(1 << z);
        for (int i = 0; i < (1 << z); i++){
            D[i] = Ls[i] * Rs[i] * inv[z];
            U[i] = (Ls[i] * Rf[i] + Lf[i] * Rs[i]) * inv[z];
        }
        atcoder::internal::butterfly_inv(D);
        atcoder::internal::butterfly_inv(U);
        D.resize(r - l + 1);
        U.resize(r - l);
        return {U, D};
    };
    return rec(rec, 0, N).first;
}
}
