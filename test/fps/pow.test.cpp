#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "../../fps/FPS_pow.hpp"

#include <vector>
#include <iostream>
#include <atcoder/modint>


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    long long M;
    std::cin >> N >> M;
    std::vector<atcoder::modint998244353> A(N);
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        A[i] = a;
    }
    auto B = po167::FPS_pow(A, M);
    for (int i = 0; i < N; i++){
        if (i) std::cout << " ";
        std::cout << B[i].val();
    }
    std::cout << "\n";
}