---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/aho.test.cpp
    title: test/string/aho.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/string/trie_tree.test.cpp
    title: test/string/trie_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/Trie_Tree.hpp\"\n#include <vector>\n#include <array>\n\
    #include <string>\n\nnamespace po167{\ntemplate<const int char_size,int base>\n\
    struct Trie_Tree\n{\n    struct Node{\n        std::array<int, char_size> next_node;\n\
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
    \            }\n        }\n    }\n};\n}\nusing po167::Trie_Tree;\n"
  code: "#pragma once\n#include <vector>\n#include <array>\n#include <string>\n\n\
    namespace po167{\ntemplate<const int char_size,int base>\nstruct Trie_Tree\n{\n\
    \    struct Node{\n        std::array<int, char_size> next_node;\n        std::vector<int>\
    \ terminate_node;\n        int parent_node;\n        int char_number;\n      \
    \  int accepet_count;\n        explicit Node(int c_):parent_node(-1),char_number(c_),accepet_count(0){\n\
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
    \            }\n        }\n    }\n};\n}\nusing po167::Trie_Tree;\n"
  dependsOn: []
  isVerificationFile: false
  path: string/Trie_Tree.hpp
  requiredBy: []
  timestamp: '2025-06-26 21:26:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/trie_tree.test.cpp
  - test/string/aho.test.cpp
documentation_of: string/Trie_Tree.hpp
layout: document
redirect_from:
- /library/string/Trie_Tree.hpp
- /library/string/Trie_Tree.hpp.html
title: string/Trie_Tree.hpp
---
