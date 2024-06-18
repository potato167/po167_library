#pragma once
#include <vector>
#include <atcoder/convolution>

namespace po167{
// in  : DFT(v) (len(v) = z)
// out : DFT(v) (len(v) = 2 * z)
template<class T>
void FPS_extend(std::vector<T> &v){
    int z = v.size();
    T e = (T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod() / (2 * z));
    auto cp = v;
    atcoder::internal::butterfly_inv(cp);
    T tmp = (T)(1) / (T)(z);
    for (int i = 0; i < z; i++){
        cp[i] *= tmp;
        tmp *= e;
    }
    atcoder::internal::butterfly(cp);
    for (int i = 0; i < z; i++) v.push_back(cp[i]);
};
}