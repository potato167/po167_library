#define PROBLEM "https://judge.yosupo.jp/problem/consecutive_terms_of_linear_recurrent_sequence"


#include "../../fps/FPS_consecutive_linear.hpp"
#include<iostream>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = atcoder::modint998244353;

    long long d, k, M, num;
    std::cin >> d >> k >> M;
    std::vector<mint> A(d), C(d + 1);
    for (int i = 0; i < d; i++) std::cin >> num, A[i] = num;
    for (int i = 1; i <= d; i++) std::cin >> num, C[i] = num;
    C[0] = -1;
    auto ans = po167::Consecutive_Linear(k, k + M, A, C);
    for (int i = 0; i < (int)ans.size(); i++){
        if (i) std::cout << " ";
        std::cout << ans[i].val();
    }
    std::cout << "\n";
}