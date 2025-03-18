#define PROBLEM "https://yukicoder.me/problems/no/1145"
#include "../../fps/FPS_sum_of_power.hpp"
#include <iostream>

int main(){
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M;
    std::cin >> N >> M;
    std::vector<atcoder::modint998244353> A(N);
    for (int i = 0; i < N; i++){
        int a;
        std::cin >> a;
        A[i] = a;
    }
    auto ans = po167::FPS_sum_of_power(A, M);
    for (int i = 1; i <= M; i++){
        std::cout << ans[i].val() << (i == M ? "\n" : " ");
    }
}