
namespace po167{
// N = len (v)
// s.t N<64
// O(2^{N/2})
// ex if v[2]+v[3]+v[5] = S
// return 4+8+32
// https://atcoder.jp/contests/abc326/tasks/abc326_f

template<class T>
std::vector<std::pair<T,long long>> fsss2_sub(std::vector<T> v){
    int N=v.size();
    std::vector<std::pair<T,long long>> res={{0,0}};
    for(int i=0;i<N;i++){
        std::vector<std::pair<T,long long>> n_res(1<<(i+1));
        int l1=0,l2=0;
        for(int j=0;j<(1<<(i+1));j++){
            if(l1==(int)res.size()) n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];
            else if(l2==(int)res.size()) n_res[j]=res[l1],l1++;
            else if(res[l1].first<=res[l2].first+v[i]) n_res[j]=res[l1],l1++;
            else n_res[j]=res[l2],l2++,n_res[j].second+=(1<<i),n_res[j].first+=v[i];
        }
        swap(n_res,res);
    }
    return res;
}

template<class T>
long long fast_subset_sub_solver_2(std::vector<T> v,T S){
    int N=v.size();
    std::vector<T> X(N/2),Y((N+1)/2);
    for(int i=0;i<N/2;i++) X[i]=v[i];
    for(int i=N/2;i<N;i++) Y[i-N/2]=v[i];
    auto A=fsss2_sub(X);
    auto B=fsss2_sub(Y);
    int r=(int)B.size()-1;
    for(int l=0;l<(int)A.size();l++){
        while(r!=0&&A[l].first+B[r].first>S) r--;
        if(S==A[l].first+B[r].first){
            return A[l].second+(B[r].second<<(N/2));
        }
    }
    return -1;
}
}

// https://atcoder.jp/contests/abc326/submissions/47072566
void abc326f(){
    int N,X,Y;
    std::cin>>N>>X>>Y;
    std::vector<int> A(N),D(N+1),S={X,Y};
    for(int i=0;i<N;i++) std::cin>>A[i];
    for(int i=0;i<2;i++){
        std::vector<int> B((N+i)/2);
        for(int j=0;j<N;j++) if((i+j)&1){
            B[j>>1]=A[j]*2;
            S[i]+=A[j];
        }
        auto res=po167::fast_subset_sub_solver_2(B,S[i]);
        if(res==-1){
            std::cout<<"No\n";
            return;
        }
        for(int j=0;j<(N+i)/2;j++){
            if(res&(1ll<<j)) D[j*2+2-i]=i;
            else D[j*2+2-i]=i+2;
        }
    }
    std::cout<<"Yes\n";
    for(int i=0;i<N;i++){
        std::cout<<(((D[i+1]-D[i]+4)&2)?'R':'L');
    }
    std::cout<<'\n';
}
