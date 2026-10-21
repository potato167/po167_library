#pragma once
// po167 Monge library v2 (2026-10-21)
#include <cassert>
#include <vector>
#include "smawk.hpp"

namespace po167 {

// f: {(i,j) | 0 <= i < j <= n} -> long long, 0 <= k <= n.
// f(a,c) + f(b,d) <= f(a,d) + f(b,c)  (a < b < c < d).
// ans[d] = min_{0 = v_0 < ... < v_d = n} sum_{t=1}^d f(v_{t-1},v_t), 1 <= d <= k.
// ans[0] は未使用。各 ans[d] は long long、全 DP 値・候補値は T に収まること。
// f が O(1) のとき、時間 O(nk)、追加メモリ O(n)。
template <class T = __int128_t, class F>
std::vector<long long> monge_k_edge_shortest_path(int n, int k, const F& f) {
    assert(0 <= k && k <= n);
    std::vector<long long> answer(k + 1);
    if (k == 0) return answer;
    answer[1] = f(0, n);
    if (k == 1) return answer;

    std::vector<T> prev(n + 1), next(n + 1);
    for (int j = 1; j < n; ++j) prev[j] = T(f(0, j));
    prev[n] = T(answer[1]);
    for (int d = 2; d <= k; ++d) {
        int size = n - d + 1;
        auto argmin = po167::smawk(size, size, [&](int r, int a, int b) {
            int j = r + d, i = a + d - 1, h = b + d - 1;
            return h < j && prev[h] + T(f(h, j)) < prev[i] + T(f(i, j));
        });
        for (int j = d; j <= n; ++j) {
            int i = argmin[j - d] + d - 1;
            next[j] = prev[i] + T(f(i, j));
        }
        answer[d] = (long long)next[n];
        prev.swap(next);
    }
    return answer;
}

}  // namespace po167
