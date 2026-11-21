---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/DynamicConnectivity.hpp
    title: "\u30AA\u30F3\u30E9\u30A4\u30F3\u52D5\u7684\u9023\u7D50\u6027"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/dynamic_connectivity_aoj.test.cpp
    title: test/graph/dynamic_connectivity_aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/dynamic_connectivity_yosupo.test.cpp
    title: test/graph/dynamic_connectivity_yosupo.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/dynamic_connectivity_yukicoder.test.cpp
    title: test/graph/dynamic_connectivity_yukicoder.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/tree/EulerTourTree.hpp\"\n\n#include <cassert>\n#include\
    \ <cstddef>\n#include <type_traits>\n#include <vector>\n\nnamespace po167::dynamic_connectivity_detail\
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
    \            }\n        }\n        return result;\n    }\n};\n\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cstddef>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace po167::dynamic_connectivity_detail {\n\nstruct\
    \ EmptyValue {};\n\ntemplate<class T>\nstruct EulerTourAggregate {\n    T sum{};\n\
    };\n\ntemplate<>\nstruct EulerTourAggregate<void> {};\n\n// Splay forest with\
    \ one occurrence of each vertex and two of each tree edge.\n// The dynamic connectivity\
    \ levels use the marks to locate edges for promotion.\ntemplate<class T>\nclass\
    \ EulerTourTree {\n    using Value = std::conditional_t<std::is_void_v<T>, EmptyValue,\
    \ T>;\n    static constexpr unsigned char exact_edge = 1;\n    static constexpr\
    \ unsigned char incident_edge = 2;\n\n    struct Node : EulerTourAggregate<T>\
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
    \            }\n        }\n        return result;\n    }\n};\n\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/tree/EulerTourTree.hpp
  requiredBy:
  - graph/DynamicConnectivity.hpp
  timestamp: '2026-11-21 02:49:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/dynamic_connectivity_yosupo.test.cpp
  - test/graph/dynamic_connectivity_aoj.test.cpp
  - test/graph/dynamic_connectivity_yukicoder.test.cpp
documentation_of: graph/tree/EulerTourTree.hpp
layout: document
redirect_from:
- /library/graph/tree/EulerTourTree.hpp
- /library/graph/tree/EulerTourTree.hpp.html
title: graph/tree/EulerTourTree.hpp
---
