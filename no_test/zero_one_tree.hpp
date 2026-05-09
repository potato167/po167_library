#pragma once
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <utility>
namespace po167{
//minmize \sum_{i=0,1,...,n-1}(u[q[i]]*\sum_{j=0,1,...,i}(d[q[j]]))
//st q is permutation
//order[p[i]]<order[i]
//p[root]=-1
//https://atcoder.jp/contests/agc023/submissions/40321108
std::pair<long long, std::vector<int>> scheduling_cost(std::vector<int> p, std::vector<int> u, std::vector<int> d) {
    int n=p.size();
    struct _job{
        long long cost;
        long long time;
        int ind;
        int hash = 0;
    };
    std::vector<int> par(n);
    std::vector<_job> val(n);
    long long ans=0;
    for (int i = 0; i< n; i++){
        par[i] = i;
        val[i].cost = (long long)u[i];
        val[i].time = (long long)d[i];
        val[i].ind = i;
        ans += val[i].cost * val[i].time;
    }
    auto concat_job = [&](_job &l, _job r) -> void {
        ans += l.time * r.cost;
        l.time += r.time;
        l.cost += r.cost;
    };
    auto comp_job = [&](_job l, _job r) -> bool {
        if (r.time == 0 && r.cost == 0) return false;
        if (l.time == 0 && l.cost == 0) return true;
        return l.cost * r.time < l.time * r.cost;
    };
    auto root = [&](auto self, int a)-> int {
        if (a == par[a]) return a;
        par[a] = self(self, par[a]);
        return par[a];
    };
    std::priority_queue<_job,std::vector<_job>, std::function<bool(_job, _job)>> pq(comp_job);
    int t = -1;
    for (int i = 0; i < n; i++){
        if (p[i] == -1) t = i;
    }
    std::vector<int> seen(n), hash(n);
    for (int i = 0; i < n; i++){
        if (i != t){
            pq.push(val[i]);
        }
    }
    int count = 0;
    while (!pq.empty()){
        _job tmp = pq.top();
        pq.pop();
        if (tmp.hash != hash[tmp.ind]) continue;
        seen[tmp.ind] = n - count;
        count++;
        par[tmp.ind] = p[tmp.ind];
        int r = root(root, tmp.ind);
        concat_job(val[r], tmp);
        if (r != t){
            val[r].hash = count;
            hash[r] = count;
            pq.push(val[r]);
        }
    }
    std::vector<int> order;
    order.reserve(n);
    std::vector<std::vector<int>> G(n);
    std::priority_queue<std::pair<int, int>> valid;
    for (int i = 0; i < n; i++){
        if (0 <= p[i]) G[p[i]].push_back(i);
        else valid.push({seen[i], i});
    }
    while (!valid.empty()){
        int a = valid.top().second;
        order.push_back(a);
        valid.pop();
        for (auto x : G[a]) valid.push({seen[x], x});
    }
    return {ans, order};
}
}