---
title: 乗法的関数の累積和
documentation_of: //math/multiplicative_prefix_sum.hpp
---

## 概要

乗法的関数 $f$（$f(1)=1$）について、

$$
F(N)=\sum_{n=1}^{N}f(n)
$$

を求める。

次の2つを用意し、`sum` に渡す。

- 素数だけの累積和 $P(x)=\sum_{p\le x,\ p:\mathrm{prime}}f(p)$ の表。
- 素数べきでの値 $f(p^e)$ を返す関数。

`prime_sum` は、素数和の表を作るための補助関数である。

## 関数一覧
### 構築

```cpp
po167::multiplicative_prefix_sum<T> sieve(N);
```

`T` には `atcoder::modint998244353` などを使う。
内部で $2,3,4,5$ の逆元を使うため、`long long` などの整数型は使えない。

`quotients` には、集合

$$
Q_N=\left\{\left\lfloor\frac{N}{i}\right\rfloor:1\le i\le N\right\}
$$

の要素が降順・重複なしで入る。以下の返り値の配列も、この順序で並ぶ。

### `prime_sum(value, prefix)`

```cpp
auto P = sieve.prime_sum(value, prefix);
```

補助関数 $g$ に対して、次の2つの関数を渡す。

| 引数 | 返す値 |
|---|---|
| `value(p)` | $g(p)$ |
| `prefix(x)` | $\sum_{n=1}^{x}g(n)$ |

$g$ は **完全乗法的**、すなわち $g(1)=1$ かつ、すべての正整数 $a,b$ に対して $g(ab)=g(a)g(b)$ を満たす必要がある。

返り値は、

$$
P[i]=\sum_{\substack{p\le \mathrm{quotients}[i]\\p:\mathrm{prime}}}g(p).
$$

注 : **第2引数で渡すのは全整数の和、返ってくるのは素数だけの和**である。

代表的な使い方は次のとおり。

| $g(n)$ | `value(p)` | `prefix(x)` | 得られる表 |
|---|---|---|---|
| $1$ | $1$ | $x$ | 素数の個数 $P_0(x)$ |
| $n$ | $p$ | $x(x+1)/2$ | 素数の値の和 $P_1(x)$ |

求めたい関数が素数上で $f(p)=a+bp$ なら、$P=aP_0+bP_1$ として素数和の表を作れる。

### `sum(P, prime_power)`

```cpp
auto F = sieve.sum(P, prime_power);
```

| 引数 | 内容 |
|---|---|
| `P[i]` | $\sum_{p\le \mathrm{quotients}[i],\ p:\mathrm{prime}}f(p)$ |
| `prime_power(p, e, pe)` | $f(p^e)$ を返す関数。`pe` には計算済みの $p^e$ が渡される |

返り値は、

$$
F[i]=\sum_{n=1}^{\mathrm{quotients}[i]}f(n).
$$

$f(1)=1$ は内部で処理するため、`prime_power` で $e=0$ を扱う必要はない。

### `get(table, x)`

```cpp
T answer = sieve.get(F, N);
```

表から上限 $x$ に対応する値を取得する。$x$ は $Q_N$ の要素または $0$ に限る。
`get(table, 0)` は $0$ を返す。

## 使用例

[Sum of Multiplicative Function](https://judge.yosupo.jp/problem/sum_of_multiplicative_function) では、

$$
f(p^e)=ae+bp
$$

が与えられる。

素数上では $f(p)=a+bp$ なので、$g(n)=1$ と $g(n)=n$ から素数和を作る。
次は `test/verify/` に置く提出用コードの例。

```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_multiplicative_function"

#include "../../math/multiplicative_prefix_sum.hpp"
#include <atcoder/modint>
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using mint = atcoder::static_modint<469762049>;
    const mint inv2 = mint(1) / 2;

    int T;
    std::cin >> T;
    while (T--){
        long long N;
        int a, b;
        std::cin >> N >> a >> b;

        po167::multiplicative_prefix_sum<mint> sieve(N);

        // P0(x) = sum_{prime p <= x} 1
        auto P0 = sieve.prime_sum(
            [](long long){ return mint(1); },
            [](long long x){ return mint(x); }
        );

        // P1(x) = sum_{prime p <= x} p
        auto P1 = sieve.prime_sum(
            [](long long p){ return mint(p); },
            [inv2](long long x){
                return mint(x) * (mint(x) + 1) * inv2;
            }
        );

        // sum_{prime p <= x} f(p) = a * P0(x) + b * P1(x)
        for (std::size_t i = 0; i < P1.size(); i++){
            P1[i] = P0[i] * a + P1[i] * b;
        }

        // f(p^e) = a * e + b * p
        auto F = sieve.sum(P1, [a, b](long long p, int e, long long){
            return mint(a) * e + mint(b) * p;
        });
        std::cout << sieve.get(F, N).val() << "\n";
    }
}
```

## 計算量

渡す関数の評価と `T` の演算が $O(1)$ のとき、`prime_sum` と `sum` はそれぞれ次の計算量で動作する。

- 時間：$O(N^{2/3}/\log N)$
- 空間：$O(\sqrt N)$

`prime_sum` を $k$ 回使う場合、全体の時間計算量は $O((k+1)N^{2/3}/\log N)$。