---
title: 二項係数関連
documentation_of: //math/Binomial.hpp
---

## 説明

二項係数関連のものを詰め込んでいる。

### <code>Catalan(int n)</code>
カタラン数を返す

### <code>narayana(int n)</code>
narayama_number を返す
https://yukicoder.me/problems/no/2472 あとで verify

### <code>Catalan_pow(int n,int d)</code>

カタラン数の母関数を $C(x)$ としたとき、 $[x^{n}]C(x)^{d}$ を返す


### <code>ruiseki(int a,int b)</code>

$[x^{a}]\dfrac{1}{(1-x)^{b}}$

### <code>mirror(int a, int b, int c, int d, int e = 0)</code>
$2$ 次元座標上の点 $(a, b)$ から $(c, d)$ にグリッドに沿って進む場合の数。ただし、$x + e \ge y$ を常に、満たす。これは鏡像法でもとまる。カタラン数の拡張