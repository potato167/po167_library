---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/agc023/submissions/40321108
  bundledCode: "#line 2 \"no_test/zero_one_tree.hpp\"\n#include <vector>\n#include\
    \ <algorithm>\n#include <queue>\n#include <functional>\n#include <utility>\nnamespace\
    \ po167{\n//minmize \\sum_{i=0,1,...,n-1}(u[q[i]]*\\sum_{j=0,1,...,i}(d[q[j]]))\n\
    //st q is permutation\n//order[p[i]]<order[i]\n//p[root]=-1\n//https://atcoder.jp/contests/agc023/submissions/40321108\n\
    std::pair<long long, std::vector<int>> scheduling_cost(std::vector<int> p, std::vector<int>\
    \ u, std::vector<int> d) {\n    int n=p.size();\n    struct _job{\n        long\
    \ long cost;\n        long long time;\n        int ind;\n        int hash = 0;\n\
    \    };\n    std::vector<int> par(n);\n    std::vector<_job> val(n);\n    long\
    \ long ans=0;\n    for (int i = 0; i< n; i++){\n        par[i] = i;\n        val[i].cost\
    \ = (long long)u[i];\n        val[i].time = (long long)d[i];\n        val[i].ind\
    \ = i;\n        ans += val[i].cost * val[i].time;\n    }\n    auto concat_job\
    \ = [&](_job &l, _job r) -> void {\n        ans += l.time * r.cost;\n        l.time\
    \ += r.time;\n        l.cost += r.cost;\n    };\n    auto comp_job = [&](_job\
    \ l, _job r) -> bool {\n        if (r.time == 0 && r.cost == 0) return false;\n\
    \        if (l.time == 0 && l.cost == 0) return true;\n        return l.cost *\
    \ r.time < l.time * r.cost;\n    };\n    auto root = [&](auto self, int a)-> int\
    \ {\n        if (a == par[a]) return a;\n        par[a] = self(self, par[a]);\n\
    \        return par[a];\n    };\n    std::priority_queue<_job,std::vector<_job>,\
    \ std::function<bool(_job, _job)>> pq(comp_job);\n    int t = -1;\n    for (int\
    \ i = 0; i < n; i++){\n        if (p[i] == -1) t = i;\n    }\n    std::vector<int>\
    \ seen(n), hash(n);\n    for (int i = 0; i < n; i++){\n        if (i != t){\n\
    \            pq.push(val[i]);\n        }\n    }\n    int count = 0;\n    while\
    \ (!pq.empty()){\n        _job tmp = pq.top();\n        pq.pop();\n        if\
    \ (tmp.hash != hash[tmp.ind]) continue;\n        seen[tmp.ind] = n - count;\n\
    \        count++;\n        par[tmp.ind] = p[tmp.ind];\n        int r = root(root,\
    \ tmp.ind);\n        concat_job(val[r], tmp);\n        if (r != t){\n        \
    \    val[r].hash = count;\n            hash[r] = count;\n            pq.push(val[r]);\n\
    \        }\n    }\n    std::vector<int> order;\n    order.reserve(n);\n    std::vector<std::vector<int>>\
    \ G(n);\n    std::priority_queue<std::pair<int, int>> valid;\n    for (int i =\
    \ 0; i < n; i++){\n        if (0 <= p[i]) G[p[i]].push_back(i);\n        else\
    \ valid.push({seen[i], i});\n    }\n    while (!valid.empty()){\n        int a\
    \ = valid.top().second;\n        order.push_back(a);\n        valid.pop();\n \
    \       for (auto x : G[a]) valid.push({seen[x], x});\n    }\n    return {ans,\
    \ order};\n}\n}\n"
  code: "#pragma once\n#include <vector>\n#include <algorithm>\n#include <queue>\n\
    #include <functional>\n#include <utility>\nnamespace po167{\n//minmize \\sum_{i=0,1,...,n-1}(u[q[i]]*\\\
    sum_{j=0,1,...,i}(d[q[j]]))\n//st q is permutation\n//order[p[i]]<order[i]\n//p[root]=-1\n\
    //https://atcoder.jp/contests/agc023/submissions/40321108\nstd::pair<long long,\
    \ std::vector<int>> scheduling_cost(std::vector<int> p, std::vector<int> u, std::vector<int>\
    \ d) {\n    int n=p.size();\n    struct _job{\n        long long cost;\n     \
    \   long long time;\n        int ind;\n        int hash = 0;\n    };\n    std::vector<int>\
    \ par(n);\n    std::vector<_job> val(n);\n    long long ans=0;\n    for (int i\
    \ = 0; i< n; i++){\n        par[i] = i;\n        val[i].cost = (long long)u[i];\n\
    \        val[i].time = (long long)d[i];\n        val[i].ind = i;\n        ans\
    \ += val[i].cost * val[i].time;\n    }\n    auto concat_job = [&](_job &l, _job\
    \ r) -> void {\n        ans += l.time * r.cost;\n        l.time += r.time;\n \
    \       l.cost += r.cost;\n    };\n    auto comp_job = [&](_job l, _job r) ->\
    \ bool {\n        if (r.time == 0 && r.cost == 0) return false;\n        if (l.time\
    \ == 0 && l.cost == 0) return true;\n        return l.cost * r.time < l.time *\
    \ r.cost;\n    };\n    auto root = [&](auto self, int a)-> int {\n        if (a\
    \ == par[a]) return a;\n        par[a] = self(self, par[a]);\n        return par[a];\n\
    \    };\n    std::priority_queue<_job,std::vector<_job>, std::function<bool(_job,\
    \ _job)>> pq(comp_job);\n    int t = -1;\n    for (int i = 0; i < n; i++){\n \
    \       if (p[i] == -1) t = i;\n    }\n    std::vector<int> seen(n), hash(n);\n\
    \    for (int i = 0; i < n; i++){\n        if (i != t){\n            pq.push(val[i]);\n\
    \        }\n    }\n    int count = 0;\n    while (!pq.empty()){\n        _job\
    \ tmp = pq.top();\n        pq.pop();\n        if (tmp.hash != hash[tmp.ind]) continue;\n\
    \        seen[tmp.ind] = n - count;\n        count++;\n        par[tmp.ind] =\
    \ p[tmp.ind];\n        int r = root(root, tmp.ind);\n        concat_job(val[r],\
    \ tmp);\n        if (r != t){\n            val[r].hash = count;\n            hash[r]\
    \ = count;\n            pq.push(val[r]);\n        }\n    }\n    std::vector<int>\
    \ order;\n    order.reserve(n);\n    std::vector<std::vector<int>> G(n);\n   \
    \ std::priority_queue<std::pair<int, int>> valid;\n    for (int i = 0; i < n;\
    \ i++){\n        if (0 <= p[i]) G[p[i]].push_back(i);\n        else valid.push({seen[i],\
    \ i});\n    }\n    while (!valid.empty()){\n        int a = valid.top().second;\n\
    \        order.push_back(a);\n        valid.pop();\n        for (auto x : G[a])\
    \ valid.push({seen[x], x});\n    }\n    return {ans, order};\n}\n}"
  dependsOn: []
  isVerificationFile: false
  path: no_test/zero_one_tree.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/zero_one_tree.hpp
layout: document
redirect_from:
- /library/no_test/zero_one_tree.hpp
- /library/no_test/zero_one_tree.hpp.html
title: no_test/zero_one_tree.hpp
---
