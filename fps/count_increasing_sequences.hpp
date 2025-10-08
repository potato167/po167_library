#pragma once
#include <atcoder/convolution>
#include "../math/Binomial.hpp"
#include "FPS_cyclic_convolution.hpp"
namespace po167{
template<class T>
std::pair<std::vector<T>, std::vector<T>> count_square(std::vector<T> L, std::vector<T> D){
    assert(!L.empty() && !D.empty());
    int N = L.size();
    int M = D.size();
    po167::Binomial<T> table(N + M);
    std::vector<T> R(N), U(M);
    int z = 0;
    while ((1 << z) < (N + M - 1)) z++;
    // 左から右
    {
        std::vector<T> tmp(N);
        for (int i = 0; i < N; i++) tmp[i] = table.C(M - 1 + i, i);
        tmp = atcoder::convolution(tmp, L);
        for (int i = 0; i < N; i++) R[i] += tmp[i];
    }
    // 左から上
    {
        std::vector<T> tmp(1 << z);
        for (int i = 0; i < N; i++) L[i] *= table.invfact(N - 1 - i);
        for (int i = 0; i < N + M - 1; i++) tmp[i] = table.fact(i);
        L.resize(1 << z, 0);
        tmp = po167::FPS_cyclic_convolution(tmp, L);
        for (int i = 0; i < M; i++) U[i] += tmp[N - 1 + i] * table.invfact(i);
    }
    // 下から上
    {
        std::vector<T> tmp(M);
        for (int i = 0; i < M; i++) tmp[i] = table.C(N - 1 + i, i);
        tmp = atcoder::convolution(tmp, D);
        for (int i = 0; i < M; i++) U[i] += tmp[i];
    }
    // 下から右
    {
        std::vector<T> tmp(1 << z);
        for (int i = 0; i < M; i++) D[i] *= table.invfact(M - i - 1);
        for (int i = 0; i < N + M - 1; i++) tmp[i] = table.fact(i);
        D.resize(1 << z, 0);
        tmp = po167::FPS_cyclic_convolution(tmp, D);
        for (int i = 0; i < N; i++) R[i] += tmp[M - 1 + i] * table.invfact(i);
    }
    return {R, U};
}
template<class T>
/*
 * g(A, x) を
 * 0 <= B[i] < A[i] かつ B[i] = x を満たす
 * 広義単調増加列 B の数とする
 * res[x] = sum C[i] * g(A[i:N], x)
 * を返す
 */
std::vector<T> count_increase_sequences_with_upper_bounds(std::vector<int> A, std::vector<T> C){
    int N = A.size();
    assert((int)C.size() == N);
    assert(N);
    for (int i = (int)(A.size()) - 1; i > 0; i--) A[i - 1] = std::min(A[i - 1], A[i]);
    if (A.back() == 0) return {};
    if (N == 1){
        std::vector<T> res(A[0]);
        for (int i = 0; i < A[0]; i++) res[i] = C[0];
        return res;
    }
    int m = N / 2;
    std::vector<int> LA(m), RA(N - m);
    std::vector<T> LC(m), RC(N - m);
    for (int i = 0; i < m; i++){
        LA[i] = A[i];
        LC[i] = C[i];
    }
    for (int i = 0; i < N - m; i++){
        RA[i] = A[i + m] - A[m - 1];
        RC[i] = C[i + m];
    }
    std::vector<T> res;
    res.reserve(A.back());
    auto L = count_increase_sequences_with_upper_bounds(LA, LC);
    if (!L.empty()){
        auto [R, U] = count_square(L, RC);
        for (int i = 0; i < (int)R.size(); i++) res.push_back(R[i]);
        std::swap(U, RC);
    }
    auto R = count_increase_sequences_with_upper_bounds(RA, RC);
    for (auto x : R) res.push_back(x);
    return res;
}
template<class T>
std::vector<T> NAIVE_count_increase_sequences_with_upper_lower_bounds(std::vector<int> A, std::vector<int> B, std::vector<T> C = {}){
    std::vector<T> tmp(B.back() - A[0]);
    if (C.empty()){
        int b = B[0];
        for (int i = 1; i < (int)B.size(); i++) b = std::min(b, B[i]);
        for (int i = 0; i < b - A[0]; i++) tmp[i] = 1;
    }
    else for (int i = 0; i < (int)std::min(tmp.size(), C.size()); i++) tmp[i] = C[i];
    int N = A.size();
    for (int i = 1; i < N; i++){
        for (int j = 1; j < (int)tmp.size(); j++){
            tmp[j] += tmp[j - 1];
        }
        for (int j = 0; j < (int)tmp.size(); j++){
            if (j < A[i] - A[0] || B[i] - A[0] <= j) tmp[j] = 0;
        }
    }
    std::vector<T> res(B.back() - A.back());
    for (int i = 0; i < B.back() - A.back(); i++){
        res[i] = tmp[A.back() - A[0] + i];
    }
    return res;
}

template<class T>
/*
 * f(a, b) を X[0] = a, X[N - 1] = b であるような、A, B に挟まれたものとする
 * res[b] = sum C[a - A[0]] * f(a, b)
 */
std::vector<T> count_increase_sequences_with_upper_lower_bounds(std::vector<int> A, std::vector<int> B, std::vector<T> C = {}){
    int N = A.size();
    assert(A.size() == B.size());
    for (int i = 0; i < N - 1; i++){
        A[i + 1] = std::max(A[i], A[i + 1]);
    }
    for (int i = N - 1; i > 0; i--){
        B[i - 1] = std::min(B[i], B[i - 1]);
    }
    if (A.back() >= B.back()) return {};
    // A[0] == 0 にする
    std::vector<T> res(B.back() - A.back(), 0);
    {
        int tmp = A[0];
        for (int i = 0; i < N; i++){
            A[i] -= tmp;
            B[i] -= tmp;
            if (A[i] >= B[i]) return res;
        }
    }
    if (C.empty()){
        C.resize(B[0] - A[0], 1);
    }
    else assert((int)(C.size()) == B[0] - A[0]);
    int l = 0;
    while (B[l] <= A.back()){
        for (int i = (int)(C.size()) - 1; i > 0; i--) C[i] -= C[i - 1];
        int nl = l;
        while (A[nl] < B[l]) nl++;
        std::vector<int> tmp(B[l] - A[l]);
        tmp[0] = 1;
        for (int i = l; i < nl; i++){
            tmp[A[i] - A[l]]++;
        }
        for (int i = 1; i < B[l] - A[l]; i++) tmp[i] += tmp[i - 1];
        auto X = count_increase_sequences_with_upper_bounds(tmp, C);
        std::vector<int> nB(nl - l + 1);
        for (int i = l; i <= nl; i++){
            nB[i - l] = B[i] - B[l];
        }
        auto Y = count_increase_sequences_with_upper_bounds(nB, X);
        C.resize(B[nl] - A[nl]);
        for (int i = 0; i < B[nl] - A[nl]; i++){
            C[i] = Y[i + A[nl] - B[l]];
        }
        l = nl;
    }
    // A を揃えてしまえ
    {
        int a = A[l];
        for (int i = l; i < N; i++){
            A[i] -= a;
            B[i] -= a;
        }
    }
    for (int i = (int)(C.size()) - 1; i > 0; i--) C[i] -= C[i - 1];
    std::vector<T> D(N - l, 0);
    if (A.back() != 0){
        std::vector<T> L(A.back());
        for (int i = 0; i < (int)L.size(); i++) L[i] = C[i];
        std::vector<int> tmp(L.size());
        tmp[0] = 1;
        for (int i = l; i < N; i++){
            if (A[i] < (int)tmp.size()) tmp[A[i]]++;
        }
        for (int i = 1; i < (int)tmp.size(); i++){
            tmp[i] += tmp[i - 1];
        }
        auto nD = count_increase_sequences_with_upper_bounds(tmp, L);
        for (int i = 0; i < (int)nD.size(); i++) D[i] = nD[i];
    }
    for (int i = A.back(); i < B[l]; i++) C[i - A.back()] = C[i];
    C.resize(B[l] - A.back());
    auto [R, U] = count_square(C, D);
    res = R;
    std::vector<int> nB(N - l);
    for (int i = 0; i < N - l; i++) nB[i] = B[i + l] - B[l];
    R = count_increase_sequences_with_upper_bounds(nB, U);
    for (auto x : R) res.push_back(x);
    return res;
}
}