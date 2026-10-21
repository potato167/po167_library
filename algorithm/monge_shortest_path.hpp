#pragma once
// po167 Monge library v2: predecessor support (2026-10-21)
#include <cassert>
#include <utility>
#include <vector>
#include "larsch.hpp"

namespace po167 {

// f(a,c)+f(b,d) <= f(a,d)+f(b,c) (0 <= a < b < c < d <= n).
// return {dp, prev}: dp[0]=0, prev[0]=-1.
// dp[j]=min_{0 <= i < j}(dp[i]+f(i,j)) (1 <= j <= n).
// prev[j]=min argmin_{0 <= i < j}(dp[i]+f(i,j)).
// n >= 0; all costs and candidate sums must fit in T. Negative costs are allowed.
// O(n) time, O(n) space, assuming f is O(1).
template <class T = long long, class F>
std::pair<std::vector<T>, std::vector<int>> monge_shortest_path(int n, const F& f) {
    assert(n >= 0);
    std::vector<T> dp(n + 1);
    std::vector<int> prev(n + 1, -1);
    auto value = [&](int row, int col) { return dp[col] + T(f(col, row + 1)); };
    detail::Larsch<decltype(value)> solver(n, value);
    for (int v = 1; v <= n; ++v) {
        int p = prev[v] = solver.next_argmin();
        dp[v] = dp[p] + T(f(p, v));
    }
    return {std::move(dp), std::move(prev)};
}

}  // namespace po167
