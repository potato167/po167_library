#pragma once
#include <vector>

namespace po167{
template <class T>
std::vector<T> FPS_add(std::vector<T> f, std::vector<T> g){
    int len = max(f.size(), g.size());
    f.resize(len, 0);
    g.resize(len, 0);
    for (int i = 0; i < len; i++) f[i] += g[i];
    return f;
}
}