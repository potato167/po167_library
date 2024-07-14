#define PROBLEM "https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large"


#include "../../fps/FPS_inverse.hpp"

#include <atcoder/modint>
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = atcoder::modint998244353;
    int n;
    std::cin >> n;
    std::vector<mint> a(n);
    for (int i = 0; i < n; i++){
        int mem;
        std::cin >> mem;
        a[i] = mem;
    }
    auto b = po167::FPS_inverse(a);
    for (int i = 0; i < n; i++){
        std::cout << b[i].val() << (i + 1 == n ? "\n" : " ");
    }
}