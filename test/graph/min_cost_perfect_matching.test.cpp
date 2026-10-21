#define PROBLEM "https://judge.yosupo.jp/problem/assignment"

#include "graph/MinCostPerfectMatching.hpp"

#include<iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector a(n, std::vector<long long>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cin >> a[i][j];
        }
    }
    auto ans = po167::min_cost_perfect_matching(a);
    std::cout << ans.first << "\n";
    for (int i = 0; i < n; i++){
        std::cout << ans.second[i] << (i + 1 == n ? "\n" : " ");
    }
}