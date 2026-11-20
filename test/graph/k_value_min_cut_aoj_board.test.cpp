#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2903"

#include "graph/KValueMinCut.hpp"
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int r, c;
    std::cin >> r >> c;
    std::vector<std::string> board(r);
    for (auto& row : board) std::cin >> row;

    // A hole is covered vertically when v = 0, horizontally when v = 1.
    po167::KValueMinCut<> cut(std::vector<int>(r * c, 2));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (board[i][j] != '#') continue;
            int u = i * c + j;
            cut.add_linear(u, 0, 1);
            // Joining two adjacent tiles of the same direction saves one tile.
            if (i + 1 < r && board[i + 1][j] == '#') {
                cut.add_lt_lt(u, 1, u + c, 1, 1);
            }
            if (j + 1 < c && board[i][j + 1] == '#') {
                cut.add_ge_ge(u, 1, u + 1, 1, 1);
            }
        }
    }
    std::cout << cut.run().first << '\n';
}
