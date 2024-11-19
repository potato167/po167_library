#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../../ds/Sparce_table.hpp"
#include <iostream>

int op(int a, int b){
    return std::min(a, b);
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &a : A) std::cin >> a;
    po167::Sparce_table<int, op> table(A);
    while (Q--){
        int l, r;
        std::cin >> l >> r;
        std::cout << table.prod(l, r) << "\n";
    }
}