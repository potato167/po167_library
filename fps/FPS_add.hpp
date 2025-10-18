#pragma once
#include <vector>

namespace po167{
template <class T>
// a(x) += b(x) * c * x^d
void FPS_add(std::vector<T> &a, std::vector<T> b, T c = 1, int d = 0){
    for (int i = 0; i < (int)(b.size()); i++){
        while ((int)a.size() <= i + d) a.push_back((T)0);
        a[i + d] += b[i] * c;
    }
}
}