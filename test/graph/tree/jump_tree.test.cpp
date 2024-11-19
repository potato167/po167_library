#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../../graph/tree/LCA.hpp"
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::vector<int>> g(N);
    for (int i = 0; i < N - 1; i++){
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    po167::LCA L(g);
    while (Q--){
        int s, t, k;
        std::cin >> s >> t >> k;
        std::cout << L.jump(s, t, k) << "\n";
    }
}