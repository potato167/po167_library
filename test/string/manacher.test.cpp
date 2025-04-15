#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../string/Manacher.hpp"
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    auto res = po167::Manacher(S);
    for (int i = 0; i < (int)res.size(); i++){
        std::cout << res[i] << ((int)(res.size()) == i + 1 ? "\n" : " ");
    }
}