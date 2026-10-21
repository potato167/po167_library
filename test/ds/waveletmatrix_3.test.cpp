#define PROBLEM "https://yukicoder.me/problems/no/1332"

#include "../../ds/WaveletMatrix.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (auto &a : A) std::cin >> a;

    po167::WaveletMatrix<int> wm(A);

    int Q;
    std::cin >> Q;
    while (Q--){
        int l, r, x;
        std::cin >> l >> r >> x;
        --l;

        int p = wm.prev_value(l, r, x);
        int s = wm.next_value(l, r, x);
        int ans = std::numeric_limits<int>::max();
        if (p != -1) ans = std::min(ans, x - p);
        if (s != -1) ans = std::min(ans, s - x);

        std::cout << ans << "\n";
    }
}