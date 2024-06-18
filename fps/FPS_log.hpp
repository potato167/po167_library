#pragma once
#include <vector>
#include "../fps/FPS_differetial.hpp"
#include "../fps/FPS_integral.hpp"

namespace po167{
template<class T>
std::vector<T> FPS_log(std::vector<T> f, int len = -1){
    if (len == -1) len = f.size();
    if (len == 0) return {};
    if (len == 1) return {T(0)};
    assert(!f.empty() && f[0] == 1);
    std::vector<T> res = atcoder::convolution(FPS_differential(f), FPS_inv(f, len));
    res.resize(len - 1);
    return FPS_integral(res);
}
}