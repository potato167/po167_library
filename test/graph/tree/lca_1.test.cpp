#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../../graph/tree/LCA.hpp"
#include <iostream>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> pare(N, -1);
    for (int i = 1; i < N; i++) std::cin >> pare[i];
    po167::LCA L(pare);
    while (Q--){
        int a, b;
        std::cin >> a >> b;
        std::cout << L.lca(a, b) << "\n";
    }
}