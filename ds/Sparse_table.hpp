#pragma once
#include <vector>
#include <cassert>
namespace po167{
template<class T, T(*op)(T, T)>
struct Sparse_table{
    int n;
    int depth;
    std::vector<std::vector<T>> val;
    void init(std::vector<T> &v){
        depth = 1;
        n = v.size();
        while ((1 << depth) <= n) depth++;
        val.resize(depth);
        val[0] = v;
        for (int i = 1; i < depth; i++){
            val[i].resize(n);
            for (int j = 0; j <= n - (1 << i); j++){
                val[i][j] = op(val[i - 1][j], val[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    Sparse_table(std::vector<T> v){
        init(v);
    }
    Sparse_table(){}
    // 0 <= l < r <= n
    // if l == r : assert
    T prod(int l, int r){
        assert(0 <= l && l < r && r <= n);
        int z=31-__builtin_clz(r-l);
        return op(val[z][l], val[z][r - (1 << z)]);
    }
};
}