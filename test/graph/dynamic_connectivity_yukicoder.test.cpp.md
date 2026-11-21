---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/DynamicConnectivity.hpp
    title: "\u30AA\u30F3\u30E9\u30A4\u30F3\u52D5\u7684\u9023\u7D50\u6027"
  - icon: ':heavy_check_mark:'
    path: graph/tree/EulerTourTree.hpp
    title: graph/tree/EulerTourTree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2072
    links:
    - https://yukicoder.me/problems/no/2072
  bundledCode: "#line 1 \"test/graph/dynamic_connectivity_yukicoder.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/2072\"\n\n#line 2 \"graph/DynamicConnectivity.hpp\"\
    \n\n#line 2 \"graph/tree/EulerTourTree.hpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace po167::dynamic_connectivity_detail\
    \ {\n\nstruct EmptyValue {};\n\ntemplate<class T>\nstruct EulerTourAggregate {\n\
    \    T sum{};\n};\n\ntemplate<>\nstruct EulerTourAggregate<void> {};\n\n// Splay\
    \ forest with one occurrence of each vertex and two of each tree edge.\n// The\
    \ dynamic connectivity levels use the marks to locate edges for promotion.\ntemplate<class\
    \ T>\nclass EulerTourTree {\n    using Value = std::conditional_t<std::is_void_v<T>,\
    \ EmptyValue, T>;\n    static constexpr unsigned char exact_edge = 1;\n    static\
    \ constexpr unsigned char incident_edge = 2;\n\n    struct Node : EulerTourAggregate<T>\
    \ {\n        int child[2]{};\n        int parent = 0;\n        int size = 0;\n\
    \        int item = 0;  // Vertex number or the bitwise complement of an edge\
    \ ID.\n        int extra = 0; // Incidence head on a vertex, lower-level handle\
    \ on a forward arc.\n        unsigned char marks = 0;\n        unsigned char subtree_marks\
    \ = 0;\n    };\n\n    std::vector<Node> nodes;\n    std::vector<int> vertex_nodes;\
    \ // Higher levels create vertex occurrences on demand.\n    std::vector<Value>\
    \ values;\n    int free_arc = 0;\n\n    int vertex(int v) const {\n        return\
    \ vertex_nodes.empty() ? v + 1 : vertex_nodes[v];\n    }\n\n    int ensure_vertex(int\
    \ v) {\n        int x = vertex(v);\n        if (x == 0) {\n            x = static_cast<int>(nodes.size());\n\
    \            nodes.emplace_back();\n            nodes[x].item = v;\n         \
    \   nodes[x].size = 1;\n            vertex_nodes[v] = x;\n        }\n        return\
    \ x;\n    }\n\n    void attach_child(int parent, bool right, int child) {\n  \
    \      nodes[parent].child[right] = child;\n        nodes[child].parent = parent;\n\
    \    }\n\n    void pull(int x) {\n        Node& node = nodes[x];\n        const\
    \ Node& left = nodes[node.child[0]];\n        const Node& right = nodes[node.child[1]];\n\
    \        const bool is_vertex = node.item >= 0;\n        node.size = left.size\
    \ + is_vertex + right.size;\n        node.subtree_marks = left.subtree_marks |\
    \ node.marks | right.subtree_marks;\n        if constexpr (!std::is_void_v<T>)\
    \ {\n            if (is_vertex) {\n                const T& value = values[node.item];\n\
    \                node.sum = node.child[0] ? left.sum + value : value;\n      \
    \          if (node.child[1]) node.sum = node.sum + right.sum;\n            }\
    \ else if (node.child[0] && node.child[1]) {\n                node.sum = left.sum\
    \ + right.sum;\n            } else {\n                node.sum = node.child[0]\
    \ ? left.sum : right.sum;\n            }\n        }\n    }\n\n    void rotate(int\
    \ x) {\n        const int p = nodes[x].parent;\n        const int g = nodes[p].parent;\n\
    \        const bool right = nodes[p].child[1] == x;\n        const int middle\
    \ = nodes[x].child[!right];\n        nodes[p].child[right] = middle;\n       \
    \ if (middle) nodes[middle].parent = p;\n        attach_child(x, !right, p);\n\
    \        nodes[x].parent = g;\n        if (g) nodes[g].child[nodes[g].child[1]\
    \ == p] = x;\n\n        // The whole rotated subtree keeps its sequence and aggregate.\n\
    \        nodes[x].size = nodes[p].size;\n        nodes[x].subtree_marks = nodes[p].subtree_marks;\n\
    \        if constexpr (!std::is_void_v<T>) nodes[x].sum = nodes[p].sum;\n    \
    \    pull(p);\n    }\n\n    void splay(int x) {\n        while (const int p =\
    \ nodes[x].parent) {\n            const int g = nodes[p].parent;\n           \
    \ if (g) {\n                const bool aligned = (nodes[g].child[1] == p) == (nodes[p].child[1]\
    \ == x);\n                rotate(aligned ? p : x);\n            }\n          \
    \  rotate(x);\n        }\n    }\n\n    int join(int left, int right) {\n     \
    \   if (!left) return right;\n        if (!right) return left;\n        while\
    \ (nodes[left].child[1]) left = nodes[left].child[1];\n        splay(left);\n\
    \        attach_child(left, true, right);\n        pull(left);\n        return\
    \ left;\n    }\n\n    int find_marked(int v, unsigned char mark) {\n        int\
    \ x = vertex(v);\n        if (!x) return 0;\n        splay(x);\n        if (!(nodes[x].subtree_marks\
    \ & mark)) return 0;\n        while (!(nodes[x].marks & mark)) {\n           \
    \ const int left = nodes[x].child[0];\n            x = nodes[left].subtree_marks\
    \ & mark ? left : nodes[x].child[1];\n            assert(x != 0);\n        }\n\
    \        splay(x);\n        return x;\n    }\n\npublic:\n    explicit EulerTourTree(int\
    \ n, bool sparse = false)\n        : nodes(sparse ? 1 : static_cast<std::size_t>(n)\
    \ + 1), vertex_nodes(sparse ? n : 0) {\n        if constexpr (!std::is_void_v<T>)\
    \ values.resize(n);\n        if (!sparse) {\n            for (int v = 0; v < n;\
    \ ++v) {\n                nodes[v + 1].item = v;\n                nodes[v + 1].size\
    \ = 1;\n            }\n        }\n    }\n\n    bool same(int u, int v) {\n   \
    \     if (u == v) return true;\n        const int a = vertex(u), b = vertex(v);\n\
    \        if (!a || !b) return false;\n        splay(a);\n        splay(b);\n \
    \       // Splaying b moves a away from the root only in a shared tour.\n    \
    \    return nodes[a].parent != 0;\n    }\n\n    int size(int v) {\n        const\
    \ int x = vertex(v);\n        if (!x) return 1;\n        splay(x);\n        return\
    \ nodes[x].size;\n    }\n\n    // The two vertices must be in distinct trees.\
    \ Returns the forward arc handle.\n    int link(int u, int v, int edge, int lower_arc,\
    \ bool exact) {\n        const int a = ensure_vertex(u), b = ensure_vertex(v);\n\
    \        splay(a);\n        splay(b);\n\n        // Rotate v's tour to start at\
    \ v, then splice it immediately after u.\n        int tour = b;\n        if (const\
    \ int prefix = nodes[b].child[0]) {\n            nodes[prefix].parent = 0;\n \
    \           nodes[b].child[0] = 0;\n            pull(b);\n            tour = join(b,\
    \ prefix);\n        }\n\n        int arc = free_arc;\n        if (arc) {\n   \
    \         free_arc = nodes[arc].parent;\n            nodes[arc] = Node{};\n  \
    \          nodes[arc + 1] = Node{};\n        } else {\n            arc = static_cast<int>(nodes.size());\n\
    \            nodes.resize(nodes.size() + 2);\n        }\n        const int reverse\
    \ = arc + 1;\n        const int suffix = nodes[a].child[1];\n        nodes[arc].item\
    \ = nodes[reverse].item = ~edge;\n        nodes[arc].extra = lower_arc;\n    \
    \    nodes[arc].marks = exact ? exact_edge : 0;\n        attach_child(arc, true,\
    \ tour);\n        attach_child(reverse, false, arc);\n        if (suffix) attach_child(reverse,\
    \ true, suffix);\n        attach_child(a, true, reverse);\n        pull(arc);\n\
    \        pull(reverse);\n        pull(a);\n        return arc;\n    }\n\n    //\
    \ Splits the tour at the two occurrences of an edge, then joins its outer pieces.\n\
    \    int cut(int arc) {\n        const int lower_arc = nodes[arc].extra;\n   \
    \     splay(arc);\n        const int left = nodes[arc].child[0], right = nodes[arc].child[1];\n\
    \        if (left) nodes[left].parent = 0;\n        if (right) nodes[right].parent\
    \ = 0;\n        const int reverse = arc + 1;\n        splay(reverse);\n      \
    \  const bool reverse_on_left = left && (left == reverse || nodes[left].parent);\n\
    \        const int before = nodes[reverse].child[0], after = nodes[reverse].child[1];\n\
    \        if (before) nodes[before].parent = 0;\n        if (after) nodes[after].parent\
    \ = 0;\n        if (reverse_on_left) join(before, right);\n        else join(left,\
    \ after);\n        nodes[arc].parent = free_arc;\n        free_arc = arc;\n  \
    \      return lower_arc;\n    }\n\n    int take_exact_edge(int v) {\n        const\
    \ int x = find_marked(v, exact_edge);\n        if (!x) return 0;\n        nodes[x].marks\
    \ = 0;\n        pull(x);\n        return ~nodes[x].item;\n    }\n\n    int incident_vertex(int\
    \ v) {\n        const int x = find_marked(v, incident_edge);\n        return x\
    \ ? nodes[x].item : -1;\n    }\n\n    int incidence_head(int v) const {\n    \
    \    return nodes[vertex(v)].extra;\n    }\n\n    void set_incidence_head(int\
    \ v, int head) {\n        const int x = head ? ensure_vertex(v) : vertex(v);\n\
    \        const bool changed = (nodes[x].extra == 0) != (head == 0);\n        nodes[x].extra\
    \ = head;\n        if (!changed) return;\n        splay(x);\n        nodes[x].marks\
    \ = head ? incident_edge : 0;\n        pull(x);\n    }\n\n    void update(int\
    \ v, const Value& delta) {\n        const int x = vertex(v);\n        splay(x);\n\
    \        values[v] = values[v] + delta;\n        pull(x);\n    }\n\n    Value\
    \ get_sum(int v) {\n        const int x = vertex(v);\n        splay(x);\n    \
    \    return nodes[x].sum;\n    }\n\n    std::vector<int> get_vertex(int v) {\n\
    \        const int x = vertex(v);\n        if (!x) return {v};\n        splay(x);\n\
    \        std::vector<int> result;\n        result.reserve(nodes[x].size);\n  \
    \      std::vector<int> stack{x};\n        while (!stack.empty()) {\n        \
    \    const int current = stack.back();\n            stack.pop_back();\n      \
    \      const Node& node = nodes[current];\n            if (node.item >= 0) result.push_back(node.item);\n\
    \            for (int child : node.child) {\n                if (child) stack.push_back(child);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n}\n#line 4 \"\
    graph/DynamicConnectivity.hpp\"\n\n#line 7 \"graph/DynamicConnectivity.hpp\"\n\
    #include <cstdint>\n#include <deque>\n#line 10 \"graph/DynamicConnectivity.hpp\"\
    \n#include <unordered_map>\n#include <utility>\n#line 13 \"graph/DynamicConnectivity.hpp\"\
    \n\nnamespace po167 {\n\n// Online connectivity for an undirected simple graph\
    \ with vertices [0, n).\n// Reference: https://qiita.com/hotman78/items/78cd3aa50b05a57738d4\n\
    // Expected amortized O(log n) for link and O(log^2 n) for cut.\n// Connectivity,\
    \ component size/sum and vertex updates take amortized O(log n).\n// Space: O(m\
    \ + n log n), where m is the maximum number of simultaneous edges.\n// For component\
    \ sums, T{} is zero and operator+ is associative and commutative.\ntemplate<class\
    \ T = void>\nclass DynamicConnectivity {\n    template<class U>\n    using Forest\
    \ = dynamic_connectivity_detail::EulerTourTree<U>;\n    using Value = std::conditional_t<std::is_void_v<T>,\
    \ dynamic_connectivity_detail::EmptyValue, T>;\n\n    struct Incidence {\n   \
    \     int prev = 0;\n        int next = 0;\n    };\n\n    struct Edge {\n    \
    \    int endpoint[2]{};\n        int level = 0;\n        int arc = 0; // Highest-level\
    \ tree arc, or zero for a non-tree edge.\n        Incidence incidence[2]{};\n\
    \    };\n\n    struct EdgeHash {\n        std::size_t operator()(std::uint64_t\
    \ key) const noexcept {\n            key = (key ^ (key >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \            key = (key ^ (key >> 27)) * 0x94d049bb133111ebULL;\n            return\
    \ static_cast<std::size_t>(key ^ (key >> 31));\n        }\n    };\n\n    int n;\n\
    \    Forest<T> base;\n    std::deque<Forest<void>> upper; // Appending a level\
    \ preserves references used by reconnect.\n    std::unordered_map<std::uint64_t,\
    \ int, EdgeHash> edge_id;\n    std::vector<Edge> edges{1};\n    int free_edge\
    \ = 0;\n\n    void check_vertex([[maybe_unused]] int v) const {\n        assert(0\
    \ <= v && v < n);\n    }\n\n    static std::uint64_t key(int u, int v) {\n   \
    \     if (u > v) std::swap(u, v);\n        return (static_cast<std::uint64_t>(u)\
    \ << 32) | static_cast<std::uint32_t>(v);\n    }\n\n    Forest<void>& next_forest(int\
    \ level) {\n        const int count = static_cast<int>(upper.size());\n      \
    \  assert(level <= count);\n        if (level == count) upper.emplace_back(n,\
    \ true);\n        return upper[level];\n    }\n\n    int make_edge(int u, int\
    \ v) {\n        const Edge edge{{u, v}};\n        int id = free_edge;\n      \
    \  if (id) {\n            free_edge = edges[id].endpoint[0];\n            edges[id]\
    \ = edge;\n        } else {\n            id = static_cast<int>(edges.size());\n\
    \            edges.push_back(edge);\n        }\n        return id;\n    }\n\n\
    \    Incidence& incidence(int handle) {\n        return edges[handle / 2].incidence[handle\
    \ % 2];\n    }\n\n    // Each non-tree edge has two doubly linked list entries,\
    \ one per endpoint.\n    template<class U>\n    void attach(Forest<U>& forest,\
    \ int id) {\n        Edge& edge = edges[id];\n        for (int side = 0; side\
    \ < 2; ++side) {\n            const int v = edge.endpoint[side];\n           \
    \ const int head = forest.incidence_head(v);\n            const int handle = 2\
    \ * id + side;\n            edge.incidence[side] = {0, head};\n            if\
    \ (head) incidence(head).prev = handle;\n            forest.set_incidence_head(v,\
    \ handle);\n        }\n    }\n\n    template<class U>\n    void detach(Forest<U>&\
    \ forest, int id) {\n        const Edge& edge = edges[id];\n        for (int side\
    \ = 0; side < 2; ++side) {\n            const auto [prev, next] = edge.incidence[side];\n\
    \            if (next) incidence(next).prev = prev;\n            if (prev) incidence(prev).next\
    \ = next;\n            else forest.set_incidence_head(edge.endpoint[side], next);\n\
    \        }\n    }\n\n    void link_tree(int id) {\n        Edge& edge = edges[id];\n\
    \        const auto [u, v] = edge.endpoint;\n        int arc = base.link(u, v,\
    \ id, 0, edge.level == 0);\n        for (int level = 1; level <= edge.level; ++level)\
    \ {\n            arc = upper[level - 1].link(u, v, id, arc, level == edge.level);\n\
    \        }\n        edge.arc = arc;\n    }\n\n    template<class U>\n    bool\
    \ reconnect(Forest<U>& forest, int u, int v, int level) {\n        if (forest.size(u)\
    \ > forest.size(v)) std::swap(u, v);\n        // The smaller tree fits at the\
    \ next level by the n / 2^level size invariant.\n        while (const int id =\
    \ forest.take_exact_edge(u)) {\n            Edge& edge = edges[id];\n        \
    \    const auto [a, b] = edge.endpoint;\n            edge.arc = next_forest(level).link(a,\
    \ b, id, edge.arc, true);\n            ++edge.level;\n        }\n        for (int\
    \ a = forest.incident_vertex(u); a != -1; a = forest.incident_vertex(u)) {\n \
    \           while (const int head = forest.incidence_head(a)) {\n            \
    \    const int id = head / 2;\n                Edge& edge = edges[id];\n     \
    \           const int b = edge.endpoint[1 - head % 2];\n                detach(forest,\
    \ id);\n                if (!forest.same(a, b)) {\n                    link_tree(id);\n\
    \                    return true;\n                }\n                ++edge.level;\n\
    \                attach(next_forest(level), id);\n            }\n        }\n \
    \       return false;\n    }\n\npublic:\n    explicit DynamicConnectivity(int\
    \ n) : n(n), base(n) {}\n\n    // Adds an edge and returns whether two components\
    \ merged. Duplicate edges and loops are ignored.\n    bool link(int u, int v)\
    \ {\n        check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ false;\n        const auto [entry, inserted] = edge_id.try_emplace(key(u, v),\
    \ 0);\n        if (!inserted) return false;\n        const int id = make_edge(u,\
    \ v);\n        entry->second = id;\n        if (base.same(u, v)) {\n         \
    \   attach(base, id);\n            return false;\n        }\n        link_tree(id);\n\
    \        return true;\n    }\n\n    // Removes an edge and returns whether a component\
    \ split. Missing edges are ignored.\n    bool cut(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v) return false;\n        const auto\
    \ entry = edge_id.find(key(u, v));\n        if (entry == edge_id.end()) return\
    \ false;\n        const int id = entry->second;\n        edge_id.erase(entry);\n\
    \        Edge& edge = edges[id];\n        int level = edge.level;\n        int\
    \ arc = edge.arc;\n        bool split = false;\n        if (arc) {\n         \
    \   for (int i = level; i > 0; --i) arc = upper[i - 1].cut(arc);\n           \
    \ base.cut(arc);\n            while (level > 0 && !reconnect(upper[level - 1],\
    \ u, v, level)) --level;\n            split = level == 0 && !reconnect(base, u,\
    \ v, 0);\n        } else if (level) {\n            detach(upper[level - 1], id);\n\
    \        } else {\n            detach(base, id);\n        }\n        edge.endpoint[0]\
    \ = free_edge;\n        free_edge = id;\n        return split;\n    }\n\n    bool\
    \ same(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n \
    \       return base.same(u, v);\n    }\n\n    int size(int v) {\n        check_vertex(v);\n\
    \        return base.size(v);\n    }\n\n    // Lists the component's vertices\
    \ in unspecified order in amortized O(log n + size(v)).\n    std::vector<int>\
    \ get_vertex(int v) {\n        check_vertex(v);\n        return base.get_vertex(v);\n\
    \    }\n\n    template<class U = T, std::enable_if_t<!std::is_void_v<U>, int>\
    \ = 0>\n    void update(int v, const Value& delta) {\n        check_vertex(v);\n\
    \        base.update(v, delta);\n    }\n\n    template<class U = T, std::enable_if_t<!std::is_void_v<U>,\
    \ int> = 0>\n    Value get_sum(int v) {\n        check_vertex(v);\n        return\
    \ base.get_sum(v);\n    }\n};\n\n}\n#line 4 \"test/graph/dynamic_connectivity_yukicoder.test.cpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#line 9 \"test/graph/dynamic_connectivity_yukicoder.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, m;\n    std::cin >> n >> m;\n    po167::DynamicConnectivity<long\
    \ long> graph(n);\n    std::vector<std::pair<int, int>> edges(m);\n    for (auto&\
    \ [u, v] : edges) {\n        std::cin >> u >> v;\n        --u;\n        --v;\n\
    \        graph.link(u, v);\n    }\n\n    // Deletions in distinct components commute.\
    \ In edge order, each new\n    // deletion is one round after the last deletion\
    \ in its component.\n    long long answer = 0;\n    for (auto [u, v] : edges)\
    \ {\n        // Store round * n + vertex at a single vertex of each component.\n\
    \        long long marker = graph.get_sum(u);\n        long long round = marker\
    \ / n + 1;\n        if (marker) graph.update(static_cast<int>(marker % n), -marker);\n\
    \        bool split = graph.cut(u, v);\n        graph.update(u, round * n + u);\n\
    \        if (split) graph.update(v, round * n + v);\n        answer = std::max(answer,\
    \ round);\n    }\n    std::cout << answer << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2072\"\n\n#include \"\
    graph/DynamicConnectivity.hpp\"\n\n#include <algorithm>\n#include <iostream>\n\
    #include <utility>\n#include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, m;\n    std::cin >> n >> m;\n    po167::DynamicConnectivity<long\
    \ long> graph(n);\n    std::vector<std::pair<int, int>> edges(m);\n    for (auto&\
    \ [u, v] : edges) {\n        std::cin >> u >> v;\n        --u;\n        --v;\n\
    \        graph.link(u, v);\n    }\n\n    // Deletions in distinct components commute.\
    \ In edge order, each new\n    // deletion is one round after the last deletion\
    \ in its component.\n    long long answer = 0;\n    for (auto [u, v] : edges)\
    \ {\n        // Store round * n + vertex at a single vertex of each component.\n\
    \        long long marker = graph.get_sum(u);\n        long long round = marker\
    \ / n + 1;\n        if (marker) graph.update(static_cast<int>(marker % n), -marker);\n\
    \        bool split = graph.cut(u, v);\n        graph.update(u, round * n + u);\n\
    \        if (split) graph.update(v, round * n + v);\n        answer = std::max(answer,\
    \ round);\n    }\n    std::cout << answer << '\\n';\n}\n"
  dependsOn:
  - graph/DynamicConnectivity.hpp
  - graph/tree/EulerTourTree.hpp
  isVerificationFile: true
  path: test/graph/dynamic_connectivity_yukicoder.test.cpp
  requiredBy: []
  timestamp: '2026-11-21 02:49:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/dynamic_connectivity_yukicoder.test.cpp
layout: document
redirect_from:
- /verify/test/graph/dynamic_connectivity_yukicoder.test.cpp
- /verify/test/graph/dynamic_connectivity_yukicoder.test.cpp.html
title: test/graph/dynamic_connectivity_yukicoder.test.cpp
---
