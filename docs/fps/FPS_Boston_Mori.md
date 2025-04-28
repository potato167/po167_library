---
title: ボスタン森法
documentation_of: //fps/FPS_Boston_Mori.hpp
---

## ボスタン森法

#### <code>T Boston_Mori(long long k, std::vector<T> P, std::vector<T> Q)</code>

$[x^{k}](P(x) / Q(x))$ を返す関数

$N = \max(|P|, |Q|)$ として、 $O(N\log(N)\log(k))$

$Q(x)$ の DFT から $Q(-x)$ の DFT が簡単に求まることや、偶奇の取り出し、$0$ 詰めなどの高速化を行なっている。

## 線形漸化式

#### <code>T Kth_Linear(long long k, std::vector<T> a, std::vector<T> c)</code>

$|a| = d, |c| = d + 1$ を満たす数列 $a, c$ を用いて、以下を満たす正整数列 $b$ の $k$ 項目を求める。

- $0\leq i< d\implies b_{i} = a_{i}$
- $k\leq i\implies 0 = \sum_{j = 0}^{d}b_{i - j}c_{j}$

計算量は $O(d\log(d)\log(k))$
