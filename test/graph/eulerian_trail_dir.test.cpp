#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

// #include "graph/Eulerian_trail.hpp"
#include "../../../graph/Eulerian_trail.hpp"
#include <iostream>
void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) solve();
}

void solve(){
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<std::pair<int, int>>> G(N);
    for (int i = 0; i < M; i++){
        int a, b;
        std::cin >> a >> b;
        G[a].push_back({b, i});
        // G[b].push_back({a, i});
    }
    auto [var, edge] = po167::Eulerian_trail(G, M, -1, true);
    if (var.empty()){
        std::cout << "No\n";
    }
    else{
        std::cout << "Yes\n";
        for (int i = 0; i < (int)var.size(); i++){
            std::cout << var[i] << (i + 1 == (int)var.size() ? "\n" : " ");
        }
        for (int i = 0; i < (int)edge.size(); i++){
            std::cout << edge[i] << (i + 1 == (int)edge.size() ? "\n" : " ");
        }
        if (edge.empty()) std::cout << "\n";
    }
}