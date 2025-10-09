#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"


#include "../../fps/FPS_composition.hpp"
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
    std::vector<mint> b(n);
    for (int i = 0; i < n; i++){
        int mem;
        std::cin >> mem;
        b[i] = mem;
    }
    auto c = po167::FPS_comp(a, b);
    for (int i = 0; i < n; i++){
        std::cout << c[i].val() << (i + 1 == n ? "\n" : " ");
    }
}