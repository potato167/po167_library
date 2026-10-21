#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../math/multiplicative_prefix_sum.hpp"
#include <atcoder/modint>
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N;
    std::cin >> N;

    using mint = atcoder::modint998244353;
    const mint inv2 = mint(1) / 2;
    po167::multiplicative_prefix_sum<mint> sieve(N);

    auto P0 = sieve.prime_sum(
        [](long long){ return mint(1); },
        [](long long x){ return mint(x); }
    );
    auto P1 = sieve.prime_sum(
        [](long long p){ return mint(p); },
        [inv2](long long x){
            return mint(x) * (mint(x) + 1) * inv2;
        }
    );
    for (std::size_t i = 0; i < P1.size(); i++){
        P1[i] -= P0[i];
    }

    auto F = sieve.sum(P1, [](long long p, int, long long pe){
        return mint(pe) - mint(pe / p);
    });
    std::cout << sieve.get(F, N).val() << "\n";
}