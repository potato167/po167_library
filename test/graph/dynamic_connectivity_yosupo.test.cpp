#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"

#include "graph/DynamicConnectivity.hpp"

#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    po167::DynamicConnectivity<long long> graph(n);
    for (int v = 0; v < n; ++v) {
        long long value;
        std::cin >> value;
        graph.update(v, value);
    }
    while (q--) {
        int type, u;
        std::cin >> type >> u;
        if (type <= 1) {
            int v;
            std::cin >> v;
            if (type == 0) graph.link(u, v);
            else graph.cut(u, v);
        } else if (type == 2) {
            long long value;
            std::cin >> value;
            graph.update(u, value);
        } else {
            std::cout << graph.get_sum(u) << '\n';
        }
    }
}
