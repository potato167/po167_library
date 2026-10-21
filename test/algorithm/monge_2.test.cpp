#define PROBLEM "https://yukicoder.me/problems/no/952"

#include "../../algorithm/monge_k_edge_shortest_path.hpp"
#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<long long> S(N + 1);
    for (int i = 0; i < N; ++i){
        std::cin >> S[i + 1];
        S[i + 1] += S[i];
    }

    auto cost = [&](int i, int j){
        long long sum = S[j - 1] - S[i];
        return sum * sum;
    };

    auto ans = po167::monge_k_edge_shortest_path<long long>(N + 1, N, cost);
    for (int k = 1; k <= N; ++k){
        std::cout << ans[N - k + 1] << "\n";
    }
}
