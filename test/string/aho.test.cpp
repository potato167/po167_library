#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"
#include "../../string/Trie_Tree.hpp"
#include <string>
#include <iostream>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    po167::Trie_Tree<'a', 26> T;
    std::vector<int> ans(N);
    for (int i = 0; i < N; i++){
        std::string S;
        std::cin >> S;
        auto lis = T.insert(S, i);
        ans[i] = lis.back();
    }
    T.aho();
    std::cout << T.nodes.size() << "\n";
    for (int i = 1; i < (int)T.nodes.size(); i++){
        std::cout << T.nodes[i].parent_node << " " << T.fail[i] << "\n";
    }
    for (int i = 0; i < N; i++){
        std::cout << ans[i] << (i == N - 1 ? "\n" : " ");
    }
}