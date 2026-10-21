---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/multiplicative_prefix_sum.hpp
    title: "\u4E57\u6CD5\u7684\u95A2\u6570\u306E\u7D2F\u7A4D\u548C"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large
    links:
    - https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large
  bundledCode: "#line 1 \"test/math/sum_of_multiplicative_function_large.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large\"\
    \n\n#line 2 \"math/multiplicative_prefix_sum.hpp\"\n#include <cassert>\n#include\
    \ <cmath>\n#include <vector>\n\nnamespace po167 {\n\n// f(1) = 1, gcd(a, b) =\
    \ 1 => f(ab) = f(a)f(b).\n// result[i] = sum_{1 <= k <= quotients[i]} f(k).\n\
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
    \n} // namespace po167\n#line 4 \"test/math/sum_of_multiplicative_function_large.test.cpp\"\
    \n#include <atcoder/modint>\n#include <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    using mint = atcoder::static_modint<469762049>;\n\
    \    const mint inv2 = mint(1) / 2;\n\n    int T;\n    std::cin >> T;\n    while\
    \ (T--){\n        long long N;\n        int a, b;\n        std::cin >> N >> a\
    \ >> b;\n\n        po167::multiplicative_prefix_sum<mint> sieve(N);\n\n      \
    \  auto P0 = sieve.prime_sum(\n            [](long long){ return mint(1); },\n\
    \            [](long long x){ return mint(x); }\n        );\n        auto P1 =\
    \ sieve.prime_sum(\n            [](long long p){ return mint(p); },\n        \
    \    [inv2](long long x){\n                return mint(x) * (mint(x) + 1) * inv2;\n\
    \            }\n        );\n        for (std::size_t i = 0; i < P1.size(); i++){\n\
    \            P1[i] = P0[i] * a + P1[i] * b;\n        }\n\n        auto F = sieve.sum(P1,\
    \ [a, b](long long p, int e, long long){\n            return mint(a) * e + mint(b)\
    \ * p;\n        });\n        std::cout << sieve.get(F, N).val() << \"\\n\";\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_multiplicative_function_large\"\
    \n\n#include \"../../math/multiplicative_prefix_sum.hpp\"\n#include <atcoder/modint>\n\
    #include <iostream>\n\nint main(){\n    std::ios::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n\n    using mint = atcoder::static_modint<469762049>;\n\
    \    const mint inv2 = mint(1) / 2;\n\n    int T;\n    std::cin >> T;\n    while\
    \ (T--){\n        long long N;\n        int a, b;\n        std::cin >> N >> a\
    \ >> b;\n\n        po167::multiplicative_prefix_sum<mint> sieve(N);\n\n      \
    \  auto P0 = sieve.prime_sum(\n            [](long long){ return mint(1); },\n\
    \            [](long long x){ return mint(x); }\n        );\n        auto P1 =\
    \ sieve.prime_sum(\n            [](long long p){ return mint(p); },\n        \
    \    [inv2](long long x){\n                return mint(x) * (mint(x) + 1) * inv2;\n\
    \            }\n        );\n        for (std::size_t i = 0; i < P1.size(); i++){\n\
    \            P1[i] = P0[i] * a + P1[i] * b;\n        }\n\n        auto F = sieve.sum(P1,\
    \ [a, b](long long p, int e, long long){\n            return mint(a) * e + mint(b)\
    \ * p;\n        });\n        std::cout << sieve.get(F, N).val() << \"\\n\";\n\
    \    }\n}"
  dependsOn:
  - math/multiplicative_prefix_sum.hpp
  isVerificationFile: true
  path: test/math/sum_of_multiplicative_function_large.test.cpp
  requiredBy: []
  timestamp: '2026-10-22 04:47:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/sum_of_multiplicative_function_large.test.cpp
layout: document
redirect_from:
- /verify/test/math/sum_of_multiplicative_function_large.test.cpp
- /verify/test/math/sum_of_multiplicative_function_large.test.cpp.html
title: test/math/sum_of_multiplicative_function_large.test.cpp
---
