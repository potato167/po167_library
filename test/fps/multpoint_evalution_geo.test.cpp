#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"
#include "../../fps/Multipoint_Evaluation_Geo.hpp"

#include <iostream>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = atcoder::modint998244353;

    int N, M, a, r;
    std::cin >> N >> M >> a >> r;
    std::vector<mint> c(N);
    int b;
    for (auto &x : c){
        std::cin >> b;
        x = b;
    }
    auto ans = po167::Multipoint_Evaluation_Geo(c, (mint)(a), (mint)(r), M);
    for (int i = 0; i < (int)ans.size(); i++){
        std::cout << ans[i].val() << (i + 1 == (int)ans.size() ? "\n" : " ");
    }
}