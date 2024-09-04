#define PROBLEM "https://judge.yosupo.jp/problem/q_binomial_coefficient_prime_mod"

#include "../../math/q_Binomial.hpp"

#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T, m, q;
    std::cin >> T >> m >> q;
    mint::set_mod(m);
    po167::q_Binomial<mint> table(q, m);
    while (T--){
        int n, k;
        std::cin >> n >> k;
        std::cout << table.C(n, k).val() << "\n";
    }
}