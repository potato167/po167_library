#pragma once
#include <vector>
#include "../fps/FPS_exp.hpp"
#include "../fps/FPS_log.hpp"
#include "../fps/FPS_Power_Projection.hpp"

namespace po167{
// return g
// g(f) = x
// [x ^ 0] f  = 0
// [x ^ 1] f != 0
template<class T>
std::vector<T> FPS_inverse(std::vector<T> f, int len = -1){
    if (len == -1) len = f.size();
    if (len == 0) return {};
    if (len == 1) return {(T)(0)};
    assert((int)f.size() >= 2);
    assert(f[0] == 0);
    assert(f[1] != 0);
    T c = (T)(1) / f[1];
    for (auto &x : f) x *= c;
    std::vector<T> inv_num(len + 1, 1);
    for (int i = 2; i <= len; i++){
        inv_num[i] = (0 - inv_num[T::mod() % i]) * (T::mod() / i);
    }
    f.resize(len);
    std::vector<T> p(len);
    p[0] = 1;
    p = Power_Projection(p, f, len);
    std::vector<T> g(len - 1);
    for (int i = 1; i < len; i++){
        g[len - 1 - i] = p[i] * (T)(len - 1) * inv_num[i];
    }
    g = FPS_log(g);
    for (int i = 0; i < len - 1; i++){
        g[i] *= (T)(-1) * inv_num[len - 1];
    }
    g = FPS_exp(g);
    g.insert(g.begin(), 0);
    T v = 1;
    for (auto &x : g) x *= v, v *= c;
    return g;
}

}