#pragma once

#include <vector>
#include <atcoder/convolution>

#include "FPS_exp.hpp"
#include "FPS_log.hpp"

namespace po167{
template<class T>
std::vector<T> FPS_pow(std::vector<T> f,long long M, int len = -1){
    if (len == -1) len = f.size();
    std::vector<T> res(len, 0);
    if (M == 0){
        res[0] = 1;
        return res;
    }
    for (int i = 0; i < (int)f.size(); i++){
        if (f[i] == 0) continue;
        if (i > (len - 1) / M) break;
        std::vector<T> g((int)f.size() - i);
        T v = (T)(1) / (T)(f[i]);
        for (int j = i; j < (int)f.size(); j++){
            g[j - i] = f[j] * v;
        }
        long long zero = i * M;
        if (i) len -= i * M;
        g = FPS_log(g, len);
        for (T &x : g) x *= M;
        g = FPS_exp(g, len);
        v = (T)(1) / v;
        T c = 1;
        while (M){
            if (M & 1) c = c * v;
            v = v * v;
            M >>= 1;
        }
        for (int i = 0; i < len; i++) res[i + zero] = g[i] * c;
        return res;
    }
    return res;
}
}