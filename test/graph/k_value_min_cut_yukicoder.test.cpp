#define PROBLEM "https://yukicoder.me/problems/no/119"

#include "graph/KValueMinCut.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    po167::KValueMinCut<long long> cut(std::vector<int>(n, 3));
    long long inf = 1;
    for (int i = 0; i < n; i++) {
        long long b, c;
        std::cin >> b >> c;
        // 0: visit without a tour, 1: do not visit, 2: join the tour.
        cut.add_eq(i, 0, -c);
        cut.add_eq(i, 2, -b);
        inf += std::max(b, c);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int d, e;
        std::cin >> d >> e;
        // Joining d's tour forbids visiting e without joining its tour.
        cut.add_lt_ge(e, 1, d, 2, inf);
    }
    std::cout << -cut.run().first << '\n';
}
