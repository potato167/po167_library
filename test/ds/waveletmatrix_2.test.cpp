#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include "../../ds/WaveletMatrix.hpp"
#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &a : A) std::cin >> a;

    po167::WaveletMatrix<int> wm(A);
    while (Q--){
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << wm.range_freq(l, r, x, x + 1) << "\n";
    }
}