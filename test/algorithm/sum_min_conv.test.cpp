#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include "../../algorithm/sum_max_convolution.hpp"

#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N), B(M);
    for (auto &a : A) std::cin >> a, a *= -1;
    for (auto &b : B) std::cin >> b, b *= -1;
    auto c = po167::sum_max_convolution(A, B);
    for (int i = 0; i < N + M - 1; i++){
        if (i) std::cout << " ";
        std::cout << -c[i];
    }
    std::cout << "\n";
}