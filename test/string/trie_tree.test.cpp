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
    std::vector<int> taboo(tt.nodes.size());
    {
        std::vector<int> order = {0};
        for (int i = 0; i < (int)order.size(); i++){
            int a = order[i];
            if (!tt.nodes[a].terminate_node.empty()) taboo[a] = 1;
            if (taboo[tt.fail[a]]) taboo[a] = 1;
            for (int j = 0; j < 26; j++) if (tt.nodes[a].next_node[j] != -1){
                order.push_back(tt.nodes[a].next_node[j]);
            }
        }
    }
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