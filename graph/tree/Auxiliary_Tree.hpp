
#pragma once
#include "LCA.hpp"
#include <vector>
#include <stack>

namespace po167{
struct Auxiliary_Tree{
    std::vector<int> pre_order_list;
    std::vector<int> pre_order_inv;
    int n;
    po167::LCA L;
    std::vector<int> out_order;
    Auxiliary_Tree(std::vector<std::vector<int>> g, int root = 0){
        std::stack<int> st;
        n = (int)g.size();
        std::vector<int> seen(n);
        seen[root] = 0;
        st.push(root);
        while (!st.empty()){
            int a = st.top();
            st.pop();
            pre_order_list.push_back(a);
            for (auto x : g[a]) if (seen[x] == 0){
                seen[x] = 1;
                st.push(x);
            }
        }
        assert((int)pre_order_list.size() == n);
        pre_order_inv.resize(n);
        for (int i = 0; i < n; i++) pre_order_inv[pre_order_list[i]] = i;
        L.init(g);
        out_order.resize(n, -1);
    }
    std::tuple<std::vector<int>, std::vector<int>> bulid(std::vector<int> v){
        std::sort(v.begin(), v.end(), [&](int l, int r){
            return pre_order_inv[l] < pre_order_inv[r];
        });
        v.erase(std::unique(v.begin(), v.end()), v.end());
        int m = v.size();
        for (int i = 0; i < m - 1; i++){
            v.push_back(L.lca(v[i], v[i + 1]));
        }
        std::sort(v.begin(), v.end(), [&](int l, int r){
            return pre_order_inv[l] < pre_order_inv[r];
        });
        v.erase(std::unique(v.begin(), v.end()), v.end());
        m = v.size();
        for (int i = 0; i < m; i++){
            out_order[v[i]] = i;
        }
        std::stack<int> st;
        st.push(v[0]);
        std::vector<int> pare(m, -1);
        for (int i = 1; i < m; i++){
            while (st.top() != L.lca(st.top(), v[i])) st.pop();
            pare[i] = out_order[st.top()];
            st.push(v[i]);
        }
        return {v, pare};
    }
};
}