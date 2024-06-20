#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "../..//ds/Swag.hpp"

#include <vector>
#include <iostream>
#include <atcoder/modint>

using mint = atcoder::modint998244353;
using F = std::pair<mint, mint>;
F e(){
    return {1, 0};
}

F op(F l, F r){
    return {l.first * r.first, l.second * r.first + r.second};
}

int main(){
    int Q;
    std::cin >> Q;
    po167::SWAG<F, op, e> S(Q);
    while (Q--){
        int t;
        std::cin >> t;
        if (t == 0){
            int a, b;
            std::cin >> a >> b;
            S.push({a, b});
        }
        if (t == 1){
            S.pop();
        }
        if (t == 2){
            int x;
            std::cin >> x;
            F tmp = S.calc();
            std::cout << (tmp.first * x + tmp.second).val() << "\n";
        }
    }
}