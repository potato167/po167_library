#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../../fps/FPS_exp.hpp"

#include <vector>
#include <iostream>
#include <atcoder/modint>

int main(){
    int N;
    std::cin >> N;
    std::vector<atcoder::modint998244353> A(N);
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        A[i] = a;
    }
    auto B = po167::FPS_exp(A);
    for (int i = 0; i < N; i++){
        std::cout << B[i].val() << (i == N - 1 ? "\n" : " ");
    }
}