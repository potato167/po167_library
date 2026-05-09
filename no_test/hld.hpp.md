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
  bundledCode: "#line 1 \"no_test/hld.hpp\"\ntemplate<class G> struct HLD {\n    using\
    \ vi = vector<int>;\n    #define sz(p) (int)(p).size()\n    G& g;\n    ll n, id;\n\
    \    vi siz, dep, down, up, nxt, par;\n    void dfs_sz(ll i) {\n        siz[i]\
    \ = 1;\n        if(sz(g[i]) > 1 && par[i] == g[i][0]) swap(g[i][0], g[i][1]);\n\
    \        for(auto& j : g[i]) {\n            if(j != par[i]) {\n              \
    \  dep[j] = dep[i] + 1;\n                par[j] = i;\n                dfs_sz(j);\n\
    \                siz[i] += siz[j];\n                if(siz[j] > siz[g[i][0]])\
    \ swap(j, g[i][0]);\n            }\n        }\n    }\n    void dfs_hld(ll i) {\n\
    \        down[i] = id++;\n        for(auto j : g[i]) if(j != par[i]) {\n     \
    \           nxt[j] = j == g[i][0] ? nxt[i] : j;\n                dfs_hld(j);\n\
    \            }\n        up[i] = id;\n    }\n    // [u, v)\n    vector<pair<ll,\
    \ ll>> ascend(ll u, ll v) {\n        vector<pair<ll, ll>> res;\n        while(nxt[u]\
    \ != nxt[v]) {\n            res.emplace_back(down[u], down[nxt[u]]);\n       \
    \     u = par[nxt[u]];\n        }\n        if(u != v) res.emplace_back(down[u],\
    \ down[v] + 1);\n        return res;\n    }\n    // (u, v]\n    vector<pair<ll,\
    \ ll>> descend(ll u, ll v) {\n        if(u == v) return {};\n        if(nxt[u]\
    \ == nxt[v]) return {{down[u] + 1, down[v]}};\n        auto res = descend(u, par[nxt[v]]);\n\
    \        res.emplace_back(down[nxt[v]], down[v]);\n        return res;\n    }\n\
    \    HLD(G& g, ll v = 0) : g(g), n(sz(g)), id(0), siz(n), dep(n), down(n, -1),\
    \ up(n, -1), nxt(n, v), par(n, v) {\n        dfs_sz(v);\n        dfs_hld(v);\n\
    \    }\n    pair<ll, ll> idx(ll i) { return {down[i], up[i]}; }\n    void path_query(ll\
    \ u, ll v, bool vtx, auto f, bool commut = 0) {\n        ll l = lca(u, v);\n \
    \       for(auto [s, t] : ascend(u, l)) {\n            s++;\n            (!commut\
    \ && s > t) ? f(t, s) : f(s, t);\n        }\n        if(vtx) f(down[l], down[l]\
    \ + 1);\n        for(auto [s, t] : descend(l, v)) {\n            t++;\n      \
    \      (!commut && s > t) ? f(t, s) : f(s, t);\n        }\n    }\n    void subtree_query(ll\
    \ u, bool vtx, auto f) {\n        f(down[u] + !vtx, up[u]);\n    }\n    ll lca(ll\
    \ a, ll b) {\n        while(nxt[a] != nxt[b]) {\n            if(down[a] < down[b])\
    \ swap(a, b);\n            a = par[nxt[a]];\n        }\n        return dep[a]\
    \ < dep[b] ? a : b;\n    }\n    ll dist(ll a, ll b) { return dep[a] + dep[b] -\
    \ dep[lca(a, b)] * 2; }\n};\n"
  code: "template<class G> struct HLD {\n    using vi = vector<int>;\n    #define\
    \ sz(p) (int)(p).size()\n    G& g;\n    ll n, id;\n    vi siz, dep, down, up,\
    \ nxt, par;\n    void dfs_sz(ll i) {\n        siz[i] = 1;\n        if(sz(g[i])\
    \ > 1 && par[i] == g[i][0]) swap(g[i][0], g[i][1]);\n        for(auto& j : g[i])\
    \ {\n            if(j != par[i]) {\n                dep[j] = dep[i] + 1;\n   \
    \             par[j] = i;\n                dfs_sz(j);\n                siz[i]\
    \ += siz[j];\n                if(siz[j] > siz[g[i][0]]) swap(j, g[i][0]);\n  \
    \          }\n        }\n    }\n    void dfs_hld(ll i) {\n        down[i] = id++;\n\
    \        for(auto j : g[i]) if(j != par[i]) {\n                nxt[j] = j == g[i][0]\
    \ ? nxt[i] : j;\n                dfs_hld(j);\n            }\n        up[i] = id;\n\
    \    }\n    // [u, v)\n    vector<pair<ll, ll>> ascend(ll u, ll v) {\n       \
    \ vector<pair<ll, ll>> res;\n        while(nxt[u] != nxt[v]) {\n            res.emplace_back(down[u],\
    \ down[nxt[u]]);\n            u = par[nxt[u]];\n        }\n        if(u != v)\
    \ res.emplace_back(down[u], down[v] + 1);\n        return res;\n    }\n    //\
    \ (u, v]\n    vector<pair<ll, ll>> descend(ll u, ll v) {\n        if(u == v) return\
    \ {};\n        if(nxt[u] == nxt[v]) return {{down[u] + 1, down[v]}};\n       \
    \ auto res = descend(u, par[nxt[v]]);\n        res.emplace_back(down[nxt[v]],\
    \ down[v]);\n        return res;\n    }\n    HLD(G& g, ll v = 0) : g(g), n(sz(g)),\
    \ id(0), siz(n), dep(n), down(n, -1), up(n, -1), nxt(n, v), par(n, v) {\n    \
    \    dfs_sz(v);\n        dfs_hld(v);\n    }\n    pair<ll, ll> idx(ll i) { return\
    \ {down[i], up[i]}; }\n    void path_query(ll u, ll v, bool vtx, auto f, bool\
    \ commut = 0) {\n        ll l = lca(u, v);\n        for(auto [s, t] : ascend(u,\
    \ l)) {\n            s++;\n            (!commut && s > t) ? f(t, s) : f(s, t);\n\
    \        }\n        if(vtx) f(down[l], down[l] + 1);\n        for(auto [s, t]\
    \ : descend(l, v)) {\n            t++;\n            (!commut && s > t) ? f(t,\
    \ s) : f(s, t);\n        }\n    }\n    void subtree_query(ll u, bool vtx, auto\
    \ f) {\n        f(down[u] + !vtx, up[u]);\n    }\n    ll lca(ll a, ll b) {\n \
    \       while(nxt[a] != nxt[b]) {\n            if(down[a] < down[b]) swap(a, b);\n\
    \            a = par[nxt[a]];\n        }\n        return dep[a] < dep[b] ? a :\
    \ b;\n    }\n    ll dist(ll a, ll b) { return dep[a] + dep[b] - dep[lca(a, b)]\
    \ * 2; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: no_test/hld.hpp
  requiredBy: []
  timestamp: '2026-05-10 00:56:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: no_test/hld.hpp
layout: document
redirect_from:
- /library/no_test/hld.hpp
- /library/no_test/hld.hpp.html
title: no_test/hld.hpp
---
