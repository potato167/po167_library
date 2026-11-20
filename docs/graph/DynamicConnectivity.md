---
title: オンライン動的連結性
documentation_of: //graph/DynamicConnectivity.hpp
---

## 概要

無向グラフに対して、辺の追加・削除、連結判定、連結成分のサイズや頂点の取得を行う。
クエリは到着順に処理できる。C++17 以降で使用する。

## 構築

```cpp
#include "graph/DynamicConnectivity.hpp"

po167::DynamicConnectivity<> graph(n);
po167::DynamicConnectivity<long long> weighted(n);
```

頂点番号は $0$ から $n-1$。初期状態は $n$ 個の孤立頂点で、辺は空。
頂点加算と成分和を使う場合は、テンプレート引数に頂点値の型 `T` を指定する。
全頂点の初期値は `T{}`。`T{}` が `operator+` の単位元で、加算が結合律と交換律を満たすことが必要。
整数型では、頂点値や途中の部分和も型の範囲に収まるようにする。

## 操作

| 操作 | 動作・返り値 | 償却計算量 |
|---|---|---|
| `link(u, v)` | 無向辺を追加し、2 つの連結成分が結合したとき `true` を返す | 期待 $O(\log n)$ |
| `cut(u, v)` | 無向辺を削除し、連結成分が分離したとき `true` を返す | 期待 $O(\log^2 n)$ |
| `same(u, v)` | 2 頂点が同じ連結成分に属するとき `true` を返す | $O(\log n)$ |
| `size(v)` | `v` の連結成分の頂点数を `int` で返す | $O(\log n)$ |
| `get_vertex(v)` | `v` の連結成分の頂点を `std::vector<int>` で返す。並び順は未規定 | $O(\log n+k)$ |
| `update(v, delta)` | 頂点 `v` の値に `delta` を加える | $O(\log n)$ |
| `get_sum(v)` | `v` の連結成分の頂点値の和を `T` で返す | $O(\log n)$ |

$k$ は取得する成分の頂点数。構築は $O(n)$、空間は $O(m+n\log n)$。$m$ は同時に存在した辺数の最大値とする。
`update` と `get_sum` は、`T` に頂点値の型を指定したときに使える。計算量は `T` の加算とコピーを $O(1)$ としている。

辺の両端の順序は自由。自己ループの追加・削除、同じ辺の重複追加、存在しない辺の削除はいずれも無操作で `false` を返す。
閉路を作る辺を追加したときと、別経路が残る辺を削除したときも `false` が返る。この場合は辺の集合が更新される。

## 使用例

三角形を作り、辺を 1 本ずつ削除して連結性と成分和を確認する。

```cpp
#include "graph/DynamicConnectivity.hpp"
#include <iostream>

int main() {
    po167::DynamicConnectivity<long long> graph(3);
    graph.link(0, 1);
    graph.link(1, 2);
    std::cout << std::boolalpha;
    std::cout << graph.link(0, 2) << '\n';  // false。辺 (0, 2) は追加される。

    graph.update(0, 5);
    graph.update(2, 7);
    std::cout << graph.get_sum(1) << '\n';  // 12

    std::cout << graph.cut(1, 0) << '\n';  // false。0 と 1 は頂点 2 を経由してつながる。
    std::cout << graph.cut(2, 0) << '\n';  // true。頂点 0 が孤立する。
    std::cout << graph.same(0, 2) << '\n'; // false
    std::cout << graph.size(1) << '\n';    // 2
    std::cout << graph.get_sum(1) << '\n'; // 7
}
```
