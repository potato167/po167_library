#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../math/Binomial.hpp"
#include <bits/stdc++.h>
#include <atcoder/modint>

int main(){
    int T, m;
    std::cin >> T >> m;
    using mint = atcoder::dynamic_modint<1>;
    mint::set_mod(m);
    po167::Binomial<mint> table(std::min(m, 10000000) - 1);
    while (T--){
        int n, k;
        std::cin >> n >> k;
        std::cout << table.C(n, k).val() << "\n";
    }
}