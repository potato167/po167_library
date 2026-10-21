#pragma once
#include <cassert>
#include <cmath>
#include <vector>

namespace po167 {

// f(1) = 1, gcd(a, b) = 1 => f(ab) = f(a)f(b).
// result[i] = sum_{1 <= k <= quotients[i]} f(k).
// quotients = {N / i : 1 <= i <= N}, in decreasing order.
// T: a commutative ring in which 2, 3, 4, 5 are invertible.
// Each prime_sum / sum: O(N^(2/3) / log N) time, O(sqrt N) space.
template <class T>
class multiplicative_prefix_sum {
    long long n, root, cut = 0, boundary;
    std::vector<long long> primes;
    T inverse[6];

    static long long isqrt(long long x) {
        long long r = std::sqrt((long double)x);
        while (r && r > x / r) --r;
        while (r + 1 <= x / (r + 1)) ++r;
        return r;
    }

    // Index of the smallest quotient >= x; also accepts non-quotients.
    std::size_t index(long long x) const {
        return x <= root ? quotients.size() - x : n / x - 1;
    }

    // a at floor(quotients[i] / d). The caller guarantees d <= quotients[i].
    T divided(const std::vector<T>& a, std::size_t i, long long d) const {
        long long x = quotients[i] / d;
        return a[x <= root ? quotients.size() - x : (i + 1) * d - 1];
    }

    void add_difference(std::vector<T>& a, const std::vector<T>& d) const {
        T s = 0;
        for (std::size_t i = a.size(); i-- > 0;) {
            s += d[i];
            a[i] += s;
        }
    }

    // Dirichlet convolution of two functions supported on integers > 1
    // whose prime factors are all greater than cut.
    std::vector<T> convolution(const std::vector<T>& a,
                               const std::vector<T>& b) const {
        struct term { long long x; T value; };
        std::vector<term> as, bs;
        const std::size_t m = a.size();
        for (long long x = cut + 1; x <= root; ++x) {
            T u = a[m - x] - a[m - x + 1];
            T v = b[m - x] - b[m - x + 1];
            if (u != T(0)) as.push_back({x, u});
            if (v != T(0)) bs.push_back({x, v});
        }
        std::vector<T> c(m);
        if (as.empty() && bs.empty()) return c;

        // Below boundary, both factors necessarily lie in [1, root].
        for (const auto& u : as) {
            long long limit = boundary / u.x;
            for (const auto& v : bs) {
                if (v.x > limit) break;
                c[index(u.x * v.x)] += u.value * v.value;
            }
        }
        for (std::size_t i = m; i-- > 1;) c[i - 1] += c[i];

        // Above boundary, use the Dirichlet hyperbola formula.
        for (std::size_t i = 0; i < m && quotients[i] > boundary; ++i) {
            long long r = isqrt(quotients[i]);
            T value = -a[m - r] * b[m - r];
            for (const auto& u : as) {
                if (u.x > r) break;
                value += u.value * divided(b, i, u.x);
            }
            for (const auto& v : bs) {
                if (v.x > r) break;
                value += v.value * divided(a, i, v.x);
            }
            c[i] = value;
        }
        return c;
    }

    // exp(a) or log(1 + a), using Dirichlet multiplication.
    // Six factors with all prime factors > cut have product > n.
    std::vector<T> series(const std::vector<T>& a, bool exponential) const {
        std::vector<T> result = a, power = a;
        T coefficient = 1;
        for (int k = 2; k <= 5; ++k) {
            power = convolution(power, a);
            if (exponential) coefficient *= inverse[k];
            else coefficient = k % 2 ? inverse[k] : -inverse[k];
            for (std::size_t i = 0; i < a.size(); ++i)
                result[i] += coefficient * power[i];
        }
        if (exponential) for (T& x : result) x += T(1);
        return result;
    }

public:
    std::vector<long long> quotients;

    explicit multiplicative_prefix_sum(long long N) : n(N), root(0) {
        assert(n >= 0);
        root = isqrt(n);
        while ((cut + 1) * (cut + 1) * (cut + 1) <= root) ++cut;
        boundary = root * (cut + 1);
        for (int k = 1; k <= 5; ++k) inverse[k] = T(1) / T(k);
        for (long long l = 1; l <= n;) {
            long long x = n / l;
            quotients.push_back(x);
            if (x == 1) break;
            l = n / x + 1;
        }
        std::vector<bool> composite(root + 1);
        for (long long p = 2; p <= root; ++p) {
            if (composite[p]) continue;
            primes.push_back(p);
            if (p <= root / p)
                for (long long q = p * p; q <= root; q += p) composite[q] = true;
        }
    }

    // x must be 0 or an element of quotients.
    T get(const std::vector<T>& a, long long x) const {
        assert(a.size() == quotients.size() && 0 <= x && x <= n);
        if (x == 0) return T(0);
        std::size_t i = index(x);
        assert(quotients[i] == x);
        return a[i];
    }

    // g(ab) = g(a)g(b) for ALL a, b, and g(1) = 1.
    // value(p) = g(p), prefix(x) = sum_{1 <= k <= x} g(k), both O(1).
    // Returns sum_{prime p <= quotients[i]} g(p).
    template <class Value, class Prefix>
    std::vector<T> prime_sum(Value value, Prefix prefix) const {
        std::vector<T> a;
        a.reserve(quotients.size());
        for (long long x : quotients) a.push_back(prefix(x));
        for (long long p : primes) {
            if (p > cut) break;
            T fp = value(p);
            for (std::size_t i = 0; i < a.size() && quotients[i] >= p; ++i)
                a[i] -= fp * divided(a, i, p);
        }
        for (T& x : a) x -= T(1);
        a = series(a, false);

        std::vector<T> d(a.size());
        for (long long p : primes) {
            T fp = value(p), power = fp;
            if (p <= cut) {
                d[index(p)] += fp;
                continue;
            }
            long long q = p;
            for (int e = 2; q <= n / p; ++e) {
                q *= p;
                power *= fp;
                d[index(q)] -= power * inverse[e];
            }
        }
        add_difference(a, d);
        return a;
    }

    // prime[i] = sum_{prime p <= quotients[i]} f(p).
    // prime_power(p, e, pe) = f(p^e), where pe = p^e, in O(1).
    // Returns sum_{1 <= k <= quotients[i]} f(k).
    template <class PrimePower>
    std::vector<T> sum(std::vector<T> prime, PrimePower prime_power) const {
        assert(prime.size() == quotients.size());
        if (n == 0) return prime;
        T small = get(prime, cut);
        for (std::size_t i = 0; i < prime.size(); ++i)
            prime[i] = quotients[i] > cut ? prime[i] - small : T(0);

        std::vector<T> d(prime.size());
        for (long long p : primes) {
            if (p <= cut) continue;
            T a[6], logarithm[6];
            a[1] = logarithm[1] = prime_power(p, 1, p);
            long long q = p;
            for (int e = 2; q <= n / p; ++e) {
                q *= p;
                a[e] = prime_power(p, e, q);
                T s = 0;
                for (int j = 1; j < e; ++j) s += T(j) * logarithm[j] * a[e - j];
                logarithm[e] = a[e] - s * inverse[e];
                d[index(q)] += logarithm[e];
            }
        }
        add_difference(prime, d);
        prime = series(prime, true);

        for (long long p : primes) {
            if (p > cut) break;
            std::vector<long long> powers;
            std::vector<T> coefficients;
            for (long long q = p, e = 1;; q *= p, ++e) {
                powers.push_back(q);
                coefficients.push_back(prime_power(p, (int)e, q));
                if (q > n / p) break;
            }
            for (std::size_t i = 0; i < prime.size() && quotients[i] >= p; ++i)
                for (std::size_t j = 0; j < powers.size() && powers[j] <= quotients[i]; ++j)
                    prime[i] += coefficients[j] * divided(prime, i, powers[j]);
        }
        return prime;
    }
};

} // namespace po167
