#pragma once
#include <vector>
#include <atcoder/convolution>

namespace po167{
// return 1 / f
template <class T>
std::vector<T> FPS_inv(std::vector<T> f, int len = -1){
    if (len == -1) len = f.size();
    assert(f[0] != 0);
    std::vector<T> g = {1 / f[0]};
    int s = 1;
    while(s < len){
        // g = 2g_s - f(g_s)^2 (mod x ^ (2 * s))
        // g = g - (fg - 1)g
        // (fg - 1) = 0 (mod x ^ (s))
        std::vector<T> n_g(s * 2, 0);
        std::vector<T> f_s(s * 2, 0);
        g.resize(s * 2);
        for (int i = 0; i < s * 2; i++){
            if (int(f.size()) > i) f_s[i] = f[i];
            n_g[i] = g[i];
        }
        atcoder::internal::butterfly(g);
        atcoder::internal::butterfly(f_s);
        for (int i = 0; i < s * 2; i++){
            f_s[i] *= g[i];
        }
        atcoder::internal::butterfly_inv(f_s);
        T iz = 1 / (T)(s * 2);
        for (int i = s; i < s * 2; i++){
            f_s[i] *= iz;
        }
        for (int i = 0; i < s; i++){
            f_s[i] = 0;
        }
        atcoder::internal::butterfly(f_s);
        for (int i = 0; i < s * 2; i++){
            f_s[i] *= g[i];
        }
        atcoder::internal::butterfly_inv(f_s);
        for (int i = s; i < s * 2; i++){
            n_g[i] -= f_s[i] * iz;
        }
        std::swap(n_g, g);
        s *= 2;
    }
    g.resize(len);
    return g;
}
}