#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../ds/Doubling.hpp"

int op(int a, int b){
    return std::min(a, b);
}

#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N), P(N);
    for (int i = 0; i < N; i++){
        std::cin >> A[i];
        P[i] = std::min(i + 1, N - 1);
    }
    po167::Doubling_op<int, op> D(P, A, N);
    while (Q--){
        int l, r;
        std::cin >> l >> r;
        std::cout << D.query(l, 1 << 30, r - l).second << "\n";
    }
}