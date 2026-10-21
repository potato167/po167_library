#pragma once
// po167 Monge library v2 (2026-10-21)
#include <cassert>
#include <utility>
#include <vector>

namespace po167 {
namespace detail {

// A[r][c] = value(r,c), 0 <= c <= r < n: Monge.
// r-th next_argmin() = min argmin_{0 <= c <= r} A[r][c].
// O(n) total time, O(n) space.
// https://noshi91.github.io/Library/algorithm/larsch.cpp.html (CC0)
template <class F>
class Larsch {
    struct Level {
        int n, row = 0, state = 0, size = 0;
        std::vector<int> column;
        Level(int n_, bool base) : n(n_), column(base ? 0 : n_) {}
    };
    F value;
    std::vector<Level> levels;

    int next_argmin(int depth) {
        auto& a = levels[depth];
        int row = a.row++, r = ((row + 1) << depth) - 1;
        auto column = [&](int j) { return depth ? a.column[j] : j; };
        int best = column(a.state);
        if (row & 1) {
            int last = column(row);
            return value(r, last) < value(r, best) ? last : best;
        }
        int bound;
        if (row + 1 == a.n) {
            bound = column(a.n - 1);
        } else {
            auto& b = levels[depth + 1];
            for (int j = (row ? row - 1 : 0); j <= row; ++j) {
                int c = column(j);
                while (b.size > row / 2) {
                    int q = (b.size << (depth + 1)) - 1;
                    if (!(value(q, c) < value(q, b.column[b.size - 1]))) break;
                    --b.size;
                }
                if (b.size < b.n) b.column[b.size++] = c;
            }
            bound = next_argmin(depth + 1);
        }
        if (best != bound) {
            auto best_value = value(r, best);
            do {
                int c = column(++a.state);
                auto candidate = value(r, c);
                if (candidate < best_value) best_value = candidate, best = c;
            } while (column(a.state) != bound);
        }
        return best;
    }

public:
    // A[r][c] = value_(r,c), 0 <= c <= r < n; next row = 0.
    Larsch(int n, F value_) : value(std::move(value_)) {
        assert(n >= 0);
        for (int size = n; size; size /= 2) levels.emplace_back(size, levels.empty());
    }

    // return min argmin_{0 <= c <= r} A[r][c], then r <- r+1.
    int next_argmin() {
        assert(!levels.empty() && levels[0].row < levels[0].n);
        return next_argmin(0);
    }

    // r <- 0; A may be changed before the next sequence of queries.
    void reset() {
        for (auto& a : levels) a.row = a.state = a.size = 0;
    }
};

}  // namespace detail
}  // namespace po167
