#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace po167::dynamic_connectivity_detail {

struct EmptyValue {};

template<class T>
struct EulerTourAggregate {
    T sum{};
};

template<>
struct EulerTourAggregate<void> {};

// Splay forest with one occurrence of each vertex and two of each tree edge.
// The dynamic connectivity levels use the marks to locate edges for promotion.
template<class T>
class EulerTourTree {
    using Value = std::conditional_t<std::is_void_v<T>, EmptyValue, T>;
    static constexpr unsigned char exact_edge = 1;
    static constexpr unsigned char incident_edge = 2;

    struct Node : EulerTourAggregate<T> {
        int child[2]{};
        int parent = 0;
        int size = 0;
        int item = 0;  // Vertex number or the bitwise complement of an edge ID.
        int extra = 0; // Incidence head on a vertex, lower-level handle on a forward arc.
        unsigned char marks = 0;
        unsigned char subtree_marks = 0;
    };

    std::vector<Node> nodes;
    std::vector<int> vertex_nodes; // Higher levels create vertex occurrences on demand.
    std::vector<Value> values;
    int free_arc = 0;

    int vertex(int v) const {
        return vertex_nodes.empty() ? v + 1 : vertex_nodes[v];
    }

    int ensure_vertex(int v) {
        int x = vertex(v);
        if (x == 0) {
            x = static_cast<int>(nodes.size());
            nodes.emplace_back();
            nodes[x].item = v;
            nodes[x].size = 1;
            vertex_nodes[v] = x;
        }
        return x;
    }

    void attach_child(int parent, bool right, int child) {
        nodes[parent].child[right] = child;
        nodes[child].parent = parent;
    }

    void pull(int x) {
        Node& node = nodes[x];
        const Node& left = nodes[node.child[0]];
        const Node& right = nodes[node.child[1]];
        const bool is_vertex = node.item >= 0;
        node.size = left.size + is_vertex + right.size;
        node.subtree_marks = left.subtree_marks | node.marks | right.subtree_marks;
        if constexpr (!std::is_void_v<T>) {
            if (is_vertex) {
                const T& value = values[node.item];
                node.sum = node.child[0] ? left.sum + value : value;
                if (node.child[1]) node.sum = node.sum + right.sum;
            } else if (node.child[0] && node.child[1]) {
                node.sum = left.sum + right.sum;
            } else {
                node.sum = node.child[0] ? left.sum : right.sum;
            }
        }
    }

    void rotate(int x) {
        const int p = nodes[x].parent;
        const int g = nodes[p].parent;
        const bool right = nodes[p].child[1] == x;
        const int middle = nodes[x].child[!right];
        nodes[p].child[right] = middle;
        if (middle) nodes[middle].parent = p;
        attach_child(x, !right, p);
        nodes[x].parent = g;
        if (g) nodes[g].child[nodes[g].child[1] == p] = x;

        // The whole rotated subtree keeps its sequence and aggregate.
        nodes[x].size = nodes[p].size;
        nodes[x].subtree_marks = nodes[p].subtree_marks;
        if constexpr (!std::is_void_v<T>) nodes[x].sum = nodes[p].sum;
        pull(p);
    }

    void splay(int x) {
        while (const int p = nodes[x].parent) {
            const int g = nodes[p].parent;
            if (g) {
                const bool aligned = (nodes[g].child[1] == p) == (nodes[p].child[1] == x);
                rotate(aligned ? p : x);
            }
            rotate(x);
        }
    }

    int join(int left, int right) {
        if (!left) return right;
        if (!right) return left;
        while (nodes[left].child[1]) left = nodes[left].child[1];
        splay(left);
        attach_child(left, true, right);
        pull(left);
        return left;
    }

    int find_marked(int v, unsigned char mark) {
        int x = vertex(v);
        if (!x) return 0;
        splay(x);
        if (!(nodes[x].subtree_marks & mark)) return 0;
        while (!(nodes[x].marks & mark)) {
            const int left = nodes[x].child[0];
            x = nodes[left].subtree_marks & mark ? left : nodes[x].child[1];
            assert(x != 0);
        }
        splay(x);
        return x;
    }

public:
    explicit EulerTourTree(int n, bool sparse = false)
        : nodes(sparse ? 1 : static_cast<std::size_t>(n) + 1), vertex_nodes(sparse ? n : 0) {
        if constexpr (!std::is_void_v<T>) values.resize(n);
        if (!sparse) {
            for (int v = 0; v < n; ++v) {
                nodes[v + 1].item = v;
                nodes[v + 1].size = 1;
            }
        }
    }

    bool same(int u, int v) {
        if (u == v) return true;
        const int a = vertex(u), b = vertex(v);
        if (!a || !b) return false;
        splay(a);
        splay(b);
        // Splaying b moves a away from the root only in a shared tour.
        return nodes[a].parent != 0;
    }

    int size(int v) {
        const int x = vertex(v);
        if (!x) return 1;
        splay(x);
        return nodes[x].size;
    }

    // The two vertices must be in distinct trees. Returns the forward arc handle.
    int link(int u, int v, int edge, int lower_arc, bool exact) {
        const int a = ensure_vertex(u), b = ensure_vertex(v);
        splay(a);
        splay(b);

        // Rotate v's tour to start at v, then splice it immediately after u.
        int tour = b;
        if (const int prefix = nodes[b].child[0]) {
            nodes[prefix].parent = 0;
            nodes[b].child[0] = 0;
            pull(b);
            tour = join(b, prefix);
        }

        int arc = free_arc;
        if (arc) {
            free_arc = nodes[arc].parent;
            nodes[arc] = Node{};
            nodes[arc + 1] = Node{};
        } else {
            arc = static_cast<int>(nodes.size());
            nodes.resize(nodes.size() + 2);
        }
        const int reverse = arc + 1;
        const int suffix = nodes[a].child[1];
        nodes[arc].item = nodes[reverse].item = ~edge;
        nodes[arc].extra = lower_arc;
        nodes[arc].marks = exact ? exact_edge : 0;
        attach_child(arc, true, tour);
        attach_child(reverse, false, arc);
        if (suffix) attach_child(reverse, true, suffix);
        attach_child(a, true, reverse);
        pull(arc);
        pull(reverse);
        pull(a);
        return arc;
    }

    // Splits the tour at the two occurrences of an edge, then joins its outer pieces.
    int cut(int arc) {
        const int lower_arc = nodes[arc].extra;
        splay(arc);
        const int left = nodes[arc].child[0], right = nodes[arc].child[1];
        if (left) nodes[left].parent = 0;
        if (right) nodes[right].parent = 0;
        const int reverse = arc + 1;
        splay(reverse);
        const bool reverse_on_left = left && (left == reverse || nodes[left].parent);
        const int before = nodes[reverse].child[0], after = nodes[reverse].child[1];
        if (before) nodes[before].parent = 0;
        if (after) nodes[after].parent = 0;
        if (reverse_on_left) join(before, right);
        else join(left, after);
        nodes[arc].parent = free_arc;
        free_arc = arc;
        return lower_arc;
    }

    int take_exact_edge(int v) {
        const int x = find_marked(v, exact_edge);
        if (!x) return 0;
        nodes[x].marks = 0;
        pull(x);
        return ~nodes[x].item;
    }

    int incident_vertex(int v) {
        const int x = find_marked(v, incident_edge);
        return x ? nodes[x].item : -1;
    }

    int incidence_head(int v) const {
        return nodes[vertex(v)].extra;
    }

    void set_incidence_head(int v, int head) {
        const int x = head ? ensure_vertex(v) : vertex(v);
        const bool changed = (nodes[x].extra == 0) != (head == 0);
        nodes[x].extra = head;
        if (!changed) return;
        splay(x);
        nodes[x].marks = head ? incident_edge : 0;
        pull(x);
    }

    void update(int v, const Value& delta) {
        const int x = vertex(v);
        splay(x);
        values[v] = values[v] + delta;
        pull(x);
    }

    Value get_sum(int v) {
        const int x = vertex(v);
        splay(x);
        return nodes[x].sum;
    }

    std::vector<int> get_vertex(int v) {
        const int x = vertex(v);
        if (!x) return {v};
        splay(x);
        std::vector<int> result;
        result.reserve(nodes[x].size);
        std::vector<int> stack{x};
        while (!stack.empty()) {
            const int current = stack.back();
            stack.pop_back();
            const Node& node = nodes[current];
            if (node.item >= 0) result.push_back(node.item);
            for (int child : node.child) {
                if (child) stack.push_back(child);
            }
        }
        return result;
    }
};

}
