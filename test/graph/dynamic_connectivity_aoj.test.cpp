#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2235"

#include "graph/DynamicConnectivity.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    po167::DynamicConnectivity<> graph(n);
    while (q--) {
        int type, u, v;
        std::cin >> type >> u >> v;
        if (type == 1) graph.link(u, v);
        else if (type == 2) graph.cut(u, v);
        else std::cout << (graph.same(u, v) ? "YES\n" : "NO\n");
    }
}
