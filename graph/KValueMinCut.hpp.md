---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: test/graph/k_value_min_cut_unit.cpp
    title: test/graph/k_value_min_cut_unit.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/k_value_min_cut_aoj_board.test.cpp
    title: test/graph/k_value_min_cut_aoj_board.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/k_value_min_cut_yukicoder.test.cpp
    title: test/graph/k_value_min_cut_yukicoder.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/KValueMinCut.hpp\"\n#include <atcoder/maxflow>\n#include\
    \ <vector>\n#include <tuple>\n#include <utility>\n#include <cassert>\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace po167 {\n\ntemplate<class T =\
    \ long long>\nstruct KValueMinCut {\n    static_assert(std::is_integral_v<T> &&\
    \ std::is_signed_v<T>);\n\n    int n, s, t;\n    std::vector<int> R, base;\n \
    \   std::vector<T> linear;\n    std::vector<std::tuple<int, int, T>> edges;\n\
    \    T constant = 0;\n\n    explicit KValueMinCut(const std::vector<int>& r)\n\
    \        : n(r.size()), R(r), base(n) {\n        int m = 0;\n        for (int\
    \ i = 0; i < n; i++) {\n            assert(R[i] >= 1);\n            base[i] =\
    \ m;\n            m += R[i] - 1;\n        }\n        s = m;\n        t = m + 1;\n\
    \        linear.resize(m + 2);\n    }\n\n    // x(i,a) = [v[i] >= a]\n    int\
    \ node(int i, int a) const {\n        assert(0 <= i && i < n);\n        assert(0\
    \ <= a && a <= R[i]);\n        if (a == 0) return s;\n        if (a == R[i]) return\
    \ t;\n        return base[i] + a - 1;\n    }\n\n    // c * x(i,a)\n    void add_linear(int\
    \ i, int a, T c) {\n        linear[node(i, a)] += c;\n    }\n\n    // c * [u is\
    \ S-side and v is T-side]\n    void add_edge(int u, int v, T c) {\n        assert(c\
    \ >= 0);\n        if (c == 0 || u == v || u == t || v == s) return;\n        if\
    \ (u == s && v == t) constant += c;\n        else edges.emplace_back(u, v, c);\n\
    \    }\n\n    // +c if v[i] == k\n    void add_eq(int i, int k, T c) {\n     \
    \   assert(0 <= k && k < R[i]);\n        add_linear(i, k, c);\n        add_linear(i,\
    \ k + 1, -c);\n    }\n\n    // +c if v[i] < a && v[j] >= b\n    void add_lt_ge(int\
    \ i, int a, int j, int b, T c) {\n        add_edge(node(j, b), node(i, a), c);\n\
    \    }\n\n    // -c if v[i] < a && v[j] < b\n    void add_lt_lt(int i, int a,\
    \ int j, int b, T c) {\n        assert(c >= 0);\n        constant -= c;\n    \
    \    add_linear(i, a, c);\n        add_lt_ge(i, a, j, b, c);\n    }\n\n    //\
    \ -c if v[i] < a for every (i, a) in conditions\n    void add_lt_lt(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        constant -= c;\n        if (conditions.empty()) return;\n        int\
    \ u = int(linear.size());\n        linear.push_back(c);\n        for (auto [i,\
    \ a] : conditions) {\n            add_edge(node(i, a), u, c);\n        }\n   \
    \ }\n\n    // -c if v[i] >= a && v[j] >= b\n    void add_ge_ge(int i, int a, int\
    \ j, int b, T c) {\n        assert(c >= 0);\n        add_linear(i, a, -c);\n \
    \       add_edge(node(i, a), node(j, b), c);\n    }\n\n    // -c if v[i] >= a\
    \ for every (i, a) in conditions\n    void add_ge_ge(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        if (conditions.empty()) {\n            constant -= c;\n            return;\n\
    \        }\n        int u = int(linear.size());\n        linear.push_back(-c);\n\
    \        for (auto [i, a] : conditions) {\n            add_edge(u, node(i, a),\
    \ c);\n        }\n    }\n\n    // +c if [v[i] >= a] != [v[j] >= b]\n    void add_diff(int\
    \ i, int a, int j, int b, T c) {\n        add_lt_ge(i, a, j, b, c);\n        add_lt_ge(j,\
    \ b, i, a, c);\n    }\n\n    // return {minimum cost, optimal v}\n    std::pair<T,\
    \ std::vector<int>> run() const {\n        int vertices = int(linear.size());\n\
    \        T sum = 0;\n        auto add_sum = [&](T c) {\n            assert(c >=\
    \ 0 && c < std::numeric_limits<T>::max() - sum);\n            sum += c;\n    \
    \    };\n\n        for (auto [u, v, c] : edges) add_sum(c);\n        for (int\
    \ u = 0; u < vertices; u++) {\n            if (u == s || u == t) continue;\n \
    \           assert(linear[u] != std::numeric_limits<T>::min());\n            add_sum(linear[u]\
    \ < 0 ? -linear[u] : linear[u]);\n        }\n\n        atcoder::mf_graph<T> graph(vertices);\n\
    \        for (auto [u, v, c] : edges) graph.add_edge(u, v, c);\n\n        T ans\
    \ = constant + linear[s];\n        for (int u = 0; u < vertices; u++) {\n    \
    \        if (u == s || u == t) continue;\n            if (linear[u] > 0) {\n \
    \               graph.add_edge(u, t, linear[u]);\n            } else if (linear[u]\
    \ < 0) {\n                graph.add_edge(s, u, -linear[u]);\n                ans\
    \ += linear[u];\n            }\n        }\n\n        T inf = sum + 1;\n      \
    \  for (int i = 0; i < n; i++) {\n            for (int a = 1; a + 1 < R[i]; a++)\
    \ {\n                graph.add_edge(node(i, a + 1), node(i, a), inf);\n      \
    \      }\n        }\n\n        ans += graph.flow(s, t);\n        auto side = graph.min_cut(s);\n\
    \n        std::vector<int> v(n);\n        for (int i = 0; i < n; i++) {\n    \
    \        for (int a = 1; a < R[i]; a++) {\n                if (side[node(i, a)])\
    \ v[i] = a;\n            }\n        }\n        return {ans, v};\n    }\n};\n\n\
    }\n"
  code: "#pragma once\n#include <atcoder/maxflow>\n#include <vector>\n#include <tuple>\n\
    #include <utility>\n#include <cassert>\n#include <limits>\n#include <type_traits>\n\
    \nnamespace po167 {\n\ntemplate<class T = long long>\nstruct KValueMinCut {\n\
    \    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);\n\n    int n,\
    \ s, t;\n    std::vector<int> R, base;\n    std::vector<T> linear;\n    std::vector<std::tuple<int,\
    \ int, T>> edges;\n    T constant = 0;\n\n    explicit KValueMinCut(const std::vector<int>&\
    \ r)\n        : n(r.size()), R(r), base(n) {\n        int m = 0;\n        for\
    \ (int i = 0; i < n; i++) {\n            assert(R[i] >= 1);\n            base[i]\
    \ = m;\n            m += R[i] - 1;\n        }\n        s = m;\n        t = m +\
    \ 1;\n        linear.resize(m + 2);\n    }\n\n    // x(i,a) = [v[i] >= a]\n  \
    \  int node(int i, int a) const {\n        assert(0 <= i && i < n);\n        assert(0\
    \ <= a && a <= R[i]);\n        if (a == 0) return s;\n        if (a == R[i]) return\
    \ t;\n        return base[i] + a - 1;\n    }\n\n    // c * x(i,a)\n    void add_linear(int\
    \ i, int a, T c) {\n        linear[node(i, a)] += c;\n    }\n\n    // c * [u is\
    \ S-side and v is T-side]\n    void add_edge(int u, int v, T c) {\n        assert(c\
    \ >= 0);\n        if (c == 0 || u == v || u == t || v == s) return;\n        if\
    \ (u == s && v == t) constant += c;\n        else edges.emplace_back(u, v, c);\n\
    \    }\n\n    // +c if v[i] == k\n    void add_eq(int i, int k, T c) {\n     \
    \   assert(0 <= k && k < R[i]);\n        add_linear(i, k, c);\n        add_linear(i,\
    \ k + 1, -c);\n    }\n\n    // +c if v[i] < a && v[j] >= b\n    void add_lt_ge(int\
    \ i, int a, int j, int b, T c) {\n        add_edge(node(j, b), node(i, a), c);\n\
    \    }\n\n    // -c if v[i] < a && v[j] < b\n    void add_lt_lt(int i, int a,\
    \ int j, int b, T c) {\n        assert(c >= 0);\n        constant -= c;\n    \
    \    add_linear(i, a, c);\n        add_lt_ge(i, a, j, b, c);\n    }\n\n    //\
    \ -c if v[i] < a for every (i, a) in conditions\n    void add_lt_lt(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        constant -= c;\n        if (conditions.empty()) return;\n        int\
    \ u = int(linear.size());\n        linear.push_back(c);\n        for (auto [i,\
    \ a] : conditions) {\n            add_edge(node(i, a), u, c);\n        }\n   \
    \ }\n\n    // -c if v[i] >= a && v[j] >= b\n    void add_ge_ge(int i, int a, int\
    \ j, int b, T c) {\n        assert(c >= 0);\n        add_linear(i, a, -c);\n \
    \       add_edge(node(i, a), node(j, b), c);\n    }\n\n    // -c if v[i] >= a\
    \ for every (i, a) in conditions\n    void add_ge_ge(const std::vector<std::pair<int,\
    \ int>>& conditions, T c) {\n        assert(c >= 0);\n        if (c == 0) return;\n\
    \        if (conditions.empty()) {\n            constant -= c;\n            return;\n\
    \        }\n        int u = int(linear.size());\n        linear.push_back(-c);\n\
    \        for (auto [i, a] : conditions) {\n            add_edge(u, node(i, a),\
    \ c);\n        }\n    }\n\n    // +c if [v[i] >= a] != [v[j] >= b]\n    void add_diff(int\
    \ i, int a, int j, int b, T c) {\n        add_lt_ge(i, a, j, b, c);\n        add_lt_ge(j,\
    \ b, i, a, c);\n    }\n\n    // return {minimum cost, optimal v}\n    std::pair<T,\
    \ std::vector<int>> run() const {\n        int vertices = int(linear.size());\n\
    \        T sum = 0;\n        auto add_sum = [&](T c) {\n            assert(c >=\
    \ 0 && c < std::numeric_limits<T>::max() - sum);\n            sum += c;\n    \
    \    };\n\n        for (auto [u, v, c] : edges) add_sum(c);\n        for (int\
    \ u = 0; u < vertices; u++) {\n            if (u == s || u == t) continue;\n \
    \           assert(linear[u] != std::numeric_limits<T>::min());\n            add_sum(linear[u]\
    \ < 0 ? -linear[u] : linear[u]);\n        }\n\n        atcoder::mf_graph<T> graph(vertices);\n\
    \        for (auto [u, v, c] : edges) graph.add_edge(u, v, c);\n\n        T ans\
    \ = constant + linear[s];\n        for (int u = 0; u < vertices; u++) {\n    \
    \        if (u == s || u == t) continue;\n            if (linear[u] > 0) {\n \
    \               graph.add_edge(u, t, linear[u]);\n            } else if (linear[u]\
    \ < 0) {\n                graph.add_edge(s, u, -linear[u]);\n                ans\
    \ += linear[u];\n            }\n        }\n\n        T inf = sum + 1;\n      \
    \  for (int i = 0; i < n; i++) {\n            for (int a = 1; a + 1 < R[i]; a++)\
    \ {\n                graph.add_edge(node(i, a + 1), node(i, a), inf);\n      \
    \      }\n        }\n\n        ans += graph.flow(s, t);\n        auto side = graph.min_cut(s);\n\
    \n        std::vector<int> v(n);\n        for (int i = 0; i < n; i++) {\n    \
    \        for (int a = 1; a < R[i]; a++) {\n                if (side[node(i, a)])\
    \ v[i] = a;\n            }\n        }\n        return {ans, v};\n    }\n};\n\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/KValueMinCut.hpp
  requiredBy:
  - test/graph/k_value_min_cut_unit.cpp
  timestamp: '2026-11-21 02:09:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/k_value_min_cut_aoj_board.test.cpp
  - test/graph/k_value_min_cut_yukicoder.test.cpp
documentation_of: graph/KValueMinCut.hpp
layout: document
title: "k \u5024\u71C3\u3084\u3059\u57CB\u3081\u308B"
---

## 概要

整数変数 $v_i\in\{0,1,\ldots,R_i-1\}$ に対するコストの和を、最小カットに帰着して最小化する。
変数ごとに値の種類数 $R_i$ を変えられ、すべて $R_i=2$ とすれば通常の二値の燃やす埋めるとして使える。

以下では $[P]$ を、条件 $P$ が真なら $1$、偽なら $0$ とする。
各関数で追加したコストは加算される。負のコストは利益を表す。
内部では $x(i,a)=[v_i\ge a]$ をカットの頂点で表し、$x(i,a)=1$ を S 側、$0$ を T 側に対応させる。

`<atcoder/maxflow>` が必要。C++17 以降で使用する。

## 構築

```cpp
po167::KValueMinCut<long long> cut(R);
```

`R` は `std::vector<int>`。`R.size()` 個の変数を用意し、すべての $R_i\ge1$ が必要。
変数の添字は $0$ 始まり。$R_i=1$ の変数は常に $0$ になる。

テンプレート引数 `T` は符号付き整数型で、既定値は `long long`。
頂点番号と頂点数は `int` に収まる必要がある。

## 関数

以下の `i`, `j` は存在する変数の添字、しきい値 `a`, `b` はそれぞれ
$0\le a\le R_i$, $0\le b\le R_j$ とする。
特に $x(i,0)=1$、$x(i,R_i)=0$ なので、端のしきい値を使って定数項や単項コストも表現できる。

### `node(i, a)`

```cpp
int u = cut.node(i, a);
```

$x(i,a)$ に対応する頂点番号を返す。
`a == 0` なら始点 `cut.s`、`a == R[i]` なら終点 `cut.t`、それ以外なら通常の頂点になる。
主に `add_edge` の引数を作るために使う。
複数条件のコストを追加して補助頂点が増えても、`node` の返り値と `cut.s`, `cut.t` の番号は変わらない。

### `add_linear(i, a, c)`

```cpp
cut.add_linear(i, a, c);
```

$c[v_i\ge a]$ を追加する。`c` は負でもよい。
`a == 0` なら定数 $c$ を追加し、`a == R[i]` ならコストに影響しない。

### `add_edge(u, v, c)`

```cpp
cut.add_edge(cut.node(i, a), cut.node(j, b), c);
```

頂点 `u` が S 側、`v` が T 側のときだけ $c$ を追加する。$c\ge0$ が必要。
上の例では $c[v_i\ge a\land v_j<b]$ になる。
`u`, `v` には `node` の返り値、`cut.s`、`cut.t` を渡す。

`u == cut.s && v == cut.t` なら定数項になる。
`c == 0`、`u == v`、`u == cut.t`、`v == cut.s` のいずれかなら何も追加しない。

### `add_eq(i, k, c)`

```cpp
cut.add_eq(i, k, c);
```

$c[v_i=k]$ を追加する。$0\le k<R_i$ が必要。`c` は負でもよい。
各 $k$ に対して呼ぶことで、任意の単項コスト $f_i(v_i)$ を追加できる。

### `add_lt_ge(i, a, j, b, c)`

```cpp
cut.add_lt_ge(i, a, j, b, c);
```

$c[v_i<a\land v_j\ge b]$ を追加する。$c\ge0$ が必要。
2 つの条件を同時に満たすときの罰金を表す。

### `add_lt_lt(i, a, j, b, c)`

```cpp
cut.add_lt_lt(i, a, j, b, c);
```

$-c[v_i<a\land v_j<b]$ を追加する。$c\ge0$ が必要。
2 つの条件を同時に満たすときに利益 $c$ を得る。

### `add_ge_ge(i, a, j, b, c)`

```cpp
cut.add_ge_ge(i, a, j, b, c);
```

$-c[v_i\ge a\land v_j\ge b]$ を追加する。$c\ge0$ が必要。
2 つの条件を同時に満たすときに利益 $c$ を得る。

### `add_lt_lt(conditions, c)`

```cpp
void add_lt_lt(const std::vector<std::pair<int, int>>& conditions, T c);
```

`conditions` の各要素 `(i, a)` を条件 $v_i<a$ として、すべての条件を満たすときにだけ $-c$ を追加する。
$c\ge0$ が必要。各要素の添字としきい値には、2 条件版と同じ範囲を指定する。

空のリストでは条件が常に成立するため、定数 $-c$ を追加する。
条件の重複、同じ変数に対する複数の条件、端のしきい値も指定できる。
リストが空でなく $c>0$ なら、内部で補助頂点を 1 個追加する。

### `add_ge_ge(conditions, c)`

```cpp
void add_ge_ge(const std::vector<std::pair<int, int>>& conditions, T c);
```

`conditions` の各要素 `(i, a)` を条件 $v_i\ge a$ として、すべての条件を満たすときにだけ $-c$ を追加する。
$c\ge0$ が必要。各要素の添字としきい値には、2 条件版と同じ範囲を指定する。

空のリストでは定数 $-c$ を追加する。
条件の重複、同じ変数に対する複数の条件、端のしきい値も指定できる。
リストが空でなく $c>0$ なら、内部で補助頂点を 1 個追加する。

### `add_diff(i, a, j, b, c)`

```cpp
cut.add_diff(i, a, j, b, c);
```

$c\bigl[[v_i\ge a]\ne[v_j\ge b]\bigr]$ を追加する。$c\ge0$ が必要。
2 つのしきい値判定が異なるときの罰金を表す。
同じ値域の変数では、すべての $a=1,\ldots,R_i-1$ に対して
`add_diff(i, a, j, a, c)` を呼ぶと $c|v_i-v_j|$ を追加できる。

### `run()`

```cpp
auto [minimum_cost, values] = cut.run();
```

追加したコストの総和を最小化し、`std::pair<T, std::vector<int>>` を返す。
`minimum_cost` は定数項を含む最小値、`values[i]` はそれを達成する $v_i$。
最適解が複数ある場合は、そのうちの 1 つを返す。
`values` の要素数は元の変数の数 `R.size()` で、補助頂点の値は含まない。

`run()` はオブジェクトを変更しないため、繰り返し呼べる。
コストを追加してから再実行することもできるが、毎回グラフを作り直して最大流を計算する。

## 使用例

2 変数 $u,v\in\{0,1,2\}$ について、

$$
f(u)+g(v)+2|u-v|,
\qquad f=(5,1,0),\quad g=(0,4,8)
$$

を最小化する。

```cpp
#include "graph/KValueMinCut.hpp"
#include <iostream>

int main() {
    po167::KValueMinCut<> cut({3, 3});
    const long long f[] = {5, 1, 0};
    const long long g[] = {0, 4, 8};
    for (int k = 0; k < 3; k++) {
        cut.add_eq(0, k, f[k]);
        cut.add_eq(1, k, g[k]);
    }
    for (int a = 1; a < 3; a++) {
        cut.add_diff(0, a, 1, a, 2);
    }
    auto [cost, values] = cut.run();
    std::cout << cost << '\n';                       // 3
    std::cout << values[0] << ' ' << values[1] << '\n'; // 1 0
}
```

利益の最大化では、利益を負のコストとして追加し、`-cost` を答えにする。

3 個以上の条件をまとめる場合は、条件のリストを渡す。

```cpp
po167::KValueMinCut<> cut({3, 4, 2});
// v[0] < 2, v[1] < 3, v[2] < 1 がすべて成立すると利益 7。
cut.add_lt_lt({{0, 2}, {1, 3}, {2, 1}}, 7);
// v[0] >= 1, v[1] >= 2, v[2] >= 1 がすべて成立すると利益 5。
cut.add_ge_ge({{0, 1}, {1, 2}, {2, 1}}, 5);
// 空の条件リストは常に成立するので、定数 -2 を追加。
cut.add_lt_lt({}, 2);
auto [cost, values] = cut.run(); // cost = -9、values は 3 要素。
```

## 整数の範囲

すべてのコストの加減算・蓄積と答えが `T` に収まるようにする。
特に `add_eq` は `-c` を計算するため、`c` に `std::numeric_limits<T>::min()` を渡せない。

`run()` は、保存した辺の容量の和と、始点・終点を除く各頂点（補助頂点を含む）に蓄積した線形係数の絶対値の和を `sum` として、
単調性 $x(i,a+1)\le x(i,a)$ を強制する辺に容量 `sum + 1` を設定する。
したがって `sum < std::numeric_limits<T>::max()` が必要であり、各線形係数の絶対値も `T` に収まる必要がある。
定数項や、負の線形係数を答えに加える途中の値についても、別途オーバーフローしないことが必要。

## 計算量

$L=\sum_i(R_i-1)$、補助頂点の数を $A$、保存した辺の数を $M$ とする。
構築は時間・空間ともに $O(n+L)$。`node` は $O(1)$。
`conditions` を取る 2 つの関数は、リストの要素数 $k>0$ に対して償却 $O(k)$、空なら $O(1)$。
それ以外のコスト追加関数は償却 $O(1)$。

`run()` が作るグラフの頂点数は $V=L+A+2$、辺数は $E=O(M+L+A)$。
一般の整数容量に対する最大流の計算量に従い、時間 $O(V^2E+V+n)$、追加空間 $O(V+E+n)$。
値域が大きいと、変数の数だけでなく $L$ に比例してグラフが大きくなる。
