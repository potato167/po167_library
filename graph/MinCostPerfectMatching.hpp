#pragma once
#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

namespace po167{
// Input:  n x n cost matrix a
// Output: {min_{p in S_n} sum_i a[i][p[i]], p}
template <class T>
std::pair<long long, std::vector<int>> min_cost_perfect_matching(
    const std::vector<std::vector<T>>& a
) {
    const long long INF = std::numeric_limits<long long>::max() / 4;
    int n = (int)a.size();
    if (n == 0) return {0, {}};
    if (n == 1) return {(long long)a[0][0], {0}};

    std::vector<const T*> c(n);
    for (int i = 0; i < n; i++) c[i] = a[i].data();
    std::vector<int> match(n, -1), inv(n, -1), cnt(n);
    std::vector<long long> v(n);

    // Column reduction
    std::vector<int> bestrow(n);
    for (int j = 0; j < n; j++) v[j] = c[0][j];
    for (int i = 1; i < n; i++) {
        const T* row = c[i];
        for (int j = 0; j < n; j++) {
            if ((long long)row[j] < v[j]) {
                v[j] = row[j];
                bestrow[j] = i;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        int i = c[j][j] == v[j] ? j : bestrow[j];
        cnt[i]++;
        if (match[i] == -1) {
            match[i] = j;
            inv[j] = i;
        }
    }

    // Reduction transfer
    for (int i = 0; i < n; i++) if (cnt[i] == 1) {
        long long best = INF;
        const T* row = c[i];
        int assigned = match[i];
        for (int j = 0; j < n; j++) if (j != assigned)
            best = std::min(best, (long long)row[j] - v[j]);
        v[assigned] -= best;
    }

    // Augmenting row reduction
    for (int rep = 0; rep < 2; rep++) {
        for (int i = 0; i < n; i++) if (match[i] == -1) {
            long long u1 = INF, u2 = INF;
            int j1 = -1;
            const T* row = c[i];
            for (int j = 0; j < n; j++) {
                long long u = (long long)row[j] - v[j];
                if (u < u1 || (u == u1 && j1 != -1 && inv[j1] != -1)) {
                    u2 = u1;
                    u1 = u;
                    j1 = j;
                } else {
                    u2 = std::min(u2, u);
                }
            }
            if (u1 < u2) v[j1] -= u2 - u1;
            if (inv[j1] != -1) match[inv[j1]] = -1;
            match[i] = j1;
            inv[j1] = i;
        }
    }

    // Shortest augmenting paths
    std::vector<long long> dist(n);
    std::vector<int> pred(n), cols(n);
    for (int j = 0; j < n; j++) cols[j] = j;

    for (int root = 0; root < n; root++) if (match[root] == -1) {
        const T* row = c[root];
        for (int j = 0; j < n; j++) {
            dist[j] = (long long)row[j] - v[j];
            pred[j] = root;
        }
        int scanned = 0, labeled = 0, last = 0, free_col = -1;
        while (free_col == -1) {
            if (scanned == labeled) {
                last = scanned;
                long long best = dist[cols[scanned]];
                for (int k = scanned; k < n; k++) {
                    int j = cols[k];
                    if (dist[j] <= best) {
                        if (dist[j] < best) best = dist[j], labeled = scanned;
                        std::swap(cols[k], cols[labeled++]);
                    }
                }
                for (int k = scanned; k < labeled; k++)
                    if (inv[cols[k]] == -1) {
                        free_col = cols[k];
                        break;
                    }
                if (free_col != -1) break;
            }

            int j1 = cols[scanned++], i = inv[j1];
            const T* row = c[i];
            long long prev = dist[j1];
            long long offset = prev - ((long long)row[j1] - v[j1]);
            for (int k = labeled; k < n; k++) {
                int j = cols[k];
                long long nd = offset + (long long)row[j] - v[j];
                if (nd < dist[j]) {
                    dist[j] = nd;
                    pred[j] = i;
                    if (nd == prev) {
                        if (inv[j] == -1) {
                            free_col = j;
                            break;
                        }
                        std::swap(cols[k], cols[labeled++]);
                    }
                }
            }
        }

        for (int k = 0; k < last; k++) {
            int j = cols[k];
            v[j] += dist[j] - dist[free_col];
        }
        while (free_col != -1) {
            int i = pred[free_col];
            int old = match[i];
            match[i] = free_col;
            inv[free_col] = i;
            free_col = old;
        }
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) sum += (long long)c[i][match[i]];
    return {sum, std::move(match)};
}
}