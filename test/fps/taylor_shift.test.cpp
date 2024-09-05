#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../fps/Taylor_Shift.hpp"

#include <iostream>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = atcoder::modint998244353;

    int N, c, a;
    std::cin >> N >> c;
    std::vector<mint> f(N);
    for (auto &x : f){
        std::cin >> a;
        x = a;
    }
    f = po167::Taylor_Shift(f, (mint)(c));
    for (int i = 0; i < N; i++){
        std::cout << f[i].val() << (i + 1 == N ? "\n" : " ");
    }
}