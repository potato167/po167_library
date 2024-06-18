#pragma once
#include <vector>
#include <atcoder/convolution>
#include "../fps/FPS_cyclic_convolution.hpp"
#include "../fps/FPS_differetial.hpp"
#include "../fps/FPS_integral.hpp"
#include "FPS_inv.hpp"

namespace po167{
template<class T>
std::vector<T> FPS_exp(std::vector<T> f, int len = -1){
    if (len == -1) len = f.size();
    if (len == 0) return {};
    if (len == 1) return {T(1)};
    assert(!f.empty() && f[0] == 0);
    int s = 1;
    // simple
    std::vector<T> g = {T(1)};
    while (s < len){
        // g' / g
        // A * B
        std::vector<T> A = g, B = g;
        A = FPS_differential(A);
        B = FPS_inv(B, 2 * s);
        A.resize(2 * s);
        A = FPS_cyclic_convolution(A, B);
        A.pop_back();
        A = FPS_integral(A);
        for (int i = 0; i < s; i++) A[i] = 0;
        for (int i = s; i < s * 2; i++) A[i] = (i < (int)f.size() ? f[i] : 0) - A[i];
        // g_hat = g (1 - g + f)
        // g += B = g * A
        g.resize(2 * s);
        B = FPS_cyclic_convolution(A, g);
        for (int i = s; i < s * 2; i++) g[i] = B[i];
        s *= 2;
    }
    g.resize(len);
    return g;
}
}