
// S=sum(p)
// O(S*sqrt(S)/w)
// s.t
// S<_max_len(=1e6+1)
// 0<=p[i]

//アンダーバーを先頭にするのはやばいらしい

//https://codeforces.com/contest/1856/problem/E2
//https://codeforces.com/contest/1856/submission/219130190
#include<vector>
const int _max_len=4e6+1;
template<int _len=1>
std::vector<bool> fast_subset_sub_solver(std::vector<int> &p,int sum=-1){
    if(sum==-1){
        sum=0;
        for(auto x:p){
            assert(x>=0);
            sum+=x;
        }
    }
    assert(sum<=_max_len);
    if(sum>=_len){
        return fast_subset_sub_solver<std::min(_max_len,2*_len)>(p,sum);
    }
    for(auto x:p) assert(x>=0);
    std::bitset<_len> dp;
    std::vector<int> q(sum+1);
    for(auto x:p) q[x]++;
    dp[0]=1;
    for(int i=1;i<=sum;i++){
        if(q[i]>=1){
            if(0==(q[i]&1)) q[i]--,dp=(dp|(dp<<i));
            q[i]--,dp=(dp|(dp<<i));
            if(i*2<=sum&&2<=q[i]) q[i*2]+=q[i]/2;
        }
    }
    std::vector<bool> res(sum+1);
    for(int i=0;i<=sum;i++) res[i]=dp[i];
    return res;
}