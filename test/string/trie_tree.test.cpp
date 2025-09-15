#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2873"
#include "../../string/Trie_Tree.hpp"
#include <iostream>

int main(){
    std::string S;
    std::cin >> S;
    int N;
    std::cin >> N;
    po167::Trie_Tree<26,'a'> tt;
    for (int i = 0; i < N; i++){
        std::string t;
        std::cin >> t;
        tt.insert(t, i);
    }
    tt.aho();
    auto taboo = tt.taboo();
    int ans = 0;
    int r = 0;
    int node = 0;
    while (r != (int)S.size()){
        int c = S[r] - 'a';
        if (tt.nodes[node].next_node[c] == -1){
            if (node == 0) r++;
            node = tt.fail[node];
        }
        else{
            node = tt.nodes[node].next_node[c];
            r++;
        }
        if (taboo[node]){
            ans++;
            node = 0;
        }
    }
    std::cout << ans << "\n";
}