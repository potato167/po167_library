#pragma once
#include "FPS_log.hpp"
#include "FPS_Product_Sequence.hpp"

namespace po167{
template<class T>
std::vector<T> FPS_sum_of_power(std::vector<T> A, int M){
    std::vector<std::vector<T>> B(A.size());
    for (int i = 0; i < (int)(A.size()); i++){
        B[i] = {1, - A[i]};
    }
    auto C = FPS_Product_Sequence(B);
    C = FPS_log(C, M + 1);
    std::vector<T> res(M + 1);
    res[0] = (int)A.size();
    for (int i = 0; i < M; i++){
        res[i + 1] = C[i + 1] * -1 * (i + 1);
    }
    return res;
}
}