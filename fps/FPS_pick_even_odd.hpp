#pragma once
#include <vector>

namespace po167{
// s.t |v| = 2 ^ s (no assert)
template<class T>
void FPS_pick_even_odd(std::vector<T> &v, int odd){
    int z = v.size() / 2;
    T half = (T)(1) / (T)(2);
    if (odd == 0){
        for (int i = 0; i < z; i++){
            v[i] = (v[i * 2] + v[i * 2 + 1]) * half;
        }
        v.resize(z);
    } else {
        T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod() / (2 * z));
        T ie = T(1) / e;
        std::vector<T> es = {half};
        while ((int)es.size() != z){
            std::vector<T> n_es((int)es.size() * 2);
            for (int i = 0; i < (int)es.size(); i++){
                n_es[i * 2] = (es[i]);
                n_es[i * 2 + 1] = (es[i] * ie);
            }
            ie *= ie;
            std::swap(n_es, es);
        }
        for (int i = 0; i < z; i ++){
            v[i] = (v[i * 2] - v[i * 2 + 1]) * es[i];
        }
        v.resize(z);
    }
}
}