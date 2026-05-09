namespace po167{
// min sum_{i} digit_sum(A[i]+x) (base D)
// st 0<=x,A[i]
//    D>=2
// O(ND log_{D}{max(A)}) ?
// arc153_d
using ans_ty=long long;
template<const int D,class F>
ans_ty Minimize_sum_of_digit_sums(
    std::vector<F> A
){
    const ans_ty INF_=1e15;
    int N=A.size();
    std::vector<ans_ty> res(N+1,INF_),n_res(N+1);
    std::vector<F> n_A(N);
    std::vector<int> rem(N);
    res[0]=0;
    bool ok=1;
    while(ok){
        ok=0;
        int ind=0;
        ans_ty val=0;
        for(int i=0;i<N;i++){
            if(A[i]) ok=1;
            rem[i]=D-1-A[i]%D;
            A[i]/=D;
            val+=D-1-rem[i];
        }
        n_res[0]=INF_;
        for(int c=0;c<D;c++){
            n_res[ind]=std::min(n_res[ind],val+res[0]);
            for(int i=0;i<N;i++){
                if(rem[i]==c){
                    val-=D;
                    n_A[ind]=A[i];
                    ind++;
                    n_res[ind]=INF_;
                }
                val++;
                n_res[ind]=std::min(n_res[ind],val+res[i+1]);
            }
        }
        std::swap(n_A,A);
        std::swap(n_res,res);
    }
    return res[0];
}
}
/*
//https://atcoder.jp/contests/arc153/tasks/arc153_d
void arc153d(){
    int N;
    std::cin>>N;
    std::vector<int> A(N);
    for(int i=0;i<N;i++) std::cin>>A[i];
    std::cout<<po167::Minimize_sum_of_digit_sums<10>(A)<<"\n";
}
*/

/*
// Div1 572 D
//https://codeforces.com/contest/1188/problem/D
void div1_572_D(){
    int N;
    std::cin>>N;
    std::vector<long long> A(N);
    long long M=0;
    for(int i=0;i<N;i++) std::cin>>A[i],M=std::max(M,A[i]);
    for(int i=0;i<N;i++) A[i]=M-A[i];
    std::cout<<po167::Minimize_sum_of_digit_sums<2>(A)<<"\n";
}
*/