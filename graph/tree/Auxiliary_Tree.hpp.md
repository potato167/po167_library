---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/Sparse_table.hpp
    title: ds/Sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: graph/tree/LCA.hpp
    title: graph/tree/LCA.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/tree/LCA.hpp\"\n#include<vector>\n#include<algorithm>\n\
    #include<cassert>\n#line 4 \"ds/Sparse_table.hpp\"\nnamespace po167{\ntemplate<class\
    \ T, T(*op)(T, T)>\nstruct Sparse_table{\n    int n;\n    int depth;\n    std::vector<std::vector<T>>\
    \ val;\n    void init(std::vector<T> &v){\n        depth = 1;\n        n = v.size();\n\
    \        while ((1 << depth) <= n) depth++;\n        val.resize(depth);\n    \
    \    val[0] = v;\n        for (int i = 1; i < depth; i++){\n            val[i].resize(n);\n\
    \            for (int j = 0; j <= n - (1 << i); j++){\n                val[i][j]\
    \ = op(val[i - 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n      \
    \  }\n    }\n    Sparse_table(std::vector<T> v){\n        init(v);\n    }\n  \
    \  Sparse_table(){}\n    // 0 <= l < r <= n\n    // if l == r : assert\n    T\
    \ prod(int l, int r){\n        assert(0 <= l && l < r && r <= n);\n        int\
    \ z=31-__builtin_clz(r-l);\n        return op(val[z][l], val[z][r - (1 << z)]);\n\
    \    }\n};\n}\n#line 6 \"graph/tree/LCA.hpp\"\nnamespace po167{\nint op(int a,\
    \ int b){\n    return std::min(a, b);\n}\nstruct LCA{\n    Sparse_table<int, op>\
    \ table;\n    std::vector<int> depth;\n    std::vector<int> E;\n    std::vector<int>\
    \ order;\n    int var_num;\n    void init(std::vector<std::vector<int>> &g, int\
    \ root = 0){\n        var_num = g.size();\n        assert(0 <= root && root <\
    \ var_num);\n        std::vector<int> val;\n        depth.assign(var_num, -1);\n\
    \        depth[root] = 0;\n        E.resize(var_num);\n        std::vector<int>\
    \ tmp;\n        order.clear();\n        tmp.reserve(var_num);\n        order.reserve(var_num);\n\
    \        int c = 0;\n        auto dfs = [&](auto self, int var, int pare) -> void\
    \ {\n            E[var] = c++;\n            if (var != root) tmp.push_back(E[pare]);\n\
    \            order.push_back(var);\n            for (auto x : g[var]) if (depth[x]\
    \ == -1){\n                depth[x] = depth[var] + 1;\n                self(self,\
    \ x, var);\n            }\n        };\n        dfs(dfs, root, -1);\n        assert(c\
    \ == var_num);\n        table.init(tmp);\n    }\n    void init(std::vector<int>\
    \ &pare){\n        int root = -1;\n        int n = pare.size();\n        std::vector<std::vector<int>>\
    \ g(n);\n        for (int i = 0; i < n; i++){\n            if (pare[i] < 0){\n\
    \                assert(root == -1);\n                root = i;\n            }\n\
    \            else{\n                assert(0 <= pare[i] && pare[i] < n);\n   \
    \             g[pare[i]].push_back(i);\n            }\n        }\n        assert(root\
    \ != -1);\n        init(g, root);\n    }\n    LCA (std::vector<std::vector<int>>\
    \ g, int root = 0){\n        init(g, root);\n    }\n    LCA (std::vector<int>\
    \ pare){\n        init(pare);\n    }\n    LCA(){\n        \n    }\n    int lca(int\
    \ a, int b){\n        assert(0 <= std::min(a, b) && std::max(a, b) < var_num);\n\
    \        if (a == b) return a;\n        if (E[a] > E[b]) std::swap(a, b);\n  \
    \      return order[table.prod(E[a], E[b])];\n    }\n    int dist(int a, int b){\n\
    \        assert(0 <= std::min(a, b) && std::max(a, b) < var_num);\n        return\
    \ depth[a] + depth[b] - 2 * depth[lca(a, b)];\n    }\n    int back(int var, int\
    \ len){\n        assert(len <= depth[var]);\n        if (len == 0) return var;\n\
    \        int l = 0, r = E[var];\n        while (r - l > 1){\n            int m\
    \ = (l + r) / 2;\n            if (depth[var] - depth[order[table.prod(m, E[var])]]\
    \ < len){\n                r = m;\n            }\n            else l = m;\n  \
    \      }\n        return order[table.prod(l, E[var])];\n    }\n    // a -> b\n\
    \    int jump(int a, int b, int len){\n        int c = lca(a, b);\n        if\
    \ (len <= depth[a] - depth[c]) return back(a, len);\n        len -= depth[a] -\
    \ depth[c];\n        if (len <= depth[b] - depth[c]) return back(b, depth[b] -\
    \ depth[c] - len);\n        return -1;\n    }\n};\n\n}\n#line 4 \"graph/tree/Auxiliary_Tree.hpp\"\
    \n#include <stack>\n#include <tuple>\n\nnamespace po167{\nstruct Auxiliary_Tree{\n\
    \    std::vector<int> pre_order_list;\n    std::vector<int> pre_order_inv;\n \
    \   int n;\n    po167::LCA L;\n    std::vector<int> out_order;\n    Auxiliary_Tree(std::vector<std::vector<int>>\
    \ g, int root = 0){\n        std::stack<int> st;\n        n = (int)g.size();\n\
    \        std::vector<int> seen(n);\n        seen[root] = 1;\n        st.push(root);\n\
    \        while (!st.empty()){\n            int a = st.top();\n            st.pop();\n\
    \            pre_order_list.push_back(a);\n            for (auto x : g[a]) if\
    \ (seen[x] == 0){\n                seen[x] = 1;\n                st.push(x);\n\
    \            }\n        }\n        assert((int)pre_order_list.size() == n);\n\
    \        pre_order_inv.resize(n);\n        for (int i = 0; i < n; i++) pre_order_inv[pre_order_list[i]]\
    \ = i;\n        L.init(g);\n        out_order.resize(n, -1);\n    }\n    std::tuple<std::vector<int>,\
    \ std::vector<int>> bulid(std::vector<int> v){\n        std::sort(v.begin(), v.end(),\
    \ [&](int l, int r){\n            return pre_order_inv[l] < pre_order_inv[r];\n\
    \        });\n        v.erase(std::unique(v.begin(), v.end()), v.end());\n   \
    \     int m = v.size();\n        for (int i = 0; i < m - 1; i++){\n          \
    \  v.push_back(L.lca(v[i], v[i + 1]));\n        }\n        std::sort(v.begin(),\
    \ v.end(), [&](int l, int r){\n            return pre_order_inv[l] < pre_order_inv[r];\n\
    \        });\n        v.erase(std::unique(v.begin(), v.end()), v.end());\n   \
    \     m = v.size();\n        for (int i = 0; i < m; i++){\n            out_order[v[i]]\
    \ = i;\n        }\n        std::stack<int> st;\n        st.push(v[0]);\n     \
    \   std::vector<int> pare(m, -1);\n        for (int i = 1; i < m; i++){\n    \
    \        while (st.top() != L.lca(st.top(), v[i])) st.pop();\n            pare[i]\
    \ = out_order[st.top()];\n            st.push(v[i]);\n        }\n        return\
    \ {v, pare};\n    }\n};\n}\n"
  code: "#pragma once\n#include \"LCA.hpp\"\n#include <vector>\n#include <stack>\n\
    #include <tuple>\n\nnamespace po167{\nstruct Auxiliary_Tree{\n    std::vector<int>\
    \ pre_order_list;\n    std::vector<int> pre_order_inv;\n    int n;\n    po167::LCA\
    \ L;\n    std::vector<int> out_order;\n    Auxiliary_Tree(std::vector<std::vector<int>>\
    \ g, int root = 0){\n        std::stack<int> st;\n        n = (int)g.size();\n\
    \        std::vector<int> seen(n);\n        seen[root] = 1;\n        st.push(root);\n\
    \        while (!st.empty()){\n            int a = st.top();\n            st.pop();\n\
    \            pre_order_list.push_back(a);\n            for (auto x : g[a]) if\
    \ (seen[x] == 0){\n                seen[x] = 1;\n                st.push(x);\n\
    \            }\n        }\n        assert((int)pre_order_list.size() == n);\n\
    \        pre_order_inv.resize(n);\n        for (int i = 0; i < n; i++) pre_order_inv[pre_order_list[i]]\
    \ = i;\n        L.init(g);\n        out_order.resize(n, -1);\n    }\n    std::tuple<std::vector<int>,\
    \ std::vector<int>> bulid(std::vector<int> v){\n        std::sort(v.begin(), v.end(),\
    \ [&](int l, int r){\n            return pre_order_inv[l] < pre_order_inv[r];\n\
    \        });\n        v.erase(std::unique(v.begin(), v.end()), v.end());\n   \
    \     int m = v.size();\n        for (int i = 0; i < m - 1; i++){\n          \
    \  v.push_back(L.lca(v[i], v[i + 1]));\n        }\n        std::sort(v.begin(),\
    \ v.end(), [&](int l, int r){\n            return pre_order_inv[l] < pre_order_inv[r];\n\
    \        });\n        v.erase(std::unique(v.begin(), v.end()), v.end());\n   \
    \     m = v.size();\n        for (int i = 0; i < m; i++){\n            out_order[v[i]]\
    \ = i;\n        }\n        std::stack<int> st;\n        st.push(v[0]);\n     \
    \   std::vector<int> pare(m, -1);\n        for (int i = 1; i < m; i++){\n    \
    \        while (st.top() != L.lca(st.top(), v[i])) st.pop();\n            pare[i]\
    \ = out_order[st.top()];\n            st.push(v[i]);\n        }\n        return\
    \ {v, pare};\n    }\n};\n}"
  dependsOn:
  - graph/tree/LCA.hpp
  - ds/Sparse_table.hpp
  isVerificationFile: false
  path: graph/tree/Auxiliary_Tree.hpp
  requiredBy: []
  timestamp: '2025-03-26 23:05:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/tree/Auxiliary_Tree.hpp
layout: document
redirect_from:
- /library/graph/tree/Auxiliary_Tree.hpp
- /library/graph/tree/Auxiliary_Tree.hpp.html
title: graph/tree/Auxiliary_Tree.hpp
---
