#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>

namespace po167{
/*
 * グラフを与える。
 * オイラーウォークが存在するなら、
 * 頂点番号の列と辺番号の列をどちらも返す
 * 入力 : vector<vector<pair<int, int>>> グラフ, 辺の数, start
 * 出力 : 頂点の列と辺の番号の列の pair
 *
 * start 地点について
 * -1 にしておくと、その後の dir をみて自動的に求める
 * dir : true  -> 出次 - 入次　が大きいやつ
 * dir : false -> 奇数頂点のやつ
 * なかったら 0 とかになる
 *
 *
 */
std::pair<std::vector<int>, std::vector<int>> Eulerian_trail(
    std::vector<std::vector<std::pair<int, int>>> g, int n_edge, int start = -1, bool dir = false
){
    int N = (int)g.size();
    // スタート地点不定
    if (start == -1){
        // 有向グラフのとき
        if (dir){
            std::vector<int> sc(N);
            for (int i = 0; i < N; i++){
                for (auto [to, ind] : g[i]){
                    sc[i]++;
                    sc[to]--;
                }
            }
            start = 0;
            for (int i = 0; i < N; i++){
                if ((int)g[i].empty()) continue;
                if (sc[i] >= sc[start]) start = i;
            }
        }
        // 無向グラフのとき
        else{
            for (int i = 0; i < N; i++){
                if ((int)g[i].size() % 2 == 1){
                    start = i;
                    break;
                }
            }
            if (start == -1){
                start = 0;
                for (int i = 0; i < N; i++){
                    if ((int)g[i].size() != 0){
                        start = i;
                        break;
                    }
                }
            }
        }
    }
    assert(0 <= start && start < N);
    // -1 はそもそも使われていないもの
    std::vector<int> use_edge(n_edge, -1);
    std::vector<int> st_var = {start}, st_edge = {-1};
    std::vector<int> res_var, res_edge;
    std::vector<int> edge_index(N);
    std::vector<int> deg(N);
    deg[start] = 1;

    // 実際に何本の辺があるのかと、n_edge の制約を満たしているか確認
    int real_edge = 0;
    for (int i = 0; i < N; i++){
        for (auto [a, b] : g[i]){
            assert(0 <= a && a < N);
            assert(0 <= b && b < n_edge);
            if (use_edge[b] == -1){
                use_edge[b] = 0;
                real_edge++;
            }
        }
    }

    while (!st_var.empty()){
        int var = st_var.back();
        int ind = edge_index[var];
        if (ind == (int)g[var].size()){
            res_var.push_back(var);
            res_edge.push_back(st_edge.back());
            st_var.pop_back();
            st_edge.pop_back();
            continue;
        }
        if (use_edge[g[var][ind].second] == 0){
            st_var.push_back(g[var][ind].first);
            use_edge[g[var][ind].second] = 1;
            st_edge.push_back(g[var][ind].second);
            deg[var]--;
            deg[g[var][ind].first]++;
        }
        edge_index[var]++;
    }

    for (auto x : deg) if (x < 0) return {{}, {}};
    if (real_edge + 1 != (int)res_var.size()) return {{}, {}};
    std::reverse(res_var.begin(), res_var.end());
    res_edge.pop_back();
    std::reverse(res_edge.begin(), res_edge.end());
    return {res_var, res_edge};
}
}