template<class G> struct HLD {
    using vi = vector<int>;
    #define sz(p) (int)(p).size()
    G& g;
    ll n, id;
    vi siz, dep, down, up, nxt, par;
    void dfs_sz(ll i) {
        siz[i] = 1;
        if(sz(g[i]) > 1 && par[i] == g[i][0]) swap(g[i][0], g[i][1]);
        for(auto& j : g[i]) {
            if(j != par[i]) {
                dep[j] = dep[i] + 1;
                par[j] = i;
                dfs_sz(j);
                siz[i] += siz[j];
                if(siz[j] > siz[g[i][0]]) swap(j, g[i][0]);
            }
        }
    }
    void dfs_hld(ll i) {
        down[i] = id++;
        for(auto j : g[i]) if(j != par[i]) {
                nxt[j] = j == g[i][0] ? nxt[i] : j;
                dfs_hld(j);
            }
        up[i] = id;
    }
    // [u, v)
    vector<pair<ll, ll>> ascend(ll u, ll v) {
        vector<pair<ll, ll>> res;
        while(nxt[u] != nxt[v]) {
            res.emplace_back(down[u], down[nxt[u]]);
            u = par[nxt[u]];
        }
        if(u != v) res.emplace_back(down[u], down[v] + 1);
        return res;
    }
    // (u, v]
    vector<pair<ll, ll>> descend(ll u, ll v) {
        if(u == v) return {};
        if(nxt[u] == nxt[v]) return {{down[u] + 1, down[v]}};
        auto res = descend(u, par[nxt[v]]);
        res.emplace_back(down[nxt[v]], down[v]);
        return res;
    }
    HLD(G& g, ll v = 0) : g(g), n(sz(g)), id(0), siz(n), dep(n), down(n, -1), up(n, -1), nxt(n, v), par(n, v) {
        dfs_sz(v);
        dfs_hld(v);
    }
    pair<ll, ll> idx(ll i) { return {down[i], up[i]}; }
    void path_query(ll u, ll v, bool vtx, auto f, bool commut = 0) {
        ll l = lca(u, v);
        for(auto [s, t] : ascend(u, l)) {
            s++;
            (!commut && s > t) ? f(t, s) : f(s, t);
        }
        if(vtx) f(down[l], down[l] + 1);
        for(auto [s, t] : descend(l, v)) {
            t++;
            (!commut && s > t) ? f(t, s) : f(s, t);
        }
    }
    void subtree_query(ll u, bool vtx, auto f) {
        f(down[u] + !vtx, up[u]);
    }
    ll lca(ll a, ll b) {
        while(nxt[a] != nxt[b]) {
            if(down[a] < down[b]) swap(a, b);
            a = par[nxt[a]];
        }
        return dep[a] < dep[b] ? a : b;
    }
    ll dist(ll a, ll b) { return dep[a] + dep[b] - dep[lca(a, b)] * 2; }
};
