#include "FPS_cyclic_convolution.hpp"
namespace po167{
// return {f(ar^0), f(ar^1), f(ar^2), ... f(ar^{len - 1})}
template <class T>
std::vector<T> Multipoint_Evaluation_Geo(
    std::vector<T> f,
    T a, T r, int len = -1
){
    if (len == -1) len = f.size();
    if (r == 0){
        T tmp = 1;
        std::vector<T> res(len, f[0]);
        for (int i = 1; i < (int)f.size(); i++){
            tmp *= a;
            res[0] += tmp * f[i];
        }
        return res;
    }
    /*
    X[k] = sum (fi * (ar^k)^i)
         = sum (fi * a^i * r^{ki})
         = sum (fi * a^i * r^t[k + i] * r^-t[k] * r^-t[i])
         = r^-t[k] sum r^t[k + i](fi * a^i * r^-t[i])
    */
    int n = f.size();
    T invr = (T)(1) / (T)(r);
    T tmp = 1, tmpr1 = 1, tmpr2 = 1;
    for (int i = 0; i < n; i++){
        f[i] *= tmp * tmpr2;
        tmpr2 *= tmpr1;
        tmpr1 *= invr;
        tmp *= a;
    }
    std::vector<T> g(n + len - 1);
    tmpr1 = 1, tmpr2 = 1;
    for (int i = 0; i < n + len - 1; i++){
        g[i] = tmpr2;
        tmpr2 *= tmpr1;
        tmpr1 *= r;
    }
    std::reverse(f.begin(), f.end());
    int size = 1;
    while (size < n + len - 1) size *= 2;
    f.resize(size);
    g.resize(size);
    f = po167::FPS_cyclic_convolution(f, g);
    std::vector<T> res(len);
    for (int i = n - 1; i < n + len - 1; i++){
        res[i - n + 1] = f[i];
    }
    tmpr1 = 1, tmpr2 = 1;
    for (int i = 0; i < len; i++){
        res[i] *= tmpr2;
        tmpr2 *= tmpr1;
        tmpr1 *= invr;
    }
    return res;
}
}
