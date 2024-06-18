#pragma once
#include <vector>

namespace po167{
template <class T>
std::vector<T> FPS_integral(std::vector<T> f){
    if (f.empty()) return f;
    std::vector<T> num_inv((int)f.size() + 1);
    num_inv[0] = 1;
    num_inv[1] = 1;
    auto m = T::mod();
    for (int i = 2; i <= (int)f.size(); i++){
        num_inv[i] = (0 - num_inv[m % i]) * (T)(m / i);
    }
    f.reserve((int)f.size() + 1);
    f.push_back(0);
    for (int i = (int)f.size() - 1; i > 0; i--){
        f[i] = f[i - 1] * num_inv[i];
    }
    f[0] = 0;
    return f;
}
}