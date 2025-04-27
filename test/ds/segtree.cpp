#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../ds/Segtree.hpp"
#include <iostream>
using ll = long long;
ll op(ll a, ll b){
    return a + b;
}
ll e(){
    return 0ll;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;
    std::vector<ll> A(N);
    for (auto &a : A) std::cin >> a;
    po167::segtree<ll, op, e> seg(A);
    while (Q--){
        int t, a, b;
        std::cin >> t >> a >> b;
        if (t == 0){
            seg.updl(a, b);
        }
        else{
            std::cout << seg.prod(a, b) << "\n";
        }
    }
}