#pragma once

#include<vector>
#include<assert.h>

namespace po167{
template<class T>
struct Binomial{
    std::vector<T> fact_vec, fact_inv_vec;
    void extend(int m = -1){
        int n = fact_vec.size();
        if (m == -1) m = n * 2;
        if (n >= m) return;
        fact_vec.resize(m);
        fact_inv_vec.resize(m);
        for (int i = n; i < m; i++){
            fact_vec[i] = fact_vec[i - 1] * T(i);
        }
        fact_inv_vec[m - 1] = T(1) / fact_vec[m - 1];
        for (int i = m - 1; i > n; i--){
            fact_inv_vec[i - 1] = fact_inv_vec[i] * T(i);
        }
    }
    Binomial(int MAX = 0){
        fact_vec.resize(1, T(1));
        fact_inv_vec.resize(1, T(1));
        extend(MAX + 1);
    }

    T fact(int i){
        if (i < 0) return 0;
        while (int(fact_vec.size()) <= i) extend();
        return fact_vec[i];
    }
    T invfact(int i){
        if (i < 0) return 0;
        while (int(fact_inv_vec.size()) <= i) extend();
        return fact_inv_vec[i];
    }
    T C(int a, int b){
        if (a < b || b < 0) return 0;
        return fact(a) * invfact(b) * invfact(a - b);
    }
    T invC(int a, int b){
        if (a < b || b < 0) return 0;
        return fact(b) * fact(a - b) *invfact(a);
    }
    T P(int a, int b){
        if (a < b || b < 0) return 0;
        return fact(a) * invfact(a - b);
    }
    T inv(int a){
        if (a < 0) return inv(-a) * T(-1);
        if (a == 0) return 1;
        return fact(a - 1) * invfact(a);
    }
    T Catalan(int n){
        if (n < 0) return 0;
        return fact(2 * n) * invfact(n + 1) * invfact(n);
    }
    T narayana(int n, int k){
        if (n <= 0 || n < k || k < 1) return 0;
        return C(n, k) *  C(n, k - 1) * inv(n);
    }
    T Catalan_pow(int n,int d){
        if (n < 0 || d < 0) return 0;
        if (d == 0){
            if (n == 0) return 1;
            return 0;
        }
        return T(d) * inv(d + n) * C(2 * n + d - 1, n);
    }
    // retrun [x^a] 1/(1-x)^b
    T ruiseki(int a,int b){
        if (a < 0 || b < 0) return 0;
        if (a == 0){
            return 1;
        }
        return C(a + b - 1, b - 1);
    }
    // (a, b) -> (c, d)
    // always x + e >= y
    T mirror(int a, int b, int c, int d, int e = 0){
        if (a + e < b || c + e < d) return 0;
        if (a > c || b > d) return 0;
        a += e;
        c += e;
        return C(c + d - a - b, c - a) - C(c + d - a - b, c - b + 1); 
    }
    // return sum_{i = 0, ... , a} sum_{j = 0, ... , b} C(i + j, i)
    // return C(a + b + 2, a + 1) - 1;
    T gird_sum(int a, int b){
        if (a < 0 || b < 0) return 0;
        return C(a + b + 2, a + 1) - 1;
    }
    // return sum_{i = a, ..., b - 1} sum_{j = c, ... , d - 1} C(i + j, i)
    // AGC 018 E
    T gird_sum_2(int a, int b, int c, int d){
        if (a >= b || c >= d) return 0;
        a--, b--, c--, d--;
        return gird_sum(a, c) - gird_sum(a, d) - gird_sum(b, c) + gird_sum(b, d);
    }

    // the number of diagonal dissections of a convex n-gon into k+1 regions.
    // OEIS A033282
    // AGC065D
    T diagonal(int n, int k){
        if (n <= 2 || n - 3 < k || k < 0) return 0;
        return C(n - 3, k) * C(n + k - 1, k) * inv(k + 1);
    }
};
}
