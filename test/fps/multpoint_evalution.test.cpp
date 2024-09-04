#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "../../fps/Multipoint_Evaluation.hpp"

#include <iostream>
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = atcoder::modint998244353;

    int N, M;
    std::cin >> N >> M;
    std::vector<mint> c(N), p(M);
    int a;
    for (auto &x : c){
        std::cin >> a;
        x = a;
    }
    for (auto &x : p){
        std::cin >> a;
        x = a;
    }
    auto ans = po167::Multipoint_Evaluation(c, p);
    for (int i = 0; i < (int)ans.size(); i++){
        std::cout << ans[i].val() << (i + 1 == (int)ans.size() ? "\n" : " ");
    }
}