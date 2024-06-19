#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "../../fps/FPS_Boston_Mori.hpp"

#include <vector>
#include <iostream>

int main(){
    using mint = atcoder::modint998244353;
    int d;
    long long k;
    std::cin >> d >> k;
    std::vector<mint> a(d), c(d + 1, -1);
    int mem;
    for (int i = 0; i < d; i++) std::cin >> mem, a[i] = mem;
    for (int i = 1; i <= d; i++) std::cin >> mem, c[i] = mem;
    std::cout << po167::Kth_Linear(k, a, c).val() << "\n";
}