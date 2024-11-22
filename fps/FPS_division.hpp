#pragma once
#include <vector>
#include <atcoder/convolution>

#include "FPS_inv.hpp"
namespace po167{
template<class T>
// f = g * res.first + res.second
// |res.first| <= |f| - |g| + 1
// |res.second| <= |g| - 1
std::pair<std::vector<T>, std::vector<T>>
FPS_division(std::vector<T> f, std::vector<T> g){
    while (!f.empty() && f.back() == 0) f.pop_back();
    assert(!g.empty() && g.back() != 0);
    if (f.size() < g.size()){
        return {{}, f};
    }
    // rev(f) / rev(g) = rev(q) (mod x ^ {|f| - |g| + 1})
    std::vector<T> r = f;
    std::reverse(f.begin(), f.end());
    std::reverse(g.begin(), g.end());
    int z = (int)f.size() - (int)g.size() + 1;
    f.resize(z);
    std::vector<T> q = atcoder::convolution(f, FPS_inv(g, z));
    q.resize(z);
    std::reverse(g.begin(), g.end());
    std::reverse(q.begin(), q.end());
    f = atcoder::convolution(q, g);
    for (int i = 0; i < (int)f.size(); i++) r[i] -= f[i];
    while (!q.empty() && q.back() == 0) q.pop_back();
    while (!r.empty() && r.back() == 0) r.pop_back();
    return {q, r};
}
}