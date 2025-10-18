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
    auto rec = [&](auto self, int l, int r) -> std::pair<std::vector<T>, std::vector<T>> {
        if (l + 1 == r){
            return {{Y[l] / Z[l]}, {-X[l], 1}};
        }
        int m = (l + r) / 2;
        auto L = self(self, l, m);
        auto R = self(self, m, r);
        auto D = atcoder::convolution(L.second, R.second);
        auto U = atcoder::convolution(L.second, R.first);
        FPS_add(U, atcoder::convolution(L.first, R.second));
        return {U, D};
    };
    return rec(rec, 0, N).first;
}
}
