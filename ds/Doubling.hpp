#pragma once
#include <vector>
#include <cassert>
namespace po167{

template<class T, T(*op)(T, T)>
struct Doubling_op{
    int n;
    int depth;
    std::vector<std::vector<int>> index;
    std::vector<std::vector<T>> val;
    Doubling_op(std::vector<int> p, std::vector<T> v, long long lim = (1ll << 60) - 1){
        n = p.size();
        for (auto x : p) assert(0 <= x && x < n);
        assert(n == (int)v.size());
        depth = 1;
        while ((1ll << depth) <= lim) depth++;
        index.resize(depth);
        val.resize(depth);
        index[0] = p;
        val[0] = v;
        for (int i = 1; i < depth; i++){
            index[i].resize(n);
            val[i].resize(n);
            for (int j = 0; j < n; j++){
                int tmp = index[i - 1][j];
                index[i][j] = index[i - 1][tmp];
                val[i][j] = op(val[i - 1][j], val[i - 1][tmp]);
            }
        }
    }
    std::pair<int, T> query(int start_ind, T start_val, long long times){
        assert(0 <= start_ind && start_ind < n);
        assert(0 <= times && times < (1ll << depth));
        int i = 0;
        while (times){
            if (times & 1){
                start_val = op(start_val, val[i][start_ind]);
                start_ind = index[i][start_ind];
            }
            i++;
            times >>= 1;
        }
        return std::make_pair(start_ind, start_val);
    }
};

struct Doubling{
    int n;
    int depth;
    std::vector<std::vector<int>> index;
    Doubling(std::vector<int> p, long long lim = (1ll << 60) - 1){
        n = p.size();
        for (auto x : p) assert(0 <= x && x < n);
        depth = 1;
        while ((1ll << depth) <= lim) depth++;
        index.resize(depth);
        index[0] = p;
        for (int i = 1; i < depth; i++){
            index[i].resize(n);
            for (int j = 0; j < n; j++){
                index[i][j] = index[i - 1][index[i - 1][j]];
            }
        }
    }
    int query(int ind, long long times){
        assert(0 <= ind && ind < n);
        assert(0 <= times && times < (1ll << depth));
        int i = 0;
        while (times){
            if (times & 1) ind = index[i][ind];
            i++;
            times >>= 1;
        }
        return ind;
    }
};
}
