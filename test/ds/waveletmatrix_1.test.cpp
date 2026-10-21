#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

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
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << wm.kth_smallest(l, r, k) << "\n";
    }
}