namespace po167{

template<class S>
std::vector<S> count_outdeg(std::vector<std::vector<S>> &G){
    int N = G.size();
    std::vector<S> outdeg(N);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) outdeg[i] += G[i][j];
    return outdeg;
}

template<class S>
std::vector<S> count_indeg(std::vector<std::vector<S>> &G){
    int N = G.size();
    std::vector<S> indeg(N);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) indeg[j] += G[i][j];
    return indeg;
}

// O(|M|^{3})
template<class T>
T det_matrix(std::vector<std::vector<T>> M){
    int N = M.size();
    if (N == 0) return 1;
    if (N == 1) return M[0][0];
    if (N == 2) return M[0][0] * M[1][1] - M[0][1] * M[1][0];

    T res = 1;
    for (int i = 0; i < N; i++){
        for (int  j = i; j < N; j++){
            if (M[j][i] != 0){
                if (j != i){
                    swap(M[i], M[j]);
                    res *= -1;
                }
                break;
            }
        }
        if (M[i][i] == 0) return 0;
        res *= M[i][i];
        if (i + 1 == N) break;
        T v = 1 / M[i][i];
        for (int j = i + 1; j < N; j++){
            T t = M[j][i] * v;
            for (int k = i; k < N; k++){
                M[j][k] -= M[i][k] * t;
            }
        }
    }
    return res;
}

template<class T,class S>
std::vector<std::vector<T>> Directed_Matrix_tree_Theorem_sub(std::vector<std::vector<S>> &G, int u = 0){
    int N = G.size();
    
    std::vector L(N - 1, std::vector<T>(N - 1, 0));
    std::vector<S> outdeg(N);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (i != j) outdeg[i] += G[i][j];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
        if (i == u || j == u) continue;
        int a = i, b = j;
        if (u < i) a--;
        if (u < j) b--;
        if (i == j) L[a][b] = outdeg[i];
        else L[a][b] -= G[i][j];
    }
    return L;
}


template<class T,class S>
T Directed_Matrix_tree_Theorem(std::vector<std::vector<S>> &G, int u = 0){
    if (int(G.size()) == 1) return T(1);
    return det_matrix(Directed_Matrix_tree_Theorem_sub<T>(G, u));
}

// s.t
// forall i,j
// 0 <= G[i][j]
// if not connected
// use remove iso
template<class T,class S>
std::pair<T, std::vector<std::vector<T>>> Count_Euler_Circuit_sub(std::vector<std::vector<S>> G, std::vector<T> &fact_base, bool fact_in = true){
    int N = G.size();
    if (N == 0) return {1, {{1}}};
    std::vector<S> outdeg = count_outdeg(G);
    std::vector<S> indeg  = count_indeg(G);

    // indeg  == outdeg ?
    for (int i = 0; i < N; i++) if (indeg[i] != outdeg[i]) return {0, {{1}}};

    // connected ?
    std::vector<bool> seen(N);
    std::vector<int> order={0};
    seen[0] = 1;
    for (int i = 0; i < N; i++){
        if (i == int(order.size())) return {0, {{1}}};
        for (int j = 0; j < N; j++){
            if (G[order[i]][j] != 0 && !seen[j]){
                seen[j] = 1;
                order.push_back(j);
            }
        }
    }
    T res = 1;
    if (fact_in) for (int i = 0; i < N; i++) res *= fact_base[outdeg[i] - 1];
    return {res ,Directed_Matrix_tree_Theorem_sub<T, S>(G)};
}

template<class T,class S>
T Count_Euler_Circuit(std::vector<std::vector<S>> G, std::vector<T> &fact_base, bool fact_in = true){
    auto tmp = Count_Euler_Circuit_sub(G, fact_base, fact_in);
    if (tmp.first == 0) return T(0);
    return tmp.first * det_matrix(tmp.second);
}

template<class S>
std::vector<std::vector<S>> remove_isolated_vertex(
    std::vector<std::vector<S>> G
){
    int N = G.size();
    std::vector<int> seen(N, -1);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
        if (G[i][j] != 0) seen[i] = 1, seen[j] = 1;
    }
    int ind = 0;
    for (int i = 0; i < N; i++) if (seen[i] == 1) seen[i] = ind++;
    std::vector res(ind, std::vector<S>(ind));
    for (int i = 0; i < N; i++) if (seen[i] != -1){
        for (int j = 0; j < N; j++) if (seen[j] != -1){
            res[seen[i]][seen[j]] = G[i][j];
        }
    }
    return res;
}

// s.t
// forall i,j
// 0 <= G[i][j]
// if not connected
// use remove iso
template<class T,class S>
std::pair<T, std::vector<std::vector<T>>> Count_Eulerian_Trail_sub(std::vector<std::vector<S>> G,std::vector<T> &fact_base, bool fact_in = true){
    bool ok = 1;
    int N = G.size();
    if (N == 0) return {1, {{1}}};
    std::vector<S> outdeg = count_outdeg(G), indeg = count_indeg(G);
    S sum = 0;
    for (int i = 0; i < N; i++){
        sum += outdeg[i];
    }
    int st = -1, ed = -1;
    for (int i = 0; i < N; i++) if (outdeg[i] != indeg[i]){
        if (std::abs(outdeg[i] - indeg[i]) > 1){
            ok = 0;
            break;
        }
        if (outdeg[i] > indeg[i]){
            if (ed != -1) ok = 0;
            ed = i;
        } else {
            if (st != -1) ok = 0;
            st = i;
        }
    }
    if (!ok) return {0, {{1}}};
    if ((st == -1) ^ (ed == -1)) return {0, {{1}}};
    if (st == -1){
        auto tmp = Count_Euler_Circuit_sub(G, fact_base, fact_in);
        return {T(sum) * tmp.first, tmp.second};
    }
    G[st][ed]++;
    return Count_Euler_Circuit_sub(G, fact_base, fact_in);
}

template<class T,class S>
T Count_Eulerian_Trail(std::vector<std::vector<S>> G,std::vector<T> &fact_base, bool fact_in = true){
    auto tmp = Count_Eulerian_Trail_sub<T, S>(G, fact_base, fact_in);
    if (tmp.first == 0) return 0;
    return tmp.first * det_matrix(tmp.second);
}

}
