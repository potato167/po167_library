#define PROBLEM "https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences"


#include "fps/count_increasing_sequences.hpp"
#include <iostream>
int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) std::cin >> A[i];
    for (int i = 0; i < N; i++) std::cin >> B[i];
    using mint = atcoder::modint998244353;
    auto tmp = po167::count_increase_sequences_with_upper_lower_bounds<mint>(A, B);
    mint ans = 0;
    for (auto x : tmp) ans += x;
    std::cout << ans.val() << "\n";
}