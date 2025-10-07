#pragma once
#include<atcoder/convolution>
namespace po167
{
template<class T>
// input A(x)
// B(x) = 1 / A(x)
// return {B[l], B[l + 1], ... , B[r - 1]}
// 0 < r
std::vector<T> FPS_Inv_Consecutive(long long l, long long r, std::vector<T> A){
    assert(0 < r);
    if (l >= r) return {};
    if (r == 1){
        std::vector<T> res(r - l, 0);
        res.back() = (T)(1) / (T)(A[0]);
        return res;
    }
    int d = A.size();
    std::vector<T> nA(d);
    for (int i = 0; i < d; i++){
        nA[i] = A[i] * (1 - 2 * (i & 1));
    }
    auto C = atcoder::convolution(nA, A);
    std::vector<T> nC(d);
    for (int i = 0; i < d; i++) nC[i] = C[i * 2];
    // calc [l - d + 1, r) 1 / C
    // calc [(l - d + 1) / 2, r / 2) 1 / nC
    long long nl = std::max(0ll, (l - d) / 2);
    long long nr = (r + 1) / 2;
    auto D = FPS_Inv_Consecutive(nl, nr, nC);
    std::vector<T> nD(2 * (int)D.size());
    for (int i = 0; i < (int)D.size(); i++){
        nD[i * 2] = D[i];
    }
    auto B = atcoder::convolution(nD, nA);
    std::vector<T> res(r - l);
    for (long long i = l; i < r; i++){
        if (i >= 0) res[i - l] = B[i - nl * 2];
    }
    return res;
}
template<class T>
// 0 = a[i] * c[0] + a[i - 1] * c[1] + a[i - 2] * c[2] + ... + a[i - d] * c[d]
// a.size() + 1 == c.size()
// almost c[0] = - 1 
// return {a[l], a[l + 1], ... , a[r - 1]}
std::vector<T> Consecutive_Linear(long long l, long long r, std::vector<T> a, std::vector<T> c){
    int d = a.size();
    assert(d + 1 == int(c.size()));
    std::vector<T> P = atcoder::convolution(a, c);
    P.resize(d);
    std::vector<T> Q = FPS_Inv_Consecutive(l - d, r, c);
    P = atcoder::convolution(P, Q);
    for (int i = 0; i < r - l; i++){
        P[i] = P[i + d];
    }
    P.resize(r - l);
    return P;
}
} // namespace po167