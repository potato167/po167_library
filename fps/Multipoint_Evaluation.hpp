#pragma once
#include <atcoder/convolution>
#include "po167_library/fps/FPS_division.hpp"

namespace po167{
template <class T>
// return {f(p[0]), f(p[1]), f(p[2]), ... }
std::vector<T> Multipoint_Evaluation(
    std::vector<T> f,
    std::vector<T> p
){
    int m = p.size();
    if (m == 0) return {};
    if (m == 1){
        T res = 0;
        T tmp = 1;
        for (auto x : f) res += tmp * x, tmp *= p[0];
        return {res};
    }
    int size = 1;
    while (size < m) size *= 2;
    std::vector<std::vector<T>> prod(size * 2);
    for (int i = 0; i < size; i++){
        if (i < m) prod[i + size] = {(T)(-1) * p[i], 1};
        else prod[i + size] = {1};
    }
    for (int i = size - 1; i > 0; i--){
        prod[i] = atcoder::convolution(prod[i * 2], prod[i * 2 + 1]);
    }
    std::vector<T> res(m);
    auto calc = [&](auto self, int l, int r, int ind, std::vector<T> tmp) -> void {
        if (m <= l) return;
        if (l + 1 == r){
            res[l] = tmp[0];
            return;
        }
        int mid = (l + r) / 2;
        self(self, l, mid, ind * 2, po167::FPS_division(tmp, prod[ind * 2]).second);
        self(self, mid, r, ind * 2 + 1, po167::FPS_division(tmp, prod[ind * 2 + 1]).second);
    };calc(calc, 0, size, 1, f);
    return res;
}
}