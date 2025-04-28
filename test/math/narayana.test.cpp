#define PROBLEM "https://yukicoder.me/problems/no/2472"
#include "../../math/Binomial.hpp"
#include <iostream>
#include <atcoder/modint>
using mint = atcoder::modint998244353;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, K;
    std::cin >> N >> K;
    if (K == 0){
        std::cout << "1\n";
        return 0; 
    }
    po167::Binomial<mint> table;
    mint ans = 0;
    for (int i = 1; i <= K; i++){
        ans += table.narayana(K, i) * table.C(K * 2 + N - i * 2 + 1, K * 2);
    }
    std::cout << ans.val() << "\n";
}