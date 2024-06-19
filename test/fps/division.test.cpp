#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../fps/FPS_division.hpp"

#include <vector>
#include <iostream>
#include <atcoder/modint>

int main(){
    int N, M, a;
    std::cin >> N >> M;
    std::vector<atcoder::modint998244353> f(N), g(M);
    for (int i = 0; i < N; i++){
        std::cin >> a;
        f[i] = a;
    }
    for (int i = 0; i < M; i++){
        std::cin >> a;
        g[i] = a;
    }
    auto ans = po167::FPS_division(f, g);
    std::cout << ans.first.size() << " " << ans.second.size() << "\n";
    for (int i = 0; i < (int)ans.first.size(); i++){
        if (i) std::cout << " ";
        std::cout << ans.first[i].val();
    }
    std::cout << "\n";
    for (int i = 0; i < (int)ans.second.size(); i++){
        if (i) std::cout << " ";
        std::cout << ans.second[i].val();
    }
    std::cout << "\n";
}