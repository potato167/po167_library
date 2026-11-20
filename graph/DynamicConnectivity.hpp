#pragma once

#include "tree/EulerTourTree.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace po167 {

// Online connectivity for an undirected simple graph with vertices [0, n).
// Reference: https://qiita.com/hotman78/items/78cd3aa50b05a57738d4
// Expected amortized O(log n) for link and O(log^2 n) for cut.
// Connectivity, component size/sum and vertex updates take amortized O(log n).
// Space: O(m + n log n), where m is the maximum number of simultaneous edges.
// For component sums, T{} is zero and operator+ is associative and commutative.
template<class T = void>
class DynamicConnectivity {
    template<class U>
    using Forest = dynamic_connectivity_detail::EulerTourTree<U>;
    using Value = std::conditional_t<std::is_void_v<T>, dynamic_connectivity_detail::EmptyValue, T>;

    struct Incidence {
        int prev = 0;
        int next = 0;
    };

    struct Edge {
        int endpoint[2]{};
        int level = 0;
        int arc = 0; // Highest-level tree arc, or zero for a non-tree edge.
        Incidence incidence[2]{};
    };

    struct EdgeHash {
        std::size_t operator()(std::uint64_t key) const noexcept {
            key = (key ^ (key >> 30)) * 0xbf58476d1ce4e5b9ULL;
            key = (key ^ (key >> 27)) * 0x94d049bb133111ebULL;
            return static_cast<std::size_t>(key ^ (key >> 31));
        }
    };

    int n;
    Forest<T> base;
    std::deque<Forest<void>> upper; // Appending a level preserves references used by reconnect.
    std::unordered_map<std::uint64_t, int, EdgeHash> edge_id;
    std::vector<Edge> edges{1};
    int free_edge = 0;

    void check_vertex([[maybe_unused]] int v) const {
        assert(0 <= v && v < n);
    }

    static std::uint64_t key(int u, int v) {
        if (u > v) std::swap(u, v);
        return (static_cast<std::uint64_t>(u) << 32) | static_cast<std::uint32_t>(v);
    }

    Forest<void>& next_forest(int level) {
        const int count = static_cast<int>(upper.size());
        assert(level <= count);
        if (level == count) upper.emplace_back(n, true);
        return upper[level];
    }

    int make_edge(int u, int v) {
        const Edge edge{{u, v}};
        int id = free_edge;
        if (id) {
            free_edge = edges[id].endpoint[0];
            edges[id] = edge;
        } else {
            id = static_cast<int>(edges.size());
            edges.push_back(edge);
        }
        return id;
    }

    Incidence& incidence(int handle) {
        return edges[handle / 2].incidence[handle % 2];
    }

    // Each non-tree edge has two doubly linked list entries, one per endpoint.
    template<class U>
    void attach(Forest<U>& forest, int id) {
        Edge& edge = edges[id];
        for (int side = 0; side < 2; ++side) {
            const int v = edge.endpoint[side];
            const int head = forest.incidence_head(v);
            const int handle = 2 * id + side;
            edge.incidence[side] = {0, head};
            if (head) incidence(head).prev = handle;
            forest.set_incidence_head(v, handle);
        }
    }

    template<class U>
    void detach(Forest<U>& forest, int id) {
        const Edge& edge = edges[id];
        for (int side = 0; side < 2; ++side) {
            const auto [prev, next] = edge.incidence[side];
            if (next) incidence(next).prev = prev;
            if (prev) incidence(prev).next = next;
            else forest.set_incidence_head(edge.endpoint[side], next);
        }
    }

    void link_tree(int id) {
        Edge& edge = edges[id];
        const auto [u, v] = edge.endpoint;
        int arc = base.link(u, v, id, 0, edge.level == 0);
        for (int level = 1; level <= edge.level; ++level) {
            arc = upper[level - 1].link(u, v, id, arc, level == edge.level);
        }
        edge.arc = arc;
    }

    template<class U>
    bool reconnect(Forest<U>& forest, int u, int v, int level) {
        if (forest.size(u) > forest.size(v)) std::swap(u, v);
        // The smaller tree fits at the next level by the n / 2^level size invariant.
        while (const int id = forest.take_exact_edge(u)) {
            Edge& edge = edges[id];
            const auto [a, b] = edge.endpoint;
            edge.arc = next_forest(level).link(a, b, id, edge.arc, true);
            ++edge.level;
        }
        for (int a = forest.incident_vertex(u); a != -1; a = forest.incident_vertex(u)) {
            while (const int head = forest.incidence_head(a)) {
                const int id = head / 2;
                Edge& edge = edges[id];
                const int b = edge.endpoint[1 - head % 2];
                detach(forest, id);
                if (!forest.same(a, b)) {
                    link_tree(id);
                    return true;
                }
                ++edge.level;
                attach(next_forest(level), id);
            }
        }
        return false;
    }

public:
    explicit DynamicConnectivity(int n) : n(n), base(n) {}

    // Adds an edge and returns whether two components merged. Duplicate edges and loops are ignored.
    bool link(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return false;
        const auto [entry, inserted] = edge_id.try_emplace(key(u, v), 0);
        if (!inserted) return false;
        const int id = make_edge(u, v);
        entry->second = id;
        if (base.same(u, v)) {
            attach(base, id);
            return false;
        }
        link_tree(id);
        return true;
    }

    // Removes an edge and returns whether a component split. Missing edges are ignored.
    bool cut(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        if (u == v) return false;
        const auto entry = edge_id.find(key(u, v));
        if (entry == edge_id.end()) return false;
        const int id = entry->second;
        edge_id.erase(entry);
        Edge& edge = edges[id];
        int level = edge.level;
        int arc = edge.arc;
        bool split = false;
        if (arc) {
            for (int i = level; i > 0; --i) arc = upper[i - 1].cut(arc);
            base.cut(arc);
            while (level > 0 && !reconnect(upper[level - 1], u, v, level)) --level;
            split = level == 0 && !reconnect(base, u, v, 0);
        } else if (level) {
            detach(upper[level - 1], id);
        } else {
            detach(base, id);
        }
        edge.endpoint[0] = free_edge;
        free_edge = id;
        return split;
    }

    bool same(int u, int v) {
        check_vertex(u);
        check_vertex(v);
        return base.same(u, v);
    }

    int size(int v) {
        check_vertex(v);
        return base.size(v);
    }

    // Lists the component's vertices in unspecified order in amortized O(log n + size(v)).
    std::vector<int> get_vertex(int v) {
        check_vertex(v);
        return base.get_vertex(v);
    }

    template<class U = T, std::enable_if_t<!std::is_void_v<U>, int> = 0>
    void update(int v, const Value& delta) {
        check_vertex(v);
        base.update(v, delta);
    }

    template<class U = T, std::enable_if_t<!std::is_void_v<U>, int> = 0>
    Value get_sum(int v) {
        check_vertex(v);
        return base.get_sum(v);
    }
};

}
