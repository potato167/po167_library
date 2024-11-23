#pragma once
#include <vector>
#include <cassert>
namespace po167{
//https://kazuma8128.hatenablog.com/entry/2018/05/31/144519
template<class T>
void and_fwt(std::vector<T> &f){
    int n = f.size();
    for (int i = 1; i < n; i <<= 1){
        for (int j = 0; j < n; j++){
            if ((j & i) == 0){
                f[j] = f[j] + f[j | i];
            }
        }
    }
}
template<class T>
void and_ifwt(std::vector<T> &f){
    int n = f.size();
    for (int i = 1; i < n; i <<= 1){
        for (int j = 0; j < n; j++){
            if ((j & i) == 0){
                f[j] = f[j] - f[j | i];
            }
        }
    }
}
template<class T>
std::vector<T> and_convolution(std::vector<T> p, std::vector<T> q){
    int n = p.size();
    assert(n == (int)q.size());
    and_fwt(p), and_fwt(q);
    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];
    and_ifwt(p);
    return p;
}

template<class T>
void or_fwt(std::vector<T> &f){
    int n = f.size();
    for (int i = 1; i < n; i <<= 1){
        for (int j = 0; j < n; j++){
            if (j & i){
                f[j] = f[j] + f[j ^ i];
            }
        }
    }
}
template<class T>
void or_ifwt(std::vector<T> &f){
    int n = f.size();
    for (int i = 1; i < n; i <<= 1){
        for (int j = 0; j < n; j++){
            if (j & i){
                f[j] = f[j] - f[j ^ i];
            }
        }
    }
}

template<class T>
std::vector<T> or_convolution(std::vector<T> p, std::vector<T> q){
    int n = p.size();
    assert(n == (int)q.size());
    or_fwt(p), or_fwt(q);
    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];
    or_ifwt(p);
    return p;
}

template<class T>
void xor_fwt(std::vector<T> &f){
    int n = f.size();
    for (int i = 1; i < n; i <<= 1){
        for (int j = 0; j < n; j++){
            if (j & i){
                T x = f[j ^ i], y = f[j];
                f[j ^ i] = x + y;
                f[j]     = x - y;
            }
        }
    }
}

template<class T>
std::vector<T> xor_convolution(std::vector<T> p, std::vector<T> q){
    int n = p.size();
    assert(n == (int)q.size());
    xor_fwt(p), xor_fwt(q);
    for (int i = 0; i < n; i++) p[i] = p[i] * q[i];
    xor_fwt(p);
    T inv = (T)(1) / (T)(n);
    for (int i = 0; i < n; i++) p[i] = p[i] * inv;
    return p;
}

};