#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../fps/Polynomial_Interpolation.hpp"

#include <iostream>
using mint = atcoder::modint998244353;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    std::vector<int> X(N);
    std::vector<mint> Y(N);
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        X[i] = a;
    }
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        Y[i] = a;
    }
    auto ans = po167::Polynomial_Interpolation(X, Y);
    for (int i = 0; i < N; i++){
        std::cout << ans[i].val() << (i + 1 == N ? "\n" : " ");
    }
}