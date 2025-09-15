#pragma once
#include <vector>
#include <array>
#include <string>

namespace po167{
template<const int char_size,int base>
struct Trie_Tree
{
    struct Node{
        std::array<int, char_size> next_node;
        std::vector<int> terminate_node;
        int parent_node;
        int char_number;
        int accepet_count;
        explicit Node(int c_):parent_node(-1),char_number(c_),accepet_count(0){
            for(int i=0;i<char_size;i++) next_node[i]=-1;
        }
    };
    std::vector<Node> nodes;
    std::vector<int> fail;
    Trie_Tree(){
        nodes.push_back(Node(-1));
    }
    std::vector<int> insert(std::string &word,int word_id){
        int node_id=0;
        std::vector<int> ids;
        for (char & i : word){
            node_id=min_insert(i,node_id,word_id);
            ids.push_back(node_id);
        }
        nodes[ids.back()].terminate_node.push_back(word_id);
        return ids;
    }
    int min_insert(char ch,int node_id,int word_id){
        int c=(int)(ch-base);
        int next_id=nodes[node_id].next_node[c];
        if(next_id==-1){
            next_id=(int)nodes.size();
            nodes.push_back(Node(c));
        }
        nodes[next_id].parent_node=node_id;
        nodes[node_id].next_node[c]=next_id;
        // nodes[next_id].accept_node.push_back(word_id);
        nodes[node_id].accepet_count++;
        node_id=next_id;
        return node_id;
    }
    void aho(){
        fail.resize(nodes.size());
        std::vector<int> order = {0};
        order.reserve(nodes.size());
        for (int i = 0; i < (int)(order.size()); i++){
            int id = order[i];
            if (id == 0){
                fail[id] = 0;
            }
            else{
                int f = fail[nodes[id].parent_node];
                int c = nodes[id].char_number;
                while (f != fail[f] && nodes[f].next_node[c] == -1){
                    f = fail[f];
                }
                if (nodes[f].next_node[c] != -1 && nodes[f].next_node[c] != id) fail[id] = nodes[f].next_node[c];
                else fail[id] = 0;
            }
            for (int j = 0; j < char_size; j++){
                if (nodes[id].next_node[j] != -1) order.push_back(nodes[id].next_node[j]);
            }
        }
    }

    // node であって、追加した文字列を部分列として含まないものを返す
    // aho を先に呼んでいることが前提
    std::vector<bool> taboo(){
        assert(!fail.empty());
        std::vector<int> order = {0};
        std::vector<bool> taboo(nodes.size(), false);
        for (int i = 0; i < (int)order.size(); i++){
            int a = order[i];
            if (!nodes[a].terminate_node.empty()) taboo[a] = true;
            if (taboo[fail[a]]) taboo[a] = true;
            if (a != 0 && taboo[nodes[a].parent_node]) taboo[a] = true;
            for (int j = 0; j < char_size; j++){
                int c = nodes[a].next_node[j];
                if (c != -1) order.push_back(c);
            }
        }    
        return taboo;
    }
};
}
using po167::Trie_Tree;
