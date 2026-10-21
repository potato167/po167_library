#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large"

#include "../../math/multiplicative_prefix_sum.hpp"
#include <atcoder/modint>
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using mint = atcoder::static_modint<469762049>;
    const mint inv2 = mint(1) / 2;

    int T;
    std::cin >> T;
    while (T--){
        long long N;
        int a, b;
        std::cin >> N >> a >> b;

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
            P1[i] = P0[i] * a + P1[i] * b;
        }

        auto F = sieve.sum(P1, [a, b](long long p, int e, long long){
            return mint(a) * e + mint(b) * p;
        });
        std::cout << sieve.get(F, N).val() << "\n";
    }
}