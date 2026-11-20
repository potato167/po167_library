#define PROBLEM "https://yukicoder.me/problems/no/2072"

#include "graph/DynamicConnectivity.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    po167::DynamicConnectivity<long long> graph(n);
    std::vector<std::pair<int, int>> edges(m);
    for (auto& [u, v] : edges) {
        std::cin >> u >> v;
        --u;
        --v;
        graph.link(u, v);
    }

    // Deletions in distinct components commute. In edge order, each new
    // deletion is one round after the last deletion in its component.
    long long answer = 0;
    for (auto [u, v] : edges) {
        // Store round * n + vertex at a single vertex of each component.
        long long marker = graph.get_sum(u);
        long long round = marker / n + 1;
        if (marker) graph.update(static_cast<int>(marker % n), -marker);
        bool split = graph.cut(u, v);
        graph.update(u, round * n + u);
        if (split) graph.update(v, round * n + v);
        answer = std::max(answer, round);
    }
    std::cout << answer << '\n';
}
