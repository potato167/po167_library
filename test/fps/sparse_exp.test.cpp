#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "../../fps/FPS_sparse.hpp"

#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint998244353;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, K;
    std::cin >> N >> K;
    std::vector<mint> f(N);
    for (int i = 0; i < K; i++){
        int a, b;
        std::cin >> a >> b;
        f[a] = b;
    }
    auto ans = po167::FPS_sparse_exp(f);
    for (int i = 0; i < N; i++){
        std::cout << ans[i].val() << (i + 1 == N ? "\n" : " ");
    }
}