#pragma once
#include <atcoder/convolution>

namespace po167{
// n = |g|
// return f(g(x))
// https://maspypy.com/fps-合成・逆関数の解説（2）転置原理による合成ア
template<class T>
std::vector<T> FPS_comp(std::vector<T> f, std::vector<T> g){
    assert(g[0] == 0);
    auto rec = [&](auto rec, int n, int k, std::vector<T> Q) -> std::vector<T> {
        if (n == 1){
            std::vector<T> p(2 * k);
            std::reverse(f.begin(), f.end());
            for (int i = 0; i < k; i++) p[2 * i] = f[i];
            return p;
        }
        std::vector<T> nxt_Q(2 * n * k);
        for (int i = 0; i < n * k; i++) nxt_Q[n * k + i] += Q[i * 2] * 2;
        Q.resize(4 * n * k);
        atcoder::internal::butterfly(Q);
        // Q(-x)
        std::vector<T> R(4 * n * k);
        for (int i = 0; i < 2 * n * k; i++){
            R[i * 2] = Q[i * 2 + 1];
            R[i * 2 + 1] = Q[i * 2];
        }
        T iz = (T)(1) / (T)(4 * n * k);
        for (int i = 0; i < 4 * n * k; i++) Q[i] *= R[i];
        for (int i = 0; i < 2 * n * k; i++) Q[i] = Q[i * 2];
        Q.resize(2 * n * k);
        atcoder::internal::butterfly_inv(Q);
        for (int i = 0; i < 2 * n * k; i++) nxt_Q[i] += Q[i] * iz * 2;
        for (int j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){
            nxt_Q[n * j + i] = 0;
        }
        std::vector<T> pq = rec(rec, n / 2, k * 2, nxt_Q);
        std::vector<T> p(2 * n * k);
        for (int j = 0; j < 2 * k; j++) for (int i = n / 2; i < n; i++){
            pq[n * j + i] = 0;
        }
        for (int i = 0; i < n * k; i++) p[i * 2 + 1] += pq[n * k + i];
        std::reverse(pq.begin(), pq.end());
        atcoder::internal::butterfly(pq);
        pq.resize(4 * n * k);
        for (int i = 2 * n * k - 1; i >= 0; i--){
            pq[i * 2 + 1] = pq[i];
            pq[i * 2] = pq[i];
        }
        for (int i = 0; i < 4 * n * k; i++) pq[i] *= R[i];
        atcoder::internal::butterfly_inv(pq);
        for (int i = 0; i < 2 * n * k; i++) p[i] += pq[4 * n * k - 1 - i] * iz;
        return p;
    };
    int N = (int)g.size();
    int n = 1;
    while (n < N) n *= 2;
    f.resize(n, 0);
    g.resize(n, 0);
    std::vector<T> Q(2 * n);
    for (int i = 0; i < n; i++) Q[i] = -g[i];
    auto p = rec(rec, n, 1, Q);
    std::vector<T> res(n);
    for (int i = 0; i < n; i++) res[i] = p[i];
    std::reverse(res.begin(), res.end());
    res.resize(N);
    return res;
}
}