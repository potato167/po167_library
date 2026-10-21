#define PROBLEM "https://yukicoder.me/problems/no/952"

#include "../../algorithm/monge_d_edge_shortest_path.hpp"
#include "../../algorithm/monge_k_edge_shortest_path.hpp"
#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<long long> S(N + 1);
    for (int i = 0; i < N; i++){
        std::cin >> S[i + 1];
        S[i + 1] += S[i];
    }

    auto cost = [&](int i, int j){
        long long s = S[j - 1] - S[i];
        return s * s;
    };
    auto ans = po167::monge_k_edge_shortest_path<long long>(N + 1, N, cost);

    // Selected edge counts are computed by the fixed-D function.
    std::vector<bool> check(N + 1);
    for (int t = 0; t < 32; t++) check[1 + (N - 1) * t / 31] = true;
    if (N >= 2) check[2] = check[N - 1] = true;
    for (int d = 1; d <= N; d++){
        if (check[d]) ans[d] = po167::monge_d_edge_shortest_path(N + 1, d, cost);
    }
    for (int k = 1; k <= N; k++){
        std::cout << ans[N + 1 - k] << "\n";
    }
}
