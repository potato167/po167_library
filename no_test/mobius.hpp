//Mobius(n)= 0  exists p n|p*p
//         =-1  if n=p_1*p_2*...*p_{2a+1}
//         = 1  if n=p_1*p_2*...*p_{2a}
std::vector<int> Mobius(int N){
    std::vector<int> p(N+1,-2);
    p[1]=1;
    for(int i=2;i<=N;i++){
        if(p[i]!=-2) continue;
        p[i]=-1;
        for(int j=i*2;j<=N;j+=i){
            if(p[j]==-2) p[j]=-1;
            else p[j]*=-1;
        }
        if(N/i<i) continue;
        for(int j=i*i;j<=N;j+=i*i) p[j]=0;
    }
    for(int i=1;i<=N;i++){
        if(p[i]==-2) p[i]=-1;
    }
    return p;
}
