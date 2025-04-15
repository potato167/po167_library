#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../string/Rolling_Hash.hpp"
#include <iostream>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    int N = S.size();
    std::vector<int> T(N);
    for (int i = 0; i < N; i++) T[i] = S[i] - 'a';
    po167::RollingHash A(T);
    std::reverse(T.begin(), T.end());
    po167::RollingHash B(T);
    for (int i = 0; i < N * 2 - 1; i++){
        int l = N - (i + 1) / 2;
        int r = 1 + i / 2;
        int a = 0, b = N + 1 - std::max(l, r);
        while (b - a > 1){
            int m = (a + b) / 2;
            if (A.get(r, r + m) == B.get(l, l + m)) a = m;
            else b = m;
        }
        std::cout << a * 2 + ((i + 1) & 1) << (i + 1 == N * 2 - 1 ? "\n" : " ");
    }
}