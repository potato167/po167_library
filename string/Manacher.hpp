#pragma once
#include <vector>
#include <string>


// https://snuke.hatenablog.com/entry/2014/12/02/235837
namespace po167{
template<class T>

// input  : abaab
// output : 1 0 3 0 1 4 1 0 1
std::vector<int> Manacher(std::vector<T> &v){
    int N = v.size();
    std::vector<int> res(N * 2 + 1);
    int i = 0, j = 0;
    while (i < N * 2 + 1){
        while (i - j >= 0 && i + j < N * 2 + 1 
            && (((i + j) & 1) == 0 || v[(i - j) / 2] == v[(i + j) / 2])) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    res.pop_back();
    res.erase(res.begin());
    for (auto &x : res) x--;
    return res;
}

// input  : abaab
// output : 1 0 3 0 1 4 1 0 1
std::vector<int> Manacher(std::string &s){
    std::vector<int> v(s.size());
    for (int i = 0; i < (int)s.size(); i++) v[i] = s[i];
    return Manacher(v);
}
}
