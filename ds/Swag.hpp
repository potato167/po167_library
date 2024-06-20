#pragma once
#include <vector>
#include <cassert>

namespace po167{
template<class T, T (*op)(T, T), T (*e)()>
struct SWAG
{
    std::vector<std::pair<T, T>> A, B;
    SWAG(int n = -1){
        if (n > 0) A.reserve(n + 1), B.reserve(n + 1);
        A.push_back({e(), e()});
        B.push_back({e(), e()});
    }
    void push(T v){
        B.push_back({v, op(B.back().second, v)});
    }
    void pop(){
        if ((int)A.size() == 1){
            while ((int)B.size() != 1){
                A.push_back({B.back().first, op(B.back().first, A.back().second)});
                B.pop_back();
            }
        }
        assert((int)A.size() != 1);
        A.pop_back();
    }
    T calc(){
        return op(A.back().second, B.back().second);
    }
};
}