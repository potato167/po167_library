#pragma once
#include <vector>
#include <algorithm>
#include "smawk.hpp"

namespace po167{
// X is convex upward
template<class T>
std::vector<T> sum_max_convolution(std::vector<T> X, std::vector<T> Y){
    int n = X.size();
    int m = Y.size();
    std::vector<T> ans(n + m - 1);
    auto get = [&](int i, int j) -> T {
        return X[i - j] + Y[j];
    };
    auto select = [&](int i, int j1, int j2) -> bool {
        if (i < j2) return false;
        if (i - j1 >= n) return true;
        return get(i, j1) <= get(i, j2);
    };
    const int D = 10;
    if (std::min(n, m) <= D) {
        for (int i = 0; i < n + m - 1; i++){
            int ind = std::max(0, i - n);
            for (int j = ind + 1; j < m && j <= i; j++){
                if (select(i, ind, j)) ind = j;
            }
            ans[i] = get(i, ind);
        }
        return ans;
    }
    std::vector<int> res = smawk(n + m - 1, m, select);
    for (int i = 0; i < n + m - 1; i++){
        ans[i] = get(i, res[i]);
    }
    return ans;
}
}