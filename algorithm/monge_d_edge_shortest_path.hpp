#pragma once
// po167 Monge library v2 (2026-10-21)
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "larsch.hpp"

namespace po167 {

// f(a,c)+f(b,d) <= f(a,d)+f(b,c) (0 <= a < b < c < d <= n).
// return min_{0=v_0 < v_1 < ... < v_d=n} sum_{t=1}^d f(v_{t-1},v_t).
// 1 <= d <= n; f(i,j) and the answer must fit in long long. Internal type: __int128_t.
// O(n log(W+2)) time, O(n) space; W is the internally computed penalty range.
template <class F>
long long monge_d_edge_shortest_path(int n, int d, const F& f) {
    using T = __int128_t;
    const T inf = T(1) << 120;
    assert(1 <= d && d <= n);
    if (d == 1) return f(0, n);
    if (d == n) {
        T total = 0;
        for (int i = 0; i < n; ++i) total += T(f(i, i + 1));
        return (long long)total;
    }

    // C[1], C[2], C[n], C[n]-C[n-1].
    T one = f(0, n), two = inf, total = f(0, 1);
    T previous = total, last_diff = -inf;
    for (int i = 1; i < n; ++i) {
        T next = f(i, i + 1);
        total += next;
        two = std::min(two, T(f(0, i)) + T(f(i, n)));
        last_diff = std::max(last_diff, previous + next - T(f(i - 1, i + 1)));
        previous = next;
    }
    if (d == 2) return (long long)two;
    if (d == n - 1) return (long long)(total - last_diff);

    std::vector<T> dp(n + 1);
    std::vector<int> parent(n + 1);
    auto value = [&](int row, int col) { return dp[col] + T(f(col, row + 1)); };
    detail::Larsch<decltype(value)> solver(n, value);
    auto solve = [&](T penalty) {
        solver.reset();
        dp[0] = penalty;
        for (int v = 1; v <= n; ++v) {
            int p = parent[v] = solver.next_argmin();
            dp[v] = dp[p] + T(f(p, v)) + penalty;
        }
        int count = 0;
        for (int v = n; v; v = parent[v]) ++count;
        return std::pair<T, int>(dp[n] - penalty, count);
    };

    T lo = -last_diff, hi = one - two;
    assert(lo <= hi);
    T answer = std::max(total + T(n - d) * lo, one + T(1 - d) * hi);
    T left_cost = total, right_cost = one;
    int left_count = n, right_count = 1;
    ++lo;
    --hi;
    bool bisect = false;
    while (lo <= hi) {
        T width = hi - lo, x = lo + width / 2;
        if (!bisect) {
            // left_cost+left_count*x = right_cost+right_count*x.
            T a = right_cost - left_cost, b = left_count - right_count;
            x = std::clamp(a / b - (a % b < 0), lo, hi);
        }
        auto [cost, count] = solve(x);
        answer = std::max(answer, cost - T(d) * x);
        if (count == d) break;
        if (count > d) {
            lo = x + 1;
            left_cost = cost - T(count) * x;
            left_count = count;
        } else {
            hi = x - 1;
            right_cost = cost - T(count) * x;
            right_count = count;
        }
        bisect = 2 * (hi - lo) > width;
    }
    return (long long)answer;
}

// return monge_d_edge_shortest_path(n,d,f); upper is unused (compatibility overload).
template <class F>
long long monge_d_edge_shortest_path(int n, int d, long long, const F& f) {
    return monge_d_edge_shortest_path(n, d, f);
}

}  // namespace po167
