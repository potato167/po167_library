#pragma once

#include "Binomial.hpp"

namespace po167{
template<class T>
struct q_Binomial{
    std::vector<T> q_pow, q_sum, fact_vec, fact_inv_vec;
    T q;
    int lim;
    int mod;
    Binomial<T> table;
    q_Binomial(int q_, int mod_, int lim_ = 10'000'100){
        q = q_;
        mod = mod_;
        lim = lim_;
        table.extend(std::min(lim + 1, mod));
        q_pow.resize(lim, T(1));
        q_sum.resize(lim, T(0));
        for (int i = 1; i < lim; i++){
            q_pow[i] = q_pow[i - 1] * q;
            q_sum[i] = q_sum[i - 1] + q_pow[i - 1];
            if (q_pow[i] == 1){
                lim = i;
                q_pow.resize(lim);
                q_sum.resize(lim);
                break;
            }
        }
        fact_vec.resize(lim, T(1));
        fact_inv_vec.resize(lim, T(1));
        for (int i = 1; i < lim; i++){
            fact_vec[i] = fact_vec[i - 1] * q_sum[i];
        }
        fact_inv_vec.back() = (T)(1) / (T)(fact_vec.back());
        for (int i = lim - 1; i > 0; i--){
            fact_inv_vec[i - 1] = fact_inv_vec[i] * q_sum[i];
        }
    }
    T fact(long long i){
        if (i < 0 || lim <= i) return 0;
        return fact_vec[i];
    }
    T invfact(long long i){
        if (i < 0 || lim <= i) return 0;
        return fact_inv_vec[i];
    }
    T aCb(long long a, long long b){
        if (a < b || b < 0) return 0;
        if (a < mod) return table.C(a, b);
        return table.C(a % mod, b % mod) * aCb(a / mod, b / mod);
    }
    T C(long long a, long long b){
        if (a < b || b < 0) return 0;
        if (a < lim) return fact(a) * invfact(b) * invfact(a - b);
        return C(a % lim, b % lim) * aCb(a / lim, b / lim);
    }
};
}
