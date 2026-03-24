---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/Eulerian_trail.hpp
    title: graph/Eulerian_trail.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/eulerian_trail_undirected
    links:
    - https://judge.yosupo.jp/problem/eulerian_trail_undirected
  bundledCode: "#line 1 \"test/graph/eulerian_trail_undir.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\n\n#line 2 \"\
    graph/Eulerian_trail.hpp\"\n#include <vector>\n#include <utility>\n#include <cassert>\n\
    #include <algorithm>\n\nnamespace po167{\n/*\n * \u30B0\u30E9\u30D5\u3092\u4E0E\
    \u3048\u308B\u3002\n * \u8FBA\u306F pair<int, int> \u3067\u3001{\u884C\u304D\u5148\
    \u3001\u8FBA\u306E index}\n * \u30AA\u30A4\u30E9\u30FC\u30A6\u30A9\u30FC\u30AF\
    \u304C\u5B58\u5728\u3059\u308B\u306A\u3089\u3001\n * \u9802\u70B9\u756A\u53F7\u306E\
    \u5217\u3068\u8FBA\u756A\u53F7\u306E\u5217\u3092\u3069\u3061\u3089\u3082\u8FD4\
    \u3059\n * \u5165\u529B : vector<vector<pair<int, int>>> \u30B0\u30E9\u30D5, \u8FBA\
    \u306E\u6570, start\n * \u51FA\u529B : \u9802\u70B9\u306E\u5217\u3068\u8FBA\u306E\
    \u756A\u53F7\u306E\u5217\u306E pair\n *\n * start \u5730\u70B9\u306B\u3064\u3044\
    \u3066\n * -1 \u306B\u3057\u3066\u304A\u304F\u3068\u3001\u305D\u306E\u5F8C\u306E\
    \ dir \u3092\u307F\u3066\u81EA\u52D5\u7684\u306B\u6C42\u3081\u308B\n * dir : true\
    \  -> \u51FA\u6B21 - \u5165\u6B21\u3000\u304C\u5927\u304D\u3044\u3084\u3064\n\
    \ * dir : false -> \u5947\u6570\u9802\u70B9\u306E\u3084\u3064\n * \u306A\u304B\
    \u3063\u305F\u3089 0 \u3068\u304B\u306B\u306A\u308B\n *\n *\n */\nstd::pair<std::vector<int>,\
    \ std::vector<int>> Eulerian_trail(\n    std::vector<std::vector<std::pair<int,\
    \ int>>> g, int n_edge, int start = -1, bool dir = false\n){\n    int N = (int)g.size();\n\
    \    // \u30B9\u30BF\u30FC\u30C8\u5730\u70B9\u4E0D\u5B9A\n    if (start == -1){\n\
    \        // \u6709\u5411\u30B0\u30E9\u30D5\u306E\u3068\u304D\n        if (dir){\n\
    \            std::vector<int> sc(N);\n            for (int i = 0; i < N; i++){\n\
    \                for (auto [to, ind] : g[i]){\n                    sc[i]++;\n\
    \                    sc[to]--;\n                }\n            }\n           \
    \ start = 0;\n            for (int i = 0; i < N; i++){\n                if ((int)g[i].empty())\
    \ continue;\n                if (sc[i] >= sc[start]) start = i;\n            }\n\
    \        }\n        // \u7121\u5411\u30B0\u30E9\u30D5\u306E\u3068\u304D\n    \
    \    else{\n            for (int i = 0; i < N; i++){\n                if ((int)g[i].size()\
    \ % 2 == 1){\n                    start = i;\n                    break;\n   \
    \             }\n            }\n            if (start == -1){\n              \
    \  start = 0;\n                for (int i = 0; i < N; i++){\n                \
    \    if ((int)g[i].size() != 0){\n                        start = i;\n       \
    \                 break;\n                    }\n                }\n         \
    \   }\n        }\n    }\n    assert(0 <= start && start < N);\n    // -1 \u306F\
    \u305D\u3082\u305D\u3082\u4F7F\u308F\u308C\u3066\u3044\u306A\u3044\u3082\u306E\
    \n    std::vector<int> use_edge(n_edge, -1);\n    std::vector<int> st_var = {start},\
    \ st_edge = {-1};\n    std::vector<int> res_var, res_edge;\n    std::vector<int>\
    \ edge_index(N);\n    std::vector<int> deg(N);\n    deg[start] = 1;\n\n    //\
    \ \u5B9F\u969B\u306B\u4F55\u672C\u306E\u8FBA\u304C\u3042\u308B\u306E\u304B\u3068\
    \u3001n_edge \u306E\u5236\u7D04\u3092\u6E80\u305F\u3057\u3066\u3044\u308B\u304B\
    \u78BA\u8A8D\n    int real_edge = 0;\n    for (int i = 0; i < N; i++){\n     \
    \   for (auto [a, b] : g[i]){\n            assert(0 <= a && a < N);\n        \
    \    assert(0 <= b && b < n_edge);\n            if (use_edge[b] == -1){\n    \
    \            use_edge[b] = 0;\n                real_edge++;\n            }\n \
    \       }\n    }\n\n    while (!st_var.empty()){\n        int var = st_var.back();\n\
    \        int ind = edge_index[var];\n        if (ind == (int)g[var].size()){\n\
    \            res_var.push_back(var);\n            res_edge.push_back(st_edge.back());\n\
    \            st_var.pop_back();\n            st_edge.pop_back();\n           \
    \ continue;\n        }\n        if (use_edge[g[var][ind].second] == 0){\n    \
    \        st_var.push_back(g[var][ind].first);\n            use_edge[g[var][ind].second]\
    \ = 1;\n            st_edge.push_back(g[var][ind].second);\n            deg[var]--;\n\
    \            deg[g[var][ind].first]++;\n        }\n        edge_index[var]++;\n\
    \    }\n\n    for (auto x : deg) if (x < 0) return {{}, {}};\n    if (real_edge\
    \ + 1 != (int)res_var.size()) return {{}, {}};\n    std::reverse(res_var.begin(),\
    \ res_var.end());\n    res_edge.pop_back();\n    std::reverse(res_edge.begin(),\
    \ res_edge.end());\n    return {res_var, res_edge};\n}\n}\n#line 4 \"test/graph/eulerian_trail_undir.test.cpp\"\
    \n#include <iostream>\nvoid solve();\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t = 1;\n    std::cin >> t;\n    while (t--)\
    \ solve();\n}\n\nvoid solve(){\n    int N, M;\n    std::cin >> N >> M;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> G(N);\n    for (int i = 0; i < M; i++){\n        int a, b;\n        std::cin\
    \ >> a >> b;\n        G[a].push_back({b, i});\n        G[b].push_back({a, i});\n\
    \    }\n    auto [var, edge] = po167::Eulerian_trail(G, M, -1, false);\n    if\
    \ (var.empty()){\n        std::cout << \"No\\n\";\n    }\n    else{\n        std::cout\
    \ << \"Yes\\n\";\n        for (int i = 0; i < (int)var.size(); i++){\n       \
    \     std::cout << var[i] << (i + 1 == (int)var.size() ? \"\\n\" : \" \");\n \
    \       }\n        for (int i = 0; i < (int)edge.size(); i++){\n            std::cout\
    \ << edge[i] << (i + 1 == (int)edge.size() ? \"\\n\" : \" \");\n        }\n  \
    \      if (edge.empty()) std::cout << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n\n#include \"graph/Eulerian_trail.hpp\"\n#include <iostream>\nvoid solve();\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int t = 1;\n    std::cin >> t;\n    while (t--) solve();\n}\n\nvoid solve(){\n\
    \    int N, M;\n    std::cin >> N >> M;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> G(N);\n    for (int i = 0; i < M; i++){\n        int a, b;\n        std::cin\
    \ >> a >> b;\n        G[a].push_back({b, i});\n        G[b].push_back({a, i});\n\
    \    }\n    auto [var, edge] = po167::Eulerian_trail(G, M, -1, false);\n    if\
    \ (var.empty()){\n        std::cout << \"No\\n\";\n    }\n    else{\n        std::cout\
    \ << \"Yes\\n\";\n        for (int i = 0; i < (int)var.size(); i++){\n       \
    \     std::cout << var[i] << (i + 1 == (int)var.size() ? \"\\n\" : \" \");\n \
    \       }\n        for (int i = 0; i < (int)edge.size(); i++){\n            std::cout\
    \ << edge[i] << (i + 1 == (int)edge.size() ? \"\\n\" : \" \");\n        }\n  \
    \      if (edge.empty()) std::cout << \"\\n\";\n    }\n}"
  dependsOn:
  - graph/Eulerian_trail.hpp
  isVerificationFile: true
  path: test/graph/eulerian_trail_undir.test.cpp
  requiredBy: []
  timestamp: '2026-03-25 04:41:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/eulerian_trail_undir.test.cpp
layout: document
redirect_from:
- /verify/test/graph/eulerian_trail_undir.test.cpp
- /verify/test/graph/eulerian_trail_undir.test.cpp.html
title: test/graph/eulerian_trail_undir.test.cpp
---
