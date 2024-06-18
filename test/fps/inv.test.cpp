#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"
#include "../../fps/FPS_inv.hpp"

#include <vector>
#include <iostream>
#include <atcoder/modint>

int main(){
    using mint = atcoder::modint998244353;
    int N;
    std::cin >> N;
    std::vector<mint> A(N);
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        A[i] = a;
    }
    A = po167::FPS_inv(A, N);
    for (int i = 0; i < N; i++){
        std::cout << A[i].val() << " ";
    }
    std::cout << "\n";
}