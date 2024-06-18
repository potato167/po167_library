#pragma once
#include <vector>

namespace po167{
template <class T>
std::vector<T> FPS_differential(std::vector<T> f){
    if (f.empty()) return f;
    for (int i = 0; i < (int)f.size() - 1; i++){
        f[i] = f[i + 1] * (T)(i + 1);
    }
    f.pop_back();
    return f;
}
}