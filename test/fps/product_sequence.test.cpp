#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"

#include "../../fps/FPS_Product_Sequence.hpp"

#include <vector>
#include <iostream>


int main(){
    int N;
    std::cin >> N;
    std::vector<std::vector<atcoder::modint998244353>> f(N);
    for (int i = 0; i < N; i++){
        int d;
        std::cin >> d;
        f[i].resize(d + 1);
        for (int j = 0; j <= d; j++){
            int a;
            std::cin >> a;
            f[i][j] = a;
        }
    }
    auto ans = po167::FPS_Product_Sequence(f);
    for (int i = 0; i < (int)ans.size(); i++){
        if (i) std::cout << " ";
        std::cout << ans[i].val();
    }
    std::cout << "\n";
}