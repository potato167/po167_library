#pragma once
#include <vector>
#include <atcoder/convolution>
#include <cassert>
#include "FPS_extend.hpp"
#include "FPS_pick_even_odd.hpp"

namespace po167{
// return [x^k] P(x) / Q(x)
template<class T>
T Boston_Mori(long long k, std::vector<T> P, std::vector<T> Q){
    assert(!Q.empty() && Q[0] != 0);
    int z = 1;
    while (z < (int)std::max(P.size(), Q.size())) z *= 2;
    P.resize(z * 2, 0);
    Q.resize(z * 2, 0);
    atcoder::internal::butterfly(P);
    atcoder::internal::butterfly(Q);

    // fast
    while (k){
        // Q(-x)
        std::vector<T> Q_n(z * 2);
        for (int i = 0; i < z; i++){
            Q_n[i * 2] = Q[i * 2 + 1];
            Q_n[i * 2 + 1] = Q[i * 2];
        }
        for (int i = 0; i < z * 2; i++){
            P[i] *= Q_n[i];
            Q[i] *= Q_n[i];
        }
        FPS_pick_even_odd(P, k & 1);
        FPS_pick_even_odd(Q, 0);
        k /= 2;
        if (k == 0) break;
        FPS_extend(P);
        FPS_extend(Q);
    }
    T SP = 0, SQ = 0;
    for (int i = 0; i < z; i++) SP += P[i], SQ += Q[i];
    return SP / SQ;

    // simple
    /*
    while (k){
        auto n_Q = Q;
        for (int i = 0; i < int(Q.size()); i++){
            if (i & 1) n_Q[i] *= -1;
        }
        auto n_P = atcoder::convolution(P, n_Q);
        n_Q = atcoder::convolution(Q, n_Q);
        for (int i = 0; i < int(Q.size()); i++){
            Q[i] = n_Q[i * 2];
        }
        P.clear();
        for (int i = (k & 1); i < int(n_P.size()); i += 2){
            P.push_back(n_P[i]);
        }
        k >>= 1;
    }
    return P[0] / Q[0];
    */
}

template<class T>
// 0 = a[i] * c[0] + a[i - 1] * c[1] + a[i - 2] * c[2] + ... + a[i - d] * c[d]
// a.size() + 1 == c.size()
// c[0] = - 1 ?
// return a[k]
T Kth_Linear(long long k, std::vector<T> a, std::vector<T> c){
    int d = a.size();
    assert(d + 1 == int(c.size()));
    std::vector<T> P = atcoder::convolution(a, c);
    P.resize(d);
    return Boston_Mori(k, P, c);
}
};