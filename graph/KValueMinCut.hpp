#pragma once
#include <atcoder/maxflow>
#include <vector>
#include <tuple>
#include <utility>
#include <cassert>
#include <limits>
#include <type_traits>

namespace po167 {

template<class T = long long>
struct KValueMinCut {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);

    int n, s, t;
    std::vector<int> R, base;
    std::vector<T> linear;
    std::vector<std::tuple<int, int, T>> edges;
    T constant = 0;

    explicit KValueMinCut(const std::vector<int>& r)
        : n(r.size()), R(r), base(n) {
        int m = 0;
        for (int i = 0; i < n; i++) {
            assert(R[i] >= 1);
            base[i] = m;
            m += R[i] - 1;
        }
        s = m;
        t = m + 1;
        linear.resize(m + 2);
    }

    // x(i,a) = [v[i] >= a]
    int node(int i, int a) const {
        assert(0 <= i && i < n);
        assert(0 <= a && a <= R[i]);
        if (a == 0) return s;
        if (a == R[i]) return t;
        return base[i] + a - 1;
    }

    // c * x(i,a)
    void add_linear(int i, int a, T c) {
        linear[node(i, a)] += c;
    }

    // c * [u is S-side and v is T-side]
    void add_edge(int u, int v, T c) {
        assert(c >= 0);
        if (c == 0 || u == v || u == t || v == s) return;
        if (u == s && v == t) constant += c;
        else edges.emplace_back(u, v, c);
    }

    // +c if v[i] == k
    void add_eq(int i, int k, T c) {
        assert(0 <= k && k < R[i]);
        add_linear(i, k, c);
        add_linear(i, k + 1, -c);
    }

    // +c if v[i] < a && v[j] >= b
    void add_lt_ge(int i, int a, int j, int b, T c) {
        add_edge(node(j, b), node(i, a), c);
    }

    // -c if v[i] < a && v[j] < b
    void add_lt_lt(int i, int a, int j, int b, T c) {
        assert(c >= 0);
        constant -= c;
        add_linear(i, a, c);
        add_lt_ge(i, a, j, b, c);
    }

    // -c if v[i] < a for every (i, a) in conditions
    void add_lt_lt(const std::vector<std::pair<int, int>>& conditions, T c) {
        assert(c >= 0);
        if (c == 0) return;
        constant -= c;
        if (conditions.empty()) return;
        int u = int(linear.size());
        linear.push_back(c);
        for (auto [i, a] : conditions) {
            add_edge(node(i, a), u, c);
        }
    }

    // -c if v[i] >= a && v[j] >= b
    void add_ge_ge(int i, int a, int j, int b, T c) {
        assert(c >= 0);
        add_linear(i, a, -c);
        add_edge(node(i, a), node(j, b), c);
    }

    // -c if v[i] >= a for every (i, a) in conditions
    void add_ge_ge(const std::vector<std::pair<int, int>>& conditions, T c) {
        assert(c >= 0);
        if (c == 0) return;
        if (conditions.empty()) {
            constant -= c;
            return;
        }
        int u = int(linear.size());
        linear.push_back(-c);
        for (auto [i, a] : conditions) {
            add_edge(u, node(i, a), c);
        }
    }

    // +c if [v[i] >= a] != [v[j] >= b]
    void add_diff(int i, int a, int j, int b, T c) {
        add_lt_ge(i, a, j, b, c);
        add_lt_ge(j, b, i, a, c);
    }

    // return {minimum cost, optimal v}
    std::pair<T, std::vector<int>> run() const {
        int vertices = int(linear.size());
        T sum = 0;
        auto add_sum = [&](T c) {
            assert(c >= 0 && c < std::numeric_limits<T>::max() - sum);
            sum += c;
        };

        for (auto [u, v, c] : edges) add_sum(c);
        for (int u = 0; u < vertices; u++) {
            if (u == s || u == t) continue;
            assert(linear[u] != std::numeric_limits<T>::min());
            add_sum(linear[u] < 0 ? -linear[u] : linear[u]);
        }

        atcoder::mf_graph<T> graph(vertices);
        for (auto [u, v, c] : edges) graph.add_edge(u, v, c);

        T ans = constant + linear[s];
        for (int u = 0; u < vertices; u++) {
            if (u == s || u == t) continue;
            if (linear[u] > 0) {
                graph.add_edge(u, t, linear[u]);
            } else if (linear[u] < 0) {
                graph.add_edge(s, u, -linear[u]);
                ans += linear[u];
            }
        }

        T inf = sum + 1;
        for (int i = 0; i < n; i++) {
            for (int a = 1; a + 1 < R[i]; a++) {
                graph.add_edge(node(i, a + 1), node(i, a), inf);
            }
        }

        ans += graph.flow(s, t);
        auto side = graph.min_cut(s);

        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            for (int a = 1; a < R[i]; a++) {
                if (side[node(i, a)]) v[i] = a;
            }
        }
        return {ans, v};
    }
};

}
