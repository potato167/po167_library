#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"


#include "../../fps/FPS_online_convolution.hpp"


#include <iostream>
using mint = atcoder::modint998244353;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    int X = N + M - 1;
    std::vector<int> A(X), B(X);
    for (int i = 0; i < N; i++) std::cin >> A[i];
    for (int i = 0; i < M; i++) std::cin >> B[i];
    po167::FPS_online_convolution<mint> oc;
    for (int i = 0; i < X; i++){
        if (i) std::cout << " ";
        std::cout << oc.query(A[i], B[i]).val();
    }
    std::cout << "\n";
}