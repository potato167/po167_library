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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.0/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ graph/tree/Auxiliary_Tree.hpp: line 2: #pragma once found in a non-first line\n"
  code: "\n#pragma once\n#include \"LCA.hpp\"\n#include <vector>\n#include <stack>\n\
    \nnamespace po167{\nstruct Auxiliary_Tree{\n    std::vector<int> pre_order_list;\n\
    \    std::vector<int> pre_order_inv;\n    int n;\n    po167::LCA L;\n    std::vector<int>\
    \ out_order;\n    Auxiliary_Tree(std::vector<std::vector<int>> g, int root = 0){\n\
    \        std::stack<int> st;\n        n = (int)g.size();\n        std::vector<int>\
    \ seen(n);\n        seen[root] = 0;\n        st.push(root);\n        while (!st.empty()){\n\
    \            int a = st.top();\n            st.pop();\n            pre_order_list.push_back(a);\n\
    \            for (auto x : g[a]) if (seen[x] == 0){\n                seen[x] =\
    \ 1;\n                st.push(x);\n            }\n        }\n        assert((int)pre_order_list.size()\
    \ == n);\n        pre_order_inv.resize(n);\n        for (int i = 0; i < n; i++)\
    \ pre_order_inv[pre_order_list[i]] = i;\n        L.init(g);\n        out_order.resize(n,\
    \ -1);\n    }\n    std::tuple<std::vector<int>, std::vector<int>> bulid(std::vector<int>\
    \ v){\n        std::sort(v.begin(), v.end(), [&](int l, int r){\n            return\
    \ pre_order_inv[l] < pre_order_inv[r];\n        });\n        v.erase(std::unique(v.begin(),\
    \ v.end()), v.end());\n        int m = v.size();\n        for (int i = 0; i <\
    \ m - 1; i++){\n            v.push_back(L.lca(v[i], v[i + 1]));\n        }\n \
    \       std::sort(v.begin(), v.end(), [&](int l, int r){\n            return pre_order_inv[l]\
    \ < pre_order_inv[r];\n        });\n        v.erase(std::unique(v.begin(), v.end()),\
    \ v.end());\n        m = v.size();\n        for (int i = 0; i < m; i++){\n   \
    \         out_order[v[i]] = i;\n        }\n        std::stack<int> st;\n     \
    \   st.push(v[0]);\n        std::vector<int> pare(m, -1);\n        for (int i\
    \ = 1; i < m; i++){\n            while (st.top() != L.lca(st.top(), v[i])) st.pop();\n\
    \            pare[i] = out_order[st.top()];\n            st.push(v[i]);\n    \
    \    }\n        return {v, pare};\n    }\n};\n}"
  dependsOn:
  - graph/tree/LCA.hpp
  - ds/Sparse_table.hpp
  isVerificationFile: false
  path: graph/tree/Auxiliary_Tree.hpp
  requiredBy: []
  timestamp: '2025-03-24 15:48:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/tree/Auxiliary_Tree.hpp
layout: document
redirect_from:
- /library/graph/tree/Auxiliary_Tree.hpp
- /library/graph/tree/Auxiliary_Tree.hpp.html
title: graph/tree/Auxiliary_Tree.hpp
---
