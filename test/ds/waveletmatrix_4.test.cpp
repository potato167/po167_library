#define PROBLEM "https://yukicoder.me/problems/no/878"

#include "../../ds/WaveletMatrix.hpp"
#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &a : A) std::cin >> a;

    // P[i]: 直前の A[i] より大きい要素の位置（1-indexed、なければ 0）。
    std::vector<int> P(N), st;
    st.reserve(N);
    for (int i = 0; i < N; i++){
        while (!st.empty() && A[st.back()] <= A[i]){
            st.pop_back();
        }
        P[i] = st.empty() ? 0 : st.back() + 1;
        st.push_back(i);
    }

    po167::WaveletMatrix<int> wm(P);
    while (Q--){
        int t, l, r;
        std::cin >> t >> l >> r;
        std::cout << wm.range_freq(l - 1, r, l) << "\n";
    }
}