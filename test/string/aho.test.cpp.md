---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: string/Trie_Tree.hpp
    title: string/Trie_Tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aho_corasick
    links:
    - https://judge.yosupo.jp/problem/aho_corasick
  bundledCode: "#line 1 \"test/string/aho.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\
    \n#line 2 \"string/Trie_Tree.hpp\"\n#include <vector>\n#include <array>\n#include\
    \ <string>\n\nnamespace po167{\ntemplate<const int char_size,int base>\nstruct\
    \ Trie_Tree\n{\n    struct Node{\n        std::array<int, char_size> next_node;\n\
    \        std::vector<int> terminate_node;\n        int parent_node;\n        int\
    \ char_number;\n        int accepet_count;\n        explicit Node(int c_):parent_node(-1),char_number(c_),accepet_count(0){\n\
    \            for(int i=0;i<char_size;i++) next_node[i]=-1;\n        }\n    };\n\
    \    std::vector<Node> nodes;\n    std::vector<int> fail;\n    Trie_Tree(){\n\
    \        nodes.push_back(Node(-1));\n    }\n    std::vector<int> insert(std::string\
    \ &word,int word_id){\n        int node_id=0;\n        std::vector<int> ids;\n\
    \        for (char & i : word){\n            node_id=min_insert(i,node_id,word_id);\n\
    \            ids.push_back(node_id);\n        }\n        nodes[ids.back()].terminate_node.push_back(word_id);\n\
    \        return ids;\n    }\n    int min_insert(char ch,int node_id,int word_id){\n\
    \        int c=(int)(ch-base);\n        int next_id=nodes[node_id].next_node[c];\n\
    \        if(next_id==-1){\n            next_id=(int)nodes.size();\n          \
    \  nodes.push_back(Node(c));\n        }\n        nodes[next_id].parent_node=node_id;\n\
    \        nodes[node_id].next_node[c]=next_id;\n        // nodes[next_id].accept_node.push_back(word_id);\n\
    \        nodes[node_id].accepet_count++;\n        node_id=next_id;\n        return\
    \ node_id;\n    }\n    void aho(){\n        fail.resize(nodes.size());\n     \
    \   std::vector<int> order = {0};\n        order.reserve(nodes.size());\n    \
    \    for (int i = 0; i < (int)(order.size()); i++){\n            int id = order[i];\n\
    \            if (id == 0){\n                fail[id] = 0;\n            }\n   \
    \         else{\n                int f = fail[nodes[id].parent_node];\n      \
    \          int c = nodes[id].char_number;\n                while (f != fail[f]\
    \ && nodes[f].next_node[c] == -1){\n                    f = fail[f];\n       \
    \         }\n                if (nodes[f].next_node[c] != -1 && nodes[f].next_node[c]\
    \ != id) fail[id] = nodes[f].next_node[c];\n                else fail[id] = 0;\n\
    \            }\n            for (int j = 0; j < char_size; j++){\n           \
    \     if (nodes[id].next_node[j] != -1) order.push_back(nodes[id].next_node[j]);\n\
    \            }\n        }\n    }\n\n    // node \u3067\u3042\u3063\u3066\u3001\
    \u8FFD\u52A0\u3057\u305F\u6587\u5B57\u5217\u3092\u90E8\u5206\u5217\u3068\u3057\
    \u3066\u542B\u307E\u306A\u3044\u3082\u306E\u3092\u8FD4\u3059\n    // aho \u3092\
    \u5148\u306B\u547C\u3093\u3067\u3044\u308B\u3053\u3068\u304C\u524D\u63D0\n   \
    \ std::vector<bool> taboo(){\n        assert(!fail.empty());\n        std::vector<int>\
    \ order = {0};\n        std::vector<bool> taboo(nodes.size(), false);\n      \
    \  for (int i = 0; i < (int)order.size(); i++){\n            int a = order[i];\n\
    \            if (!nodes[a].terminate_node.empty()) taboo[a] = true;\n        \
    \    if (taboo[fail[a]]) taboo[a] = true;\n            if (a != 0 && taboo[nodes[a].parent_node])\
    \ taboo[a] = true;\n            for (int j = 0; j < char_size; j++){\n       \
    \         int c = nodes[a].next_node[j];\n                if (c != -1) order.push_back(c);\n\
    \            }\n        }    \n        return taboo;\n    }\n};\n}\nusing po167::Trie_Tree;\n\
    #line 4 \"test/string/aho.test.cpp\"\n#include <iostream>\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int N;\n    std::cin >> N;\n    po167::Trie_Tree<'a',\
    \ 26> T;\n    std::vector<int> ans(N);\n    for (int i = 0; i < N; i++){\n   \
    \     std::string S;\n        std::cin >> S;\n        auto lis = T.insert(S, i);\n\
    \        ans[i] = lis.back();\n    }\n    T.aho();\n    std::cout << T.nodes.size()\
    \ << \"\\n\";\n    for (int i = 1; i < (int)T.nodes.size(); i++){\n        std::cout\
    \ << T.nodes[i].parent_node << \" \" << T.fail[i] << \"\\n\";\n    }\n    for\
    \ (int i = 0; i < N; i++){\n        std::cout << ans[i] << (i == N - 1 ? \"\\\
    n\" : \" \");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\n#include\
    \ \"../../string/Trie_Tree.hpp\"\n#include <string>\n#include <iostream>\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int N;\n    std::cin >> N;\n    po167::Trie_Tree<'a', 26> T;\n    std::vector<int>\
    \ ans(N);\n    for (int i = 0; i < N; i++){\n        std::string S;\n        std::cin\
    \ >> S;\n        auto lis = T.insert(S, i);\n        ans[i] = lis.back();\n  \
    \  }\n    T.aho();\n    std::cout << T.nodes.size() << \"\\n\";\n    for (int\
    \ i = 1; i < (int)T.nodes.size(); i++){\n        std::cout << T.nodes[i].parent_node\
    \ << \" \" << T.fail[i] << \"\\n\";\n    }\n    for (int i = 0; i < N; i++){\n\
    \        std::cout << ans[i] << (i == N - 1 ? \"\\n\" : \" \");\n    }\n}"
  dependsOn:
  - string/Trie_Tree.hpp
  isVerificationFile: true
  path: test/string/aho.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 01:39:10+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/string/aho.test.cpp
layout: document
redirect_from:
- /verify/test/string/aho.test.cpp
- /verify/test/string/aho.test.cpp.html
title: test/string/aho.test.cpp
---
