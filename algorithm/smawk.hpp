#pragma once
#include <vector>
#include <numeric>
namespace po167{
// return argmax
// 
// https://noshi91.github.io/Library/algorithm/smawk.cpp
template<class S> std::vector<int> smawk(int N, int M, S select){
    auto f = [&](auto self, std::vector<int> p,std::vector<int> q) -> std::vector<int> {
        // reduce
        std::vector<int> n_q;
        n_q.reserve(p.size());
        int k = -1;
        for(auto x:q){
            while(!n_q.empty()){
                if(!select(p[k], n_q.back(), x)) break;
                n_q.pop_back();
                k--;
            }
            if (k + 1 != (int)p.size()){
                n_q.push_back(x);
                k++;
            }
        }
        std::swap(n_q, q);

        int n = p.size();
        int m = q.size();
        
        // recursive
        if (n == 1){
            return q;
        }
        std::vector<int> n_p;
        n_p.reserve(n / 2);

        for (int i = 1; i < n; i += 2){
            n_p.push_back(p[i]);
        }
        
        auto fr = self(self, n_p, q);
        // interpolate
        std::vector<int> ans(n);
        int l = 0, r = 0;
        
        for (int i = 0; i < n; i++){
            if(i & 1){
                ans[i] = fr[i / 2];
                l = r;
            } else {
                if (i + 1 != n) {
                    while (q[r] != fr[i / 2]) r++;
                } else {
                    r = m - 1;
                }
                ans[i] = q[l];
                for (int j = l + 1; j <= r; j++){
                    if(select(p[i], ans[i], q[j])){
                        ans[i] = q[j];
                    }
                }
            }
        }
        return ans;
    };
    std::vector<int> P(N), Q(M);
    std::iota(P.begin(), P.end(), 0);
    std::iota(Q.begin(), Q.end(), 0);
    return f(f, P, Q);
}
}
