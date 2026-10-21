#define PROBLEM "https://yukicoder.me/problems/no/705"

#include "../../algorithm/monge_shortest_path.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<long long> A(N), X(N), Y(N);
    for (auto &a : A) std::cin >> a;
    for (auto &x : X) std::cin >> x;
    for (auto &y : Y) std::cin >> y;

    auto cost = [&](int i, int j){
        long long dx = std::abs(A[j - 1] - X[i]);
        return dx * dx * dx + Y[i] * Y[i] * Y[i];
    };

    auto dp = po167::monge_shortest_path(N, cost);
    std::cout << dp.first[N] << "\n";
}
