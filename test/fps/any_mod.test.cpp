#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../fps/any_mod.hpp"
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    using mint = atcoder::modint1000000007;
    int N, M;
    std::cin >> N >> M;
    std::vector<mint> A(N), B(M);
    int a;
    for (int i = 0; i < N; i++) std::cin >> a, A[i] = a;
    for (int i = 0; i < M; i++) std::cin >> a, B[i] = a;
    auto C = po167::convolution_mint(A, B);
    for (int i = 0; i < N + M - 1; i++){
        if (i) std::cout << " ";
        std::cout << C[i].val();
    }
    std::cout << "\n";
}