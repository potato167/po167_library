#pragma once

#include <atcoder/convolution>
#include "../math/Binomial.hpp"

namespace po167{
// return f(x + c)
template<class T>
std::vector<T> Taylor_Shift(
    std::vector<T> f, T c
){
    int n = f.size();
    Binomial<T> table(n);
    std::vector<T> g(n);
    T tmp = 1;
    for (int i = 0; i < n; i++){
        g[n - 1 - i] = table.invfact(i) * tmp;
        tmp *= c;
        f[i] *= table.fact(i);
    }
    // using cyclic convolution is faster ? 
    g = atcoder::convolution(f, g);
    std::vector<T> res(n);
    for (int i = 0; i < n; i++){
        res[i] = table.invfact(i) * g[n + i - 1];
    }
    return res;
}
}