#pragma once
#include <vector>
#include <atcoder/convolution>

namespace po167{
// |f| = |g| = 2 ^ n
template<class T>
std::vector<T> FPS_cyclic_convolution(std::vector<T> f, std::vector<T> g){
    atcoder::internal::butterfly(f);
    atcoder::internal::butterfly(g);
    for (int i = 0; i < (int)f.size(); i++) f[i] *= g[i];
    atcoder::internal::butterfly_inv(f);
    T iz = (T)(1) / (T)(f.size());
    for (int i = 0; i < (int)f.size(); i++) f[i] *= iz;
    return f;
}
}