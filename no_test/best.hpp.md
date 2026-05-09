---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"no_test/best.hpp\"\nnamespace po167{\n\ntemplate<class S>\n\
    std::vector<S> count_outdeg(std::vector<std::vector<S>> &G){\n    int N = G.size();\n\
    \    std::vector<S> outdeg(N);\n    for (int i = 0; i < N; i++) for (int j = 0;\
    \ j < N; j++) outdeg[i] += G[i][j];\n    return outdeg;\n}\n\ntemplate<class S>\n\
    std::vector<S> count_indeg(std::vector<std::vector<S>> &G){\n    int N = G.size();\n\
    \    std::vector<S> indeg(N);\n    for (int i = 0; i < N; i++) for (int j = 0;\
    \ j < N; j++) indeg[j] += G[i][j];\n    return indeg;\n}\n\n// O(|M|^{3})\ntemplate<class\
    \ T>\nT det_matrix(std::vector<std::vector<T>> M){\n    int N = M.size();\n  \
    \  if (N == 0) return 1;\n    if (N == 1) return M[0][0];\n    if (N == 2) return\
    \ M[0][0] * M[1][1] - M[0][1] * M[1][0];\n\n    T res = 1;\n    for (int i = 0;\
    \ i < N; i++){\n        for (int  j = i; j < N; j++){\n            if (M[j][i]\
    \ != 0){\n                if (j != i){\n                    swap(M[i], M[j]);\n\
    \                    res *= -1;\n                }\n                break;\n \
    \           }\n        }\n        if (M[i][i] == 0) return 0;\n        res *=\
    \ M[i][i];\n        if (i + 1 == N) break;\n        T v = 1 / M[i][i];\n     \
    \   for (int j = i + 1; j < N; j++){\n            T t = M[j][i] * v;\n       \
    \     for (int k = i; k < N; k++){\n                M[j][k] -= M[i][k] * t;\n\
    \            }\n        }\n    }\n    return res;\n}\n\ntemplate<class T,class\
    \ S>\nstd::vector<std::vector<T>> Directed_Matrix_tree_Theorem_sub(std::vector<std::vector<S>>\
    \ &G, int u = 0){\n    int N = G.size();\n    \n    std::vector L(N - 1, std::vector<T>(N\
    \ - 1, 0));\n    std::vector<S> outdeg(N);\n    for (int i = 0; i < N; i++) for\
    \ (int j = 0; j < N; j++) if (i != j) outdeg[i] += G[i][j];\n    for (int i =\
    \ 0; i < N; i++) for (int j = 0; j < N; j++){\n        if (i == u || j == u) continue;\n\
    \        int a = i, b = j;\n        if (u < i) a--;\n        if (u < j) b--;\n\
    \        if (i == j) L[a][b] = outdeg[i];\n        else L[a][b] -= G[i][j];\n\
    \    }\n    return L;\n}\n\n\ntemplate<class T,class S>\nT Directed_Matrix_tree_Theorem(std::vector<std::vector<S>>\
    \ &G, int u = 0){\n    if (int(G.size()) == 1) return T(1);\n    return det_matrix(Directed_Matrix_tree_Theorem_sub<T>(G,\
    \ u));\n}\n\n// s.t\n// forall i,j\n// 0 <= G[i][j]\n// if not connected\n// use\
    \ remove iso\ntemplate<class T,class S>\nstd::pair<T, std::vector<std::vector<T>>>\
    \ Count_Euler_Circuit_sub(std::vector<std::vector<S>> G, std::vector<T> &fact_base,\
    \ bool fact_in = true){\n    int N = G.size();\n    if (N == 0) return {1, {{1}}};\n\
    \    std::vector<S> outdeg = count_outdeg(G);\n    std::vector<S> indeg  = count_indeg(G);\n\
    \n    // indeg  == outdeg ?\n    for (int i = 0; i < N; i++) if (indeg[i] != outdeg[i])\
    \ return {0, {{1}}};\n\n    // connected ?\n    std::vector<bool> seen(N);\n \
    \   std::vector<int> order={0};\n    seen[0] = 1;\n    for (int i = 0; i < N;\
    \ i++){\n        if (i == int(order.size())) return {0, {{1}}};\n        for (int\
    \ j = 0; j < N; j++){\n            if (G[order[i]][j] != 0 && !seen[j]){\n   \
    \             seen[j] = 1;\n                order.push_back(j);\n            }\n\
    \        }\n    }\n    T res = 1;\n    if (fact_in) for (int i = 0; i < N; i++)\
    \ res *= fact_base[outdeg[i] - 1];\n    return {res ,Directed_Matrix_tree_Theorem_sub<T,\
    \ S>(G)};\n}\n\ntemplate<class T,class S>\nT Count_Euler_Circuit(std::vector<std::vector<S>>\
    \ G, std::vector<T> &fact_base, bool fact_in = true){\n    auto tmp = Count_Euler_Circuit_sub(G,\
    \ fact_base, fact_in);\n    if (tmp.first == 0) return T(0);\n    return tmp.first\
    \ * det_matrix(tmp.second);\n}\n\ntemplate<class S>\nstd::vector<std::vector<S>>\
    \ remove_isolated_vertex(\n    std::vector<std::vector<S>> G\n){\n    int N =\
    \ G.size();\n    std::vector<int> seen(N, -1);\n    for (int i = 0; i < N; i++)\
    \ for (int j = 0; j < N; j++){\n        if (G[i][j] != 0) seen[i] = 1, seen[j]\
    \ = 1;\n    }\n    int ind = 0;\n    for (int i = 0; i < N; i++) if (seen[i] ==\
    \ 1) seen[i] = ind++;\n    std::vector res(ind, std::vector<S>(ind));\n    for\
    \ (int i = 0; i < N; i++) if (seen[i] != -1){\n        for (int j = 0; j < N;\
    \ j++) if (seen[j] != -1){\n            res[seen[i]][seen[j]] = G[i][j];\n   \
    \     }\n    }\n    return res;\n}\n\n// s.t\n// forall i,j\n// 0 <= G[i][j]\n\
    // if not connected\n// use remove iso\ntemplate<class T,class S>\nstd::pair<T,\
    \ std::vector<std::vector<T>>> Count_Eulerian_Trail_sub(std::vector<std::vector<S>>\
    \ G,std::vector<T> &fact_base, bool fact_in = true){\n    bool ok = 1;\n    int\
    \ N = G.size();\n    if (N == 0) return {1, {{1}}};\n    std::vector<S> outdeg\
    \ = count_outdeg(G), indeg = count_indeg(G);\n    S sum = 0;\n    for (int i =\
    \ 0; i < N; i++){\n        sum += outdeg[i];\n    }\n    int st = -1, ed = -1;\n\
    \    for (int i = 0; i < N; i++) if (outdeg[i] != indeg[i]){\n        if (std::abs(outdeg[i]\
    \ - indeg[i]) > 1){\n            ok = 0;\n            break;\n        }\n    \
    \    if (outdeg[i] > indeg[i]){\n            if (ed != -1) ok = 0;\n         \
    \   ed = i;\n        } else {\n            if (st != -1) ok = 0;\n           \
    \ st = i;\n        }\n    }\n    if (!ok) return {0, {{1}}};\n    if ((st == -1)\
    \ ^ (ed == -1)) return {0, {{1}}};\n    if (st == -1){\n        auto tmp = Count_Euler_Circuit_sub(G,\
    \ fact_base, fact_in);\n        return {T(sum) * tmp.first, tmp.second};\n   \
    \ }\n    G[st][ed]++;\n    return Count_Euler_Circuit_sub(G, fact_base, fact_in);\n\
    }\n\ntemplate<class T,class S>\nT Count_Eulerian_Trail(std::vector<std::vector<S>>\
    \ G,std::vector<T> &fact_base, bool fact_in = true){\n    auto tmp = Count_Eulerian_Trail_sub<T,\
    \ S>(G, fact_base, fact_in);\n    if (tmp.first == 0) return 0;\n    return tmp.first\
    \ * det_matrix(tmp.second);\n}\n\n}\n"
  code: "namespace po167{\n\ntemplate<class S>\nstd::vector<S> count_outdeg(std::vector<std::vector<S>>\
    \ &G){\n    int N = G.size();\n    std::vector<S> outdeg(N);\n    for (int i =\
    \ 0; i < N; i++) for (int j = 0; j < N; j++) outdeg[i] += G[i][j];\n    return\
    \ outdeg;\n}\n\ntemplate<class S>\nstd::vector<S> count_indeg(std::vector<std::vector<S>>\
    \ &G){\n    int N = G.size();\n    std::vector<S> indeg(N);\n    for (int i =\
    \ 0; i < N; i++) for (int j = 0; j < N; j++) indeg[j] += G[i][j];\n    return\
    \ indeg;\n}\n\n// O(|M|^{3})\ntemplate<class T>\nT det_matrix(std::vector<std::vector<T>>\
    \ M){\n    int N = M.size();\n    if (N == 0) return 1;\n    if (N == 1) return\
    \ M[0][0];\n    if (N == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];\n\n\
    \    T res = 1;\n    for (int i = 0; i < N; i++){\n        for (int  j = i; j\
    \ < N; j++){\n            if (M[j][i] != 0){\n                if (j != i){\n \
    \                   swap(M[i], M[j]);\n                    res *= -1;\n      \
    \          }\n                break;\n            }\n        }\n        if (M[i][i]\
    \ == 0) return 0;\n        res *= M[i][i];\n        if (i + 1 == N) break;\n \
    \       T v = 1 / M[i][i];\n        for (int j = i + 1; j < N; j++){\n       \
    \     T t = M[j][i] * v;\n            for (int k = i; k < N; k++){\n         \
    \       M[j][k] -= M[i][k] * t;\n            }\n        }\n    }\n    return res;\n\
    }\n\ntemplate<class T,class S>\nstd::vector<std::vector<T>> Directed_Matrix_tree_Theorem_sub(std::vector<std::vector<S>>\
    \ &G, int u = 0){\n    int N = G.size();\n    \n    std::vector L(N - 1, std::vector<T>(N\
    \ - 1, 0));\n    std::vector<S> outdeg(N);\n    for (int i = 0; i < N; i++) for\
    \ (int j = 0; j < N; j++) if (i != j) outdeg[i] += G[i][j];\n    for (int i =\
    \ 0; i < N; i++) for (int j = 0; j < N; j++){\n        if (i == u || j == u) continue;\n\
    \        int a = i, b = j;\n        if (u < i) a--;\n        if (u < j) b--;\n\
    \        if (i == j) L[a][b] = outdeg[i];\n        else L[a][b] -= G[i][j];\n\
    \    }\n    return L;\n}\n\n\ntemplate<class T,class S>\nT Directed_Matrix_tree_Theorem(std::vector<std::vector<S>>\
    \ &G, int u = 0){\n    if (int(G.size()) == 1) return T(1);\n    return det_matrix(Directed_Matrix_tree_Theorem_sub<T>(G,\
    \ u));\n}\n\n// s.t\n// forall i,j\n// 0 <= G[i][j]\n// if not connected\n// use\
    \ remove iso\ntemplate<class T,class S>\nstd::pair<T, std::vector<std::vector<T>>>\
    \ Count_Euler_Circuit_sub(std::vector<std::vector<S>> G, std::vector<T> &fact_base,\
    \ bool fact_in = true){\n    int N = G.size();\n    if (N == 0) return {1, {{1}}};\n\
    \    std::vector<S> outdeg = count_outdeg(G);\n    std::vector<S> indeg  = count_indeg(G);\n\
    \n    // indeg  == outdeg ?\n    for (int i = 0; i < N; i++) if (indeg[i] != outdeg[i])\
    \ return {0, {{1}}};\n\n    // connected ?\n    std::vector<bool> seen(N);\n \
    \   std::vector<int> order={0};\n    seen[0] = 1;\n    for (int i = 0; i < N;\
    \ i++){\n        if (i == int(order.size())) return {0, {{1}}};\n        for (int\
    \ j = 0; j < N; j++){\n            if (G[order[i]][j] != 0 && !seen[j]){\n   \
    \             seen[j] = 1;\n                order.push_back(j);\n            }\n\
    \        }\n    }\n    T res = 1;\n    if (fact_in) for (int i = 0; i < N; i++)\
    \ res *= fact_base[outdeg[i] - 1];\n    return {res ,Directed_Matrix_tree_Theorem_sub<T,\
    \ S>(G)};\n}\n\ntemplate<class T,class S>\nT Count_Euler_Circuit(std::vector<std::vector<S>>\
    \ G, std::vector<T> &fact_base, bool fact_in = true){\n    auto tmp = Count_Euler_Circuit_sub(G,\
    \ fact_base, fact_in);\n    if (tmp.first == 0) return T(0);\n    return tmp.first\
    \ * det_matrix(tmp.second);\n}\n\ntemplate<class S>\nstd::vector<std::vector<S>>\
    \ remove_isolated_vertex(\n    std::vector<std::vector<S>> G\n){\n    int N =\
    \ G.size();\n    std::vector<int> seen(N, -1);\n    for (int i = 0; i < N; i++)\
    \ for (int j = 0; j < N; j++){\n        if (G[i][j] != 0) seen[i] = 1, seen[j]\
    \ = 1;\n    }\n    int ind = 0;\n    for (int i = 0; i < N; i++) if (seen[i] ==\
    \ 1) seen[i] = ind++;\n    std::vector res(ind, std::vector<S>(ind));\n    for\
    \ (int i = 0; i < N; i++) if (seen[i] != -1){\n        for (int j = 0; j < N;\
    \ j++) if (seen[j] != -1){\n            res[seen[i]][seen[j]] = G[i][j];\n   \
    \     }\n    }\n    return res;\n}\n\n// s.t\n// forall i,j\n// 0 <= G[i][j]\n\
    // if not connected\n// use remove iso\ntemplate<class T,class S>\nstd::pair<T,\
    \ std::vector<std::vector<T>>> Count_Eulerian_Trail_sub(std::vector<std::vector<S>>\
    \ G,std::vector<T> &fact_base, bool fact_in = true){\n    bool ok = 1;\n    int\
    \ N = G.size();\n    if (N == 0) return {1, {{1}}};\n    std::vector<S> outdeg\
    \ = count_outdeg(G), indeg = count_indeg(G);\n    S sum = 0;\n    for (int i =\
    \ 0; i < N; i++){\n        sum += outdeg[i];\n    }\n    int st = -1, ed = -1;\n\
    \    for (int i = 0; i < N; i++) if (outdeg[i] != indeg[i]){\n        if (std::abs(outdeg[i]\
    \ - indeg[i]) > 1){\n            ok = 0;\n            break;\n        }\n    \
    \    if (outdeg[i] > indeg[i]){\n            if (ed != -1) ok = 0;\n         \
    \   ed = i;\n        } else {\n            if (st != -1) ok = 0;\n           \
    \ st = i;\n        }\n    }\n    if (!ok) return {0, {{1}}};\n    if ((st == -1)\
    \ ^ (ed == -1)) return {0, {{1}}};\n    if (st == -1){\n        auto tmp = Count_Euler_Circuit_sub(G,\
    \ fact_base, fact_in);\n        return {T(sum) * tmp.first, tmp.second};\n   \
    \ }\n    G[st][ed]++;\n    return Count_Euler_Circuit_sub(G, fact_base, fact_in);\n\
    }\n\ntemplate<class T,class S>\nT Count_Eulerian_Trail(std::vector<std::vector<S>>\
    \ G,std::vector<T> &fact_base, bool fact_in = true){\n    auto tmp = Count_Eulerian_Trail_sub<T,\
    \ S>(G, fact_base, fact_in);\n    if (tmp.first == 0) return 0;\n    return tmp.first\
    \ * det_matrix(tmp.second);\n}\n\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/best.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/best.hpp
layout: document
redirect_from:
- /library/no_test/best.hpp
- /library/no_test/best.hpp.html
title: no_test/best.hpp
---
