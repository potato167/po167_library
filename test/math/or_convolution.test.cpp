#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "../../math/Bitwise_Convolution.hpp"
#include <iostream>
#include <atcoder/modint>
#include <algorithm>
using mint = atcoder::modint998244353;

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    std::vector<mint> A(1 << N), B(1 << N);
    int v;
    for (auto &a : A) std::cin >> v, a = v;
    for (auto &b : B) std::cin >> v, b = v;
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());
    auto ans = po167::or_convolution(A, B);
    std::reverse(ans.begin(), ans.end());
    for (auto &c : ans) std::cout << c.val() << " ";
}