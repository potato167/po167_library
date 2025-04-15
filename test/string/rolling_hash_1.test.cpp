#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../../string/Rolling_Hash.hpp"
#include <iostream>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    int N = S.size();
    po167::RollingHash H(S);
    std::cout << N;
    for (int i = 1; i < N; i++){
        int a = 0, b = N - i + 1;
        while (b - a > 1){
            int m = (a + b) / 2;
            if (H.get(0, m) == H.get(i, i + m)) a = m;
            else b = m;
        }
        std::cout << " " << a;
    }
    std::cout << "\n";
}