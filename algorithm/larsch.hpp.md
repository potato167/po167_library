---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/monge_d_edge_shortest_path.hpp
    title: algorithm/monge_d_edge_shortest_path.hpp
  - icon: ':heavy_check_mark:'
    path: algorithm/monge_shortest_path.hpp
    title: algorithm/monge_shortest_path.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/algorithm/monge_1.test.cpp
    title: test/algorithm/monge_1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/algorithm/monge_3.test.cpp
    title: test/algorithm/monge_3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.github.io/Library/algorithm/larsch.cpp.html
  bundledCode: "#line 2 \"algorithm/larsch.hpp\"\n// po167 Monge library v2 (2026-10-21)\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\nnamespace po167 {\n\
    namespace detail {\n\n// A[r][c] = value(r,c), 0 <= c <= r < n: Monge.\n// r-th\
    \ next_argmin() = min argmin_{0 <= c <= r} A[r][c].\n// O(n) total time, O(n)\
    \ space.\n// https://noshi91.github.io/Library/algorithm/larsch.cpp.html (CC0)\n\
    template <class F>\nclass Larsch {\n    struct Level {\n        int n, row = 0,\
    \ state = 0, size = 0;\n        std::vector<int> column;\n        Level(int n_,\
    \ bool base) : n(n_), column(base ? 0 : n_) {}\n    };\n    F value;\n    std::vector<Level>\
    \ levels;\n\n    int next_argmin(int depth) {\n        auto& a = levels[depth];\n\
    \        int row = a.row++, r = ((row + 1) << depth) - 1;\n        auto column\
    \ = [&](int j) { return depth ? a.column[j] : j; };\n        int best = column(a.state);\n\
    \        if (row & 1) {\n            int last = column(row);\n            return\
    \ value(r, last) < value(r, best) ? last : best;\n        }\n        int bound;\n\
    \        if (row + 1 == a.n) {\n            bound = column(a.n - 1);\n       \
    \ } else {\n            auto& b = levels[depth + 1];\n            for (int j =\
    \ (row ? row - 1 : 0); j <= row; ++j) {\n                int c = column(j);\n\
    \                while (b.size > row / 2) {\n                    int q = (b.size\
    \ << (depth + 1)) - 1;\n                    if (!(value(q, c) < value(q, b.column[b.size\
    \ - 1]))) break;\n                    --b.size;\n                }\n         \
    \       if (b.size < b.n) b.column[b.size++] = c;\n            }\n           \
    \ bound = next_argmin(depth + 1);\n        }\n        if (best != bound) {\n \
    \           auto best_value = value(r, best);\n            do {\n            \
    \    int c = column(++a.state);\n                auto candidate = value(r, c);\n\
    \                if (candidate < best_value) best_value = candidate, best = c;\n\
    \            } while (column(a.state) != bound);\n        }\n        return best;\n\
    \    }\n\npublic:\n    // A[r][c] = value_(r,c), 0 <= c <= r < n; next row = 0.\n\
    \    Larsch(int n, F value_) : value(std::move(value_)) {\n        assert(n >=\
    \ 0);\n        for (int size = n; size; size /= 2) levels.emplace_back(size, levels.empty());\n\
    \    }\n\n    // return min argmin_{0 <= c <= r} A[r][c], then r <- r+1.\n   \
    \ int next_argmin() {\n        assert(!levels.empty() && levels[0].row < levels[0].n);\n\
    \        return next_argmin(0);\n    }\n\n    // r <- 0; A may be changed before\
    \ the next sequence of queries.\n    void reset() {\n        for (auto& a : levels)\
    \ a.row = a.state = a.size = 0;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ po167\n"
  code: "#pragma once\n// po167 Monge library v2 (2026-10-21)\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\nnamespace po167 {\nnamespace detail {\n\
    \n// A[r][c] = value(r,c), 0 <= c <= r < n: Monge.\n// r-th next_argmin() = min\
    \ argmin_{0 <= c <= r} A[r][c].\n// O(n) total time, O(n) space.\n// https://noshi91.github.io/Library/algorithm/larsch.cpp.html\
    \ (CC0)\ntemplate <class F>\nclass Larsch {\n    struct Level {\n        int n,\
    \ row = 0, state = 0, size = 0;\n        std::vector<int> column;\n        Level(int\
    \ n_, bool base) : n(n_), column(base ? 0 : n_) {}\n    };\n    F value;\n   \
    \ std::vector<Level> levels;\n\n    int next_argmin(int depth) {\n        auto&\
    \ a = levels[depth];\n        int row = a.row++, r = ((row + 1) << depth) - 1;\n\
    \        auto column = [&](int j) { return depth ? a.column[j] : j; };\n     \
    \   int best = column(a.state);\n        if (row & 1) {\n            int last\
    \ = column(row);\n            return value(r, last) < value(r, best) ? last :\
    \ best;\n        }\n        int bound;\n        if (row + 1 == a.n) {\n      \
    \      bound = column(a.n - 1);\n        } else {\n            auto& b = levels[depth\
    \ + 1];\n            for (int j = (row ? row - 1 : 0); j <= row; ++j) {\n    \
    \            int c = column(j);\n                while (b.size > row / 2) {\n\
    \                    int q = (b.size << (depth + 1)) - 1;\n                  \
    \  if (!(value(q, c) < value(q, b.column[b.size - 1]))) break;\n             \
    \       --b.size;\n                }\n                if (b.size < b.n) b.column[b.size++]\
    \ = c;\n            }\n            bound = next_argmin(depth + 1);\n        }\n\
    \        if (best != bound) {\n            auto best_value = value(r, best);\n\
    \            do {\n                int c = column(++a.state);\n              \
    \  auto candidate = value(r, c);\n                if (candidate < best_value)\
    \ best_value = candidate, best = c;\n            } while (column(a.state) != bound);\n\
    \        }\n        return best;\n    }\n\npublic:\n    // A[r][c] = value_(r,c),\
    \ 0 <= c <= r < n; next row = 0.\n    Larsch(int n, F value_) : value(std::move(value_))\
    \ {\n        assert(n >= 0);\n        for (int size = n; size; size /= 2) levels.emplace_back(size,\
    \ levels.empty());\n    }\n\n    // return min argmin_{0 <= c <= r} A[r][c], then\
    \ r <- r+1.\n    int next_argmin() {\n        assert(!levels.empty() && levels[0].row\
    \ < levels[0].n);\n        return next_argmin(0);\n    }\n\n    // r <- 0; A may\
    \ be changed before the next sequence of queries.\n    void reset() {\n      \
    \  for (auto& a : levels) a.row = a.state = a.size = 0;\n    }\n};\n\n}  // namespace\
    \ detail\n}  // namespace po167\n"
  dependsOn: []
  isVerificationFile: false
  path: algorithm/larsch.hpp
  requiredBy:
  - algorithm/monge_d_edge_shortest_path.hpp
  - algorithm/monge_shortest_path.hpp
  timestamp: '2026-10-21 23:29:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/algorithm/monge_3.test.cpp
  - test/algorithm/monge_1.test.cpp
documentation_of: algorithm/larsch.hpp
layout: document
redirect_from:
- /library/algorithm/larsch.hpp
- /library/algorithm/larsch.hpp.html
title: algorithm/larsch.hpp
---
