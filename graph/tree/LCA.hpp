#pragma once
#include<vector>
#include<algorithm>
#include<cassert>
#include "../../ds/Sparce_table.hpp"
namespace po167{
int op(int a, int b){
    return std::min(a, b);
}
struct LCA{
    Sparce_table<int, op> table;
    std::vector<int> depth;
    std::vector<int> E;
    std::vector<int> order;
    int var_num;
    void init(std::vector<std::vector<int>> &g, int root = 0){
        var_num = g.size();
        assert(0 <= root && root < var_num);
        std::vector<int> val;
        depth.assign(var_num, -1);
        depth[root] = 0;
        E.resize(var_num);
        std::vector<int> tmp;
        order.clear();
        tmp.reserve(var_num);
        order.reserve(var_num);
        int c = 0;
        auto dfs = [&](auto self, int var, int pare) -> void {
            E[var] = c++;
            if (var != root) tmp.push_back(E[pare]);
            order.push_back(var);
            for (auto x : g[var]) if (depth[x] == -1){
                depth[x] = depth[var] + 1;
                self(self, x, var);
            }
        };
        dfs(dfs, root, -1);
        assert(c == var_num);
        table.init(tmp);
    }
    void init(std::vector<int> &pare){
        int root = -1;
        int n = pare.size();
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; i++){
            if (pare[i] < 0){
                assert(root == -1);
                root = i;
            }
            else{
                assert(0 <= pare[i] && pare[i] < n);
                g[pare[i]].push_back(i);
            }
        }
        assert(root != -1);
        init(g, root);
    }
    LCA (std::vector<std::vector<int>> g, int root = 0){
        init(g, root);
    }
    LCA (std::vector<int> pare){
        init(pare);
    }
    int lca(int a, int b){
        assert(0 <= std::min(a, b) && std::max(a, b) < var_num);
        if (a == b) return a;
        if (E[a] > E[b]) std::swap(a, b);
        return order[table.prod(E[a], E[b])];
    }
    int dist(int a, int b){
        assert(0 <= std::min(a, b) && std::max(a, b) < var_num);
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
    int back(int var, int len){
        assert(len <= depth[var]);
        if (len == 0) return var;
        int l = 0, r = E[var];
        while (r - l > 1){
            int m = (l + r) / 2;
            if (depth[var] - depth[order[table.prod(m, E[var])]] < len){
                r = m;
            }
            else l = m;
        }
        return order[table.prod(l, E[var])];
    }
    // a -> b
    int jump(int a, int b, int len){
        int c = lca(a, b);
        if (len <= depth[a] - depth[c]) return back(a, len);
        len -= depth[a] - depth[c];
        if (len <= depth[b] - depth[c]) return back(b, depth[b] - depth[c] - len);
        return -1;
    }
};

}