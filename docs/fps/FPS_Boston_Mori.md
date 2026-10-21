---
title: ボスタン森法
documentation_of: //fps/FPS_Boston_Mori.hpp
---

## ボスタン森法

```cpp
T Boston_Mori(long long k, std::vector<T> P, std::vector<T> Q);
```

$[x^k](P(x)/Q(x))$ を返す。

$N = \max(\lvert P\rvert, \lvert Q\rvert)$ として、
計算量は $O(N\log N\log k)$。

$Q(x)$ の DFT から $Q(-x)$ の DFT を求めることや、
偶奇成分の取り出し、ゼロ埋めなどを利用して高速化している。

## 線形漸化式

```cpp
T Kth_Linear(long long k, std::vector<T> a, std::vector<T> c);
```

$\lvert a\rvert = d$、$\lvert c\rvert = d+1$ を満たす数列 $a,c$ を受け取り、
以下を満たす数列 $b$ の第 $k$ 項を返す。添字は $0$ 始まり。

$$
b_i = a_i \qquad (0 \leq i < d)
$$

$$
\sum_{j=0}^{d} b_{i-j}c_j = 0 \qquad (i \geq d)
$$

計算量は $O(d\log d\log k)$。