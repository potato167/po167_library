---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/sum_of_multiplicative_function.test.cpp
    title: test/math/sum_of_multiplicative_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/sum_of_multiplicative_function_large.test.cpp
    title: test/math/sum_of_multiplicative_function_large.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/math/sum_of_totient_function.test.cpp
    title: test/math/sum_of_totient_function.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/multiplicative_prefix_sum.hpp\"\n#include <cassert>\n\
    #include <cmath>\n#include <vector>\n\nnamespace po167 {\n\n// f(1) = 1, gcd(a,\
    \ b) = 1 => f(ab) = f(a)f(b).\n// result[i] = sum_{1 <= k <= quotients[i]} f(k).\n\
    // quotients = {N / i : 1 <= i <= N}, in decreasing order.\n// T: a commutative\
    \ ring in which 2, 3, 4, 5 are invertible.\n// Each prime_sum / sum: O(N^(2/3)\
    \ / log N) time, O(sqrt N) space.\ntemplate <class T>\nclass multiplicative_prefix_sum\
    \ {\n    long long n, root, cut = 0, boundary;\n    std::vector<long long> primes;\n\
    \    T inverse[6];\n\n    static long long isqrt(long long x) {\n        long\
    \ long r = std::sqrt((long double)x);\n        while (r && r > x / r) --r;\n \
    \       while (r + 1 <= x / (r + 1)) ++r;\n        return r;\n    }\n\n    //\
    \ Index of the smallest quotient >= x; also accepts non-quotients.\n    std::size_t\
    \ index(long long x) const {\n        return x <= root ? quotients.size() - x\
    \ : n / x - 1;\n    }\n\n    // a at floor(quotients[i] / d). The caller guarantees\
    \ d <= quotients[i].\n    T divided(const std::vector<T>& a, std::size_t i, long\
    \ long d) const {\n        long long x = quotients[i] / d;\n        return a[x\
    \ <= root ? quotients.size() - x : (i + 1) * d - 1];\n    }\n\n    void add_difference(std::vector<T>&\
    \ a, const std::vector<T>& d) const {\n        T s = 0;\n        for (std::size_t\
    \ i = a.size(); i-- > 0;) {\n            s += d[i];\n            a[i] += s;\n\
    \        }\n    }\n\n    // Dirichlet convolution of two functions supported on\
    \ integers > 1\n    // whose prime factors are all greater than cut.\n    std::vector<T>\
    \ convolution(const std::vector<T>& a,\n                               const std::vector<T>&\
    \ b) const {\n        struct term { long long x; T value; };\n        std::vector<term>\
    \ as, bs;\n        const std::size_t m = a.size();\n        for (long long x =\
    \ cut + 1; x <= root; ++x) {\n            T u = a[m - x] - a[m - x + 1];\n   \
    \         T v = b[m - x] - b[m - x + 1];\n            if (u != T(0)) as.push_back({x,\
    \ u});\n            if (v != T(0)) bs.push_back({x, v});\n        }\n        std::vector<T>\
    \ c(m);\n        if (as.empty() && bs.empty()) return c;\n\n        // Below boundary,\
    \ both factors necessarily lie in [1, root].\n        for (const auto& u : as)\
    \ {\n            long long limit = boundary / u.x;\n            for (const auto&\
    \ v : bs) {\n                if (v.x > limit) break;\n                c[index(u.x\
    \ * v.x)] += u.value * v.value;\n            }\n        }\n        for (std::size_t\
    \ i = m; i-- > 1;) c[i - 1] += c[i];\n\n        // Above boundary, use the Dirichlet\
    \ hyperbola formula.\n        for (std::size_t i = 0; i < m && quotients[i] >\
    \ boundary; ++i) {\n            long long r = isqrt(quotients[i]);\n         \
    \   T value = -a[m - r] * b[m - r];\n            for (const auto& u : as) {\n\
    \                if (u.x > r) break;\n                value += u.value * divided(b,\
    \ i, u.x);\n            }\n            for (const auto& v : bs) {\n          \
    \      if (v.x > r) break;\n                value += v.value * divided(a, i, v.x);\n\
    \            }\n            c[i] = value;\n        }\n        return c;\n    }\n\
    \n    // exp(a) or log(1 + a), using Dirichlet multiplication.\n    // Six factors\
    \ with all prime factors > cut have product > n.\n    std::vector<T> series(const\
    \ std::vector<T>& a, bool exponential) const {\n        std::vector<T> result\
    \ = a, power = a;\n        T coefficient = 1;\n        for (int k = 2; k <= 5;\
    \ ++k) {\n            power = convolution(power, a);\n            if (exponential)\
    \ coefficient *= inverse[k];\n            else coefficient = k % 2 ? inverse[k]\
    \ : -inverse[k];\n            for (std::size_t i = 0; i < a.size(); ++i)\n   \
    \             result[i] += coefficient * power[i];\n        }\n        if (exponential)\
    \ for (T& x : result) x += T(1);\n        return result;\n    }\n\npublic:\n \
    \   std::vector<long long> quotients;\n\n    explicit multiplicative_prefix_sum(long\
    \ long N) : n(N), root(0) {\n        assert(n >= 0);\n        root = isqrt(n);\n\
    \        while ((cut + 1) * (cut + 1) * (cut + 1) <= root) ++cut;\n        boundary\
    \ = root * (cut + 1);\n        for (int k = 1; k <= 5; ++k) inverse[k] = T(1)\
    \ / T(k);\n        for (long long l = 1; l <= n;) {\n            long long x =\
    \ n / l;\n            quotients.push_back(x);\n            if (x == 1) break;\n\
    \            l = n / x + 1;\n        }\n        std::vector<bool> composite(root\
    \ + 1);\n        for (long long p = 2; p <= root; ++p) {\n            if (composite[p])\
    \ continue;\n            primes.push_back(p);\n            if (p <= root / p)\n\
    \                for (long long q = p * p; q <= root; q += p) composite[q] = true;\n\
    \        }\n    }\n\n    // x must be 0 or an element of quotients.\n    T get(const\
    \ std::vector<T>& a, long long x) const {\n        assert(a.size() == quotients.size()\
    \ && 0 <= x && x <= n);\n        if (x == 0) return T(0);\n        std::size_t\
    \ i = index(x);\n        assert(quotients[i] == x);\n        return a[i];\n  \
    \  }\n\n    // g(ab) = g(a)g(b) for ALL a, b, and g(1) = 1.\n    // value(p) =\
    \ g(p), prefix(x) = sum_{1 <= k <= x} g(k), both O(1).\n    // Returns sum_{prime\
    \ p <= quotients[i]} g(p).\n    template <class Value, class Prefix>\n    std::vector<T>\
    \ prime_sum(Value value, Prefix prefix) const {\n        std::vector<T> a;\n \
    \       a.reserve(quotients.size());\n        for (long long x : quotients) a.push_back(prefix(x));\n\
    \        for (long long p : primes) {\n            if (p > cut) break;\n     \
    \       T fp = value(p);\n            for (std::size_t i = 0; i < a.size() &&\
    \ quotients[i] >= p; ++i)\n                a[i] -= fp * divided(a, i, p);\n  \
    \      }\n        for (T& x : a) x -= T(1);\n        a = series(a, false);\n\n\
    \        std::vector<T> d(a.size());\n        for (long long p : primes) {\n \
    \           T fp = value(p), power = fp;\n            if (p <= cut) {\n      \
    \          d[index(p)] += fp;\n                continue;\n            }\n    \
    \        long long q = p;\n            for (int e = 2; q <= n / p; ++e) {\n  \
    \              q *= p;\n                power *= fp;\n                d[index(q)]\
    \ -= power * inverse[e];\n            }\n        }\n        add_difference(a,\
    \ d);\n        return a;\n    }\n\n    // prime[i] = sum_{prime p <= quotients[i]}\
    \ f(p).\n    // prime_power(p, e, pe) = f(p^e), where pe = p^e, in O(1).\n   \
    \ // Returns sum_{1 <= k <= quotients[i]} f(k).\n    template <class PrimePower>\n\
    \    std::vector<T> sum(std::vector<T> prime, PrimePower prime_power) const {\n\
    \        assert(prime.size() == quotients.size());\n        if (n == 0) return\
    \ prime;\n        T small = get(prime, cut);\n        for (std::size_t i = 0;\
    \ i < prime.size(); ++i)\n            prime[i] = quotients[i] > cut ? prime[i]\
    \ - small : T(0);\n\n        std::vector<T> d(prime.size());\n        for (long\
    \ long p : primes) {\n            if (p <= cut) continue;\n            T a[6],\
    \ logarithm[6];\n            a[1] = logarithm[1] = prime_power(p, 1, p);\n   \
    \         long long q = p;\n            for (int e = 2; q <= n / p; ++e) {\n \
    \               q *= p;\n                a[e] = prime_power(p, e, q);\n      \
    \          T s = 0;\n                for (int j = 1; j < e; ++j) s += T(j) * logarithm[j]\
    \ * a[e - j];\n                logarithm[e] = a[e] - s * inverse[e];\n       \
    \         d[index(q)] += logarithm[e];\n            }\n        }\n        add_difference(prime,\
    \ d);\n        prime = series(prime, true);\n\n        for (long long p : primes)\
    \ {\n            if (p > cut) break;\n            std::vector<long long> powers;\n\
    \            std::vector<T> coefficients;\n            for (long long q = p, e\
    \ = 1;; q *= p, ++e) {\n                powers.push_back(q);\n               \
    \ coefficients.push_back(prime_power(p, (int)e, q));\n                if (q >\
    \ n / p) break;\n            }\n            for (std::size_t i = 0; i < prime.size()\
    \ && quotients[i] >= p; ++i)\n                for (std::size_t j = 0; j < powers.size()\
    \ && powers[j] <= quotients[i]; ++j)\n                    prime[i] += coefficients[j]\
    \ * divided(prime, i, powers[j]);\n        }\n        return prime;\n    }\n};\n\
    \n} // namespace po167\n"
  code: "#pragma once\n#include <cassert>\n#include <cmath>\n#include <vector>\n\n\
    namespace po167 {\n\n// f(1) = 1, gcd(a, b) = 1 => f(ab) = f(a)f(b).\n// result[i]\
    \ = sum_{1 <= k <= quotients[i]} f(k).\n// quotients = {N / i : 1 <= i <= N},\
    \ in decreasing order.\n// T: a commutative ring in which 2, 3, 4, 5 are invertible.\n\
    // Each prime_sum / sum: O(N^(2/3) / log N) time, O(sqrt N) space.\ntemplate <class\
    \ T>\nclass multiplicative_prefix_sum {\n    long long n, root, cut = 0, boundary;\n\
    \    std::vector<long long> primes;\n    T inverse[6];\n\n    static long long\
    \ isqrt(long long x) {\n        long long r = std::sqrt((long double)x);\n   \
    \     while (r && r > x / r) --r;\n        while (r + 1 <= x / (r + 1)) ++r;\n\
    \        return r;\n    }\n\n    // Index of the smallest quotient >= x; also\
    \ accepts non-quotients.\n    std::size_t index(long long x) const {\n       \
    \ return x <= root ? quotients.size() - x : n / x - 1;\n    }\n\n    // a at floor(quotients[i]\
    \ / d). The caller guarantees d <= quotients[i].\n    T divided(const std::vector<T>&\
    \ a, std::size_t i, long long d) const {\n        long long x = quotients[i] /\
    \ d;\n        return a[x <= root ? quotients.size() - x : (i + 1) * d - 1];\n\
    \    }\n\n    void add_difference(std::vector<T>& a, const std::vector<T>& d)\
    \ const {\n        T s = 0;\n        for (std::size_t i = a.size(); i-- > 0;)\
    \ {\n            s += d[i];\n            a[i] += s;\n        }\n    }\n\n    //\
    \ Dirichlet convolution of two functions supported on integers > 1\n    // whose\
    \ prime factors are all greater than cut.\n    std::vector<T> convolution(const\
    \ std::vector<T>& a,\n                               const std::vector<T>& b)\
    \ const {\n        struct term { long long x; T value; };\n        std::vector<term>\
    \ as, bs;\n        const std::size_t m = a.size();\n        for (long long x =\
    \ cut + 1; x <= root; ++x) {\n            T u = a[m - x] - a[m - x + 1];\n   \
    \         T v = b[m - x] - b[m - x + 1];\n            if (u != T(0)) as.push_back({x,\
    \ u});\n            if (v != T(0)) bs.push_back({x, v});\n        }\n        std::vector<T>\
    \ c(m);\n        if (as.empty() && bs.empty()) return c;\n\n        // Below boundary,\
    \ both factors necessarily lie in [1, root].\n        for (const auto& u : as)\
    \ {\n            long long limit = boundary / u.x;\n            for (const auto&\
    \ v : bs) {\n                if (v.x > limit) break;\n                c[index(u.x\
    \ * v.x)] += u.value * v.value;\n            }\n        }\n        for (std::size_t\
    \ i = m; i-- > 1;) c[i - 1] += c[i];\n\n        // Above boundary, use the Dirichlet\
    \ hyperbola formula.\n        for (std::size_t i = 0; i < m && quotients[i] >\
    \ boundary; ++i) {\n            long long r = isqrt(quotients[i]);\n         \
    \   T value = -a[m - r] * b[m - r];\n            for (const auto& u : as) {\n\
    \                if (u.x > r) break;\n                value += u.value * divided(b,\
    \ i, u.x);\n            }\n            for (const auto& v : bs) {\n          \
    \      if (v.x > r) break;\n                value += v.value * divided(a, i, v.x);\n\
    \            }\n            c[i] = value;\n        }\n        return c;\n    }\n\
    \n    // exp(a) or log(1 + a), using Dirichlet multiplication.\n    // Six factors\
    \ with all prime factors > cut have product > n.\n    std::vector<T> series(const\
    \ std::vector<T>& a, bool exponential) const {\n        std::vector<T> result\
    \ = a, power = a;\n        T coefficient = 1;\n        for (int k = 2; k <= 5;\
    \ ++k) {\n            power = convolution(power, a);\n            if (exponential)\
    \ coefficient *= inverse[k];\n            else coefficient = k % 2 ? inverse[k]\
    \ : -inverse[k];\n            for (std::size_t i = 0; i < a.size(); ++i)\n   \
    \             result[i] += coefficient * power[i];\n        }\n        if (exponential)\
    \ for (T& x : result) x += T(1);\n        return result;\n    }\n\npublic:\n \
    \   std::vector<long long> quotients;\n\n    explicit multiplicative_prefix_sum(long\
    \ long N) : n(N), root(0) {\n        assert(n >= 0);\n        root = isqrt(n);\n\
    \        while ((cut + 1) * (cut + 1) * (cut + 1) <= root) ++cut;\n        boundary\
    \ = root * (cut + 1);\n        for (int k = 1; k <= 5; ++k) inverse[k] = T(1)\
    \ / T(k);\n        for (long long l = 1; l <= n;) {\n            long long x =\
    \ n / l;\n            quotients.push_back(x);\n            if (x == 1) break;\n\
    \            l = n / x + 1;\n        }\n        std::vector<bool> composite(root\
    \ + 1);\n        for (long long p = 2; p <= root; ++p) {\n            if (composite[p])\
    \ continue;\n            primes.push_back(p);\n            if (p <= root / p)\n\
    \                for (long long q = p * p; q <= root; q += p) composite[q] = true;\n\
    \        }\n    }\n\n    // x must be 0 or an element of quotients.\n    T get(const\
    \ std::vector<T>& a, long long x) const {\n        assert(a.size() == quotients.size()\
    \ && 0 <= x && x <= n);\n        if (x == 0) return T(0);\n        std::size_t\
    \ i = index(x);\n        assert(quotients[i] == x);\n        return a[i];\n  \
    \  }\n\n    // g(ab) = g(a)g(b) for ALL a, b, and g(1) = 1.\n    // value(p) =\
    \ g(p), prefix(x) = sum_{1 <= k <= x} g(k), both O(1).\n    // Returns sum_{prime\
    \ p <= quotients[i]} g(p).\n    template <class Value, class Prefix>\n    std::vector<T>\
    \ prime_sum(Value value, Prefix prefix) const {\n        std::vector<T> a;\n \
    \       a.reserve(quotients.size());\n        for (long long x : quotients) a.push_back(prefix(x));\n\
    \        for (long long p : primes) {\n            if (p > cut) break;\n     \
    \       T fp = value(p);\n            for (std::size_t i = 0; i < a.size() &&\
    \ quotients[i] >= p; ++i)\n                a[i] -= fp * divided(a, i, p);\n  \
    \      }\n        for (T& x : a) x -= T(1);\n        a = series(a, false);\n\n\
    \        std::vector<T> d(a.size());\n        for (long long p : primes) {\n \
    \           T fp = value(p), power = fp;\n            if (p <= cut) {\n      \
    \          d[index(p)] += fp;\n                continue;\n            }\n    \
    \        long long q = p;\n            for (int e = 2; q <= n / p; ++e) {\n  \
    \              q *= p;\n                power *= fp;\n                d[index(q)]\
    \ -= power * inverse[e];\n            }\n        }\n        add_difference(a,\
    \ d);\n        return a;\n    }\n\n    // prime[i] = sum_{prime p <= quotients[i]}\
    \ f(p).\n    // prime_power(p, e, pe) = f(p^e), where pe = p^e, in O(1).\n   \
    \ // Returns sum_{1 <= k <= quotients[i]} f(k).\n    template <class PrimePower>\n\
    \    std::vector<T> sum(std::vector<T> prime, PrimePower prime_power) const {\n\
    \        assert(prime.size() == quotients.size());\n        if (n == 0) return\
    \ prime;\n        T small = get(prime, cut);\n        for (std::size_t i = 0;\
    \ i < prime.size(); ++i)\n            prime[i] = quotients[i] > cut ? prime[i]\
    \ - small : T(0);\n\n        std::vector<T> d(prime.size());\n        for (long\
    \ long p : primes) {\n            if (p <= cut) continue;\n            T a[6],\
    \ logarithm[6];\n            a[1] = logarithm[1] = prime_power(p, 1, p);\n   \
    \         long long q = p;\n            for (int e = 2; q <= n / p; ++e) {\n \
    \               q *= p;\n                a[e] = prime_power(p, e, q);\n      \
    \          T s = 0;\n                for (int j = 1; j < e; ++j) s += T(j) * logarithm[j]\
    \ * a[e - j];\n                logarithm[e] = a[e] - s * inverse[e];\n       \
    \         d[index(q)] += logarithm[e];\n            }\n        }\n        add_difference(prime,\
    \ d);\n        prime = series(prime, true);\n\n        for (long long p : primes)\
    \ {\n            if (p > cut) break;\n            std::vector<long long> powers;\n\
    \            std::vector<T> coefficients;\n            for (long long q = p, e\
    \ = 1;; q *= p, ++e) {\n                powers.push_back(q);\n               \
    \ coefficients.push_back(prime_power(p, (int)e, q));\n                if (q >\
    \ n / p) break;\n            }\n            for (std::size_t i = 0; i < prime.size()\
    \ && quotients[i] >= p; ++i)\n                for (std::size_t j = 0; j < powers.size()\
    \ && powers[j] <= quotients[i]; ++j)\n                    prime[i] += coefficients[j]\
    \ * divided(prime, i, powers[j]);\n        }\n        return prime;\n    }\n};\n\
    \n} // namespace po167\n"
  dependsOn: []
  isVerificationFile: false
  path: math/multiplicative_prefix_sum.hpp
  requiredBy: []
  timestamp: '2026-10-22 04:47:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/sum_of_totient_function.test.cpp
  - test/math/sum_of_multiplicative_function.test.cpp
  - test/math/sum_of_multiplicative_function_large.test.cpp
documentation_of: math/multiplicative_prefix_sum.hpp
layout: document
title: "\u4E57\u6CD5\u7684\u95A2\u6570\u306E\u7D2F\u7A4D\u548C"
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