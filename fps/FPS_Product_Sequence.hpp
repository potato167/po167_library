#pragma once
#include <vector>
#include <atcoder/convolution>

namespace po167{
template<class T>
std::vector<T> FPS_Product_Sequence(std::vector<std::vector<T>> f){
    if (f.empty()) return {1};
    auto op = [&](auto self,int l, int r) -> std::vector<T> {
        if (l + 1 == r) return f[l];
        int m = (l + r) / 2;
        return atcoder::convolution(self(self, l, m), self(self, m, r));
    };
    return op(op, 0, f.size());
}
}