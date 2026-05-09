namespace po167{
std::vector<std::vector<int>> Lowlink(std::vector<std::vector<int>> &G){
    int n=G.size();
    std::vector<std::vector<int>> p(2,std::vector<int>(n,-1));
    std::vector<int> front(n);
    int k=1;
    std::vector<int> ind(n);
    std::stack<int> s;
    s.push(0);p[0][0]=0,p[1][0]=0;
    while(!s.empty()){
        int a=s.top();
        while(true){
            if(ind[a]==(int)(G[a].size())){
                p[1][front[a]]=std::min(p[1][front[a]],p[1][a]);
                s.pop();
                break;
            }
            int b=G[a][ind[a]];
            ind[a]++;
            if(p[0][b]==-1){
                p[0][b]=k;
                p[1][b]=k;
                front[b]=a;
                k++;
                s.push(b);
                break;
            }
            else if(front[a]!=b){
                if(p[1][a]>p[0][b]) p[1][a]=p[0][b];
            }
        }
    }
    p.push_back(front);
    return p;
}

std::vector<std::pair<int,int>> bridges(std::vector<std::vector<int>> G){
    int n=G.size();
    auto p=Lowlink(G);
    std::vector<std::pair<int,int>> ans;
    for(int i=0;i<n;i++){
        for(int j:G[i]){
            if(p[0][i]<p[0][j]&&p[0][i]<p[1][j]){
                ans.push_back({i,j});
            }
        }
    }
    return ans;
}
//https://onlinejudge.u-aizu.ac.jp/status/users/potato167/submissions/1/GRL_3_A/judge/6651994/C++17
std::vector<int> Articulation_Points(std::vector<std::vector<int>> G){
    int n=G.size();
    auto p=Lowlink(G);
    std::vector<int> ans;
    int tmp=0;
    for(auto x:G[0]){
        if(p[2][x]==0) tmp++;
    }
    if(tmp>=2) ans.push_back(0);
    for(int i=1;i<n;i++){
        for(int j:G[i]){
            if(i==p[2][j]&&p[0][i]<=p[1][j]){
                ans.push_back(i);
                break;
            }
        }
    }
    return ans;
}
}
