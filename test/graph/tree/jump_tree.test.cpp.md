---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: ds/Sparce_table.hpp
    title: ds/Sparce_table.hpp
  - icon: ':question:'
    path: graph/tree/LCA.hpp
    title: graph/tree/LCA.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"graph/tree/LCA.hpp\"\n#include<vector>\n#include<algorithm>\n\
    #include<cassert>\n#line 4 \"ds/Sparce_table.hpp\"\nnamespace po167{\ntemplate<class\
    \ T, T(*op)(T, T)>\nstruct Sparce_table{\n    int n;\n    int depth;\n    std::vector<std::vector<T>>\
    \ val;\n    void init(std::vector<T> &v){\n        depth = 1;\n        n = v.size();\n\
    \        while ((1 << depth) <= n) depth++;\n        val.resize(depth);\n    \
    \    val[0] = v;\n        for (int i = 1; i < depth; i++){\n            val[i].resize(n);\n\
    \            for (int j = 0; j <= n - (1 << i); j++){\n                val[i][j]\
    \ = op(val[i - 1][j], val[i - 1][j + (1 << (i - 1))]);\n            }\n      \
    \  }\n    }\n    Sparce_table(std::vector<T> v){\n        init(v);\n    }\n  \
    \  Sparce_table(){}\n    // 0 <= l < r <= n\n    // if l == r : assert\n    T\
    \ prod(int l, int r){\n        assert(0 <= l && l < r && r <= n);\n        int\
    \ z=31-__builtin_clz(r-l);\n        return op(val[z][l], val[z][r - (1 << z)]);\n\
    \    }\n};\n}\n#line 6 \"graph/tree/LCA.hpp\"\nnamespace po167{\nint op(int a,\
    \ int b){\n    return std::min(a, b);\n}\nstruct LCA{\n    Sparce_table<int, op>\
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
    \ pare){\n        init(pare);\n    }\n    int lca(int a, int b){\n        assert(0\
    \ <= std::min(a, b) && std::max(a, b) < var_num);\n        if (a == b) return\
    \ a;\n        if (E[a] > E[b]) std::swap(a, b);\n        return order[table.prod(E[a],\
    \ E[b])];\n    }\n    int dist(int a, int b){\n        assert(0 <= std::min(a,\
    \ b) && std::max(a, b) < var_num);\n        return depth[a] + depth[b] - 2 * depth[lca(a,\
    \ b)];\n    }\n    int back(int var, int len){\n        assert(len <= depth[var]);\n\
    \        if (len == 0) return var;\n        int l = 0, r = E[var];\n        while\
    \ (r - l > 1){\n            int m = (l + r) / 2;\n            if (depth[var] -\
    \ depth[order[table.prod(m, E[var])]] < len){\n                r = m;\n      \
    \      }\n            else l = m;\n        }\n        return order[table.prod(l,\
    \ E[var])];\n    }\n    // a -> b\n    int jump(int a, int b, int len){\n    \
    \    int c = lca(a, b);\n        if (len <= depth[a] - depth[c]) return back(a,\
    \ len);\n        len -= depth[a] - depth[c];\n        if (len <= depth[b] - depth[c])\
    \ return back(b, depth[b] - depth[c] - len);\n        return -1;\n    }\n};\n\n\
    }\n#line 2 \"test/graph/tree/jump_tree.test.cpp\"\n#include <iostream>\n\nint\
    \ main(){\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<std::vector<int>> g(N);\n\
    \    for (int i = 0; i < N - 1; i++){\n        int a, b;\n        std::cin >>\
    \ a >> b;\n        g[a].push_back(b);\n        g[b].push_back(a);\n    }\n   \
    \ po167::LCA L(g);\n    while (Q--){\n        int s, t, k;\n        std::cin >>\
    \ s >> t >> k;\n        std::cout << L.jump(s, t, k) << \"\\n\";\n    }\n}\n"
  code: "#include \"../../../graph/tree/LCA.hpp\"\n#include <iostream>\n\nint main(){\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int N,\
    \ Q;\n    std::cin >> N >> Q;\n    std::vector<std::vector<int>> g(N);\n    for\
    \ (int i = 0; i < N - 1; i++){\n        int a, b;\n        std::cin >> a >> b;\n\
    \        g[a].push_back(b);\n        g[b].push_back(a);\n    }\n    po167::LCA\
    \ L(g);\n    while (Q--){\n        int s, t, k;\n        std::cin >> s >> t >>\
    \ k;\n        std::cout << L.jump(s, t, k) << \"\\n\";\n    }\n}"
  dependsOn:
  - graph/tree/LCA.hpp
  - ds/Sparce_table.hpp
  isVerificationFile: true
  path: test/graph/tree/jump_tree.test.cpp
  requiredBy: []
  timestamp: '2024-11-20 00:33:35+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/graph/tree/jump_tree.test.cpp
layout: document
redirect_from:
- /verify/test/graph/tree/jump_tree.test.cpp
- /verify/test/graph/tree/jump_tree.test.cpp.html
title: test/graph/tree/jump_tree.test.cpp
---
