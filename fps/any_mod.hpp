#pragma once
#include <vector>
#include <atcoder/convolution>
#include <cassert>

namespace po167{
//https://kopricky.github.io/code/Computation_Advanced/garner.html
template<typename T>
T mod_add(const T a, const T b, const T mod){
    return (a + b) % mod;
}
 
template<typename T>
T mod_mul(const T a, const T b, const T mod){
    return a * b % mod;
}
 
template<typename T>
T mod_inv(T a, T mod){
    T u[] = {a, 1, 0}, v[] = {mod, 0, 1}, t;
    while(*v){
        t = *u / *v;
        std::swap(u[0] -= t * v[0], v[0]);
        std::swap(u[1] -= t * v[1], v[1]);
        std::swap(u[2] -= t * v[2], v[2]);
    }
    u[1] %= mod;
    return (u[1] < 0) ? (u[1] + mod) : u[1];
}
 
template<typename T>
T garner(const std::vector<T>& a, std::vector<T> p, const T mod){
    const unsigned int sz = a.size();
    std::vector<T> kp(sz + 1, 0), rmult(sz + 1, 1);
    p.push_back(mod);
    for(unsigned int i = 0; i < sz; ++i){
        T x = mod_mul(a[i] - kp[i], mod_inv(rmult[i], p[i]), p[i]);
        x = (x < 0) ? (x + p[i]) : x;
        for(unsigned int j = i + 1; j < sz + 1; ++j){
            kp[j] = mod_add(kp[j], rmult[j] * x, p[j]);
            rmult[j] = mod_mul(rmult[j], p[i], p[j]);
        }
    }
    return kp[sz];
}

const long long _mod0=754974721;
const long long _mod1=167772161;
const long long _mod2=469762049;
std::vector<long long> _MOD={_mod0,_mod1,_mod2};
std::vector<long long> convolution_any_mod(std::vector<long long> a,std::vector<long long> b,long long pmod){
	for(auto &x:a) x = (x % pmod + pmod) % pmod;
	for(auto &x:b) x = (x % pmod + pmod) % pmod;
	std::vector<std::vector<long long>> res(3);
	res[0] = atcoder::convolution<_mod0>(a,b);
	res[1] = atcoder::convolution<_mod1>(a,b);
	res[2] = atcoder::convolution<_mod2>(a,b);
	for(int i=0;i<(int)res[0].size();i++){
		std::vector<long long> q(3);
		for(int j=0;j<3;j++) q[j] = res[j][i];
		res[0][i] = garner(q, _MOD, pmod);
	}
	return res[0];
}
template<typename T>
std::vector<T> convolution_mint(std::vector<T> a, std::vector<T> b){
    std::vector<long long> A, B;
    A.reserve(a.size()), B.reserve(b.size());
    for (auto x : a) A.push_back(x.val());
    for (auto x : b) B.push_back(x.val());
    std::vector<long long> C = convolution_any_mod(A, B, T::mod());
    std::vector<T> c;
    c.reserve(C.size());
    for (auto x : C) c.push_back(x);
    return c;
}
};