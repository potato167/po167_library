#pragma once
#include <vector>
#include <cassert>

namespace po167{
template<class T>
std::vector<T> make_inv_vector(int N){
    std::vector<T> fact(1 + N, 1);
    std::vector<T> inv(1 + N, 1);
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i;
    T tmp = 1;
    tmp = tmp / fact[N];
    for (int i = N; i >= 1; i--){
        inv[i] = tmp * fact[i - 1];
        tmp = tmp * i;
    }
    return inv;
}
template<class T>
std::vector<std::pair<int, T>> pick_value(std::vector<T> f){
    std::vector<std::pair<int, T>> res;
    for (int i = 0; i < (int)(f.size()); i++){
        if (f[i] != 0){
            res.push_back({i, f[i]});
        }
    }
    return res;
}

// f に定数項がないときの返り値はエラーを起こします。
template<class T>
std::vector<T> FPS_sparse_inv(std::vector<T> f, int m = -1){
    if (m < 0) m = (int)f.size();
    if (m == 0) return {};
    assert(!f.empty() && f[0] != 0);
    std::vector<T> res(m);
    T inv = (T)(1) / f[0];
    res[0] = inv;
    auto p = pick_value(f);
    for (int i = 1; i < m; i++){
        for (auto [a, b] : p) if (a != 0 && a <= i){
            res[i] -= b * res[i - a];
        }
        res[i] *= inv;
    }
    return res;
}

/*
 * return F = log(f)
 * F' = (1 / f) f'
 * s.t f[0] == 1
 */
template<class T>
std::vector<T> FPS_sparse_log(std::vector<T> f, int m = -1) {
    if (m == -1) m = (int)f.size();
    if (m == 0) return {};
    assert(!f.empty() && f[0] == 1);
    auto inv = FPS_sparse_inv(f, m - 1);
    // f <- f'
    for (int i = 1; i < (int)f.size(); i++){
        f[i - 1] = f[i] * i;
    }
    f.pop_back();
    std::vector<T> res(m - 1);
    for (int i = 0; i < (int)f.size(); i++) if (f[i] != 0){
        for (int j = 0; j < m - 1 - i; j++){
            res[j + i] += inv[j] * f[i];
        }
    }
    inv = make_inv_vector<T>(m);
    res.push_back(0);
    for (int i = m - 1; i > 0; i--){
        res[i] = res[i - 1] * inv[i];
    }
    res[0] = 0;
    return res;
}

/*
 * return F = exp(f)
 * F' = f'F
 * s.t f[0] = 0
 */
template<class T>
std::vector<T> FPS_sparse_exp(std::vector<T> f, int m = -1){
    if (m == -1) m = (int)f.size();
    if (m == 0) return {};
    if (f.empty()){
        std::vector<T> res(m, 0);
        res[0] = 1;
        return res;
    }
    assert(f[0] == 0);
    auto p = pick_value(f);
    std::vector<T> res(m);
    res[0] = 1;
    auto inv = make_inv_vector<T>(m + 1);
    for (int i = 1; i < m; i++){
        for (auto [a, b] : p){
            if (a <= i){
                res[i] += b * res[i - a] * a;
            }
        }
        res[i] *= inv[i];
    }
    return res;
}
/*
 * return F = f^n
 * F' = n * f^{n - 1} * f'
 * fF' = n * F * f'
 *
 */
template<class T>
std::vector<T> FPS_sparse_pow(std::vector<T> f, long long n, int m = -1){
    if (m == -1) m = (int)f.size();
    if (m == 0) return {};
    if (n == 0){
        std::vector<T> res(m, 0);
        res[0] = 1;
        return res;
    }
    int non_zero_ind = -1;
    for (int i = 0; i < (int)f.size(); i++){
        if (f[i] != 0){
            non_zero_ind = i;
            break;
        }
    }
    // a * b >= c
    // b >= c / a
    if (non_zero_ind == -1
    || (non_zero_ind != 0 && (n > m / (long long)(non_zero_ind) || (long long)(non_zero_ind) * n >= m))){
        std::vector<T> res(m, 0);
        return res;
    }
    if (non_zero_ind){
        assert(n >= 0);
        std::vector<T> nf((int)(f.size()) - non_zero_ind * n);
        for (int i = non_zero_ind; i < (int)(f.size()); i++){
            if (i - non_zero_ind < (int)nf.size()) nf[i - non_zero_ind] = f[i];
        }
        auto tmp = FPS_sparse_pow(nf, n, m - non_zero_ind * n);
        std::vector<T> res(m, 0);
        for (int i = 0; i < (int)tmp.size(); i++){
            res[i + non_zero_ind * n] = tmp[i];
        }
        return res;
    }
    std::vector<T> res(m, 0);
    // f[0] は pow で求める
    {
        res[0] = 1;
        long long tmp = n;
        T v = f[0];
        if (n < 0){
            tmp = -tmp;
            v = (T)(1) / v;
        }
        while (tmp){
            if (tmp & 1) res[0] *= v;
            v = v * v;
            tmp /= 2;
        }
    }
    T inv = (T)(1) / f[0];
    auto invs = make_inv_vector<T>(m);
    // fF' = n * F * f'
    auto p = pick_value(f);
    for (int i = 1; i < m; i++){
        for (auto [a, b] : p) if (a != 0){
            if (a <= i){
                res[i] += b * (T)(a) * res[i - a] * (T)(n);
            }
            if (a < i){
                res[i] -= b * res[i - a] * (T)(i - a);
            }
        }
        res[i] *= inv;
        res[i] *= invs[i];
    }
    return res;
}
}