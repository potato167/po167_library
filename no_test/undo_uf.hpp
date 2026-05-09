namespace po167{
    struct UFtree_undo{
        int _n,ind;
        std::vector<int> wei;
        std::vector<int> q;
        int component;
        UFtree_undo(int n):_n(n),ind(0),wei(n),component(n),par(n){
            for(int i=0;i<n;i++){
                wei[i]=1,par[i]=i;
            }
        }
        int undo(){
            if(ind==0) return 0;
            component++;
            ind--;
            wei[par[q[ind]]]-=wei[q[ind]];
            par[q[ind]]=q[ind];
            return 1;
        }
        void rollback(int times){
            int tmp=1;
            while(tmp!=0&&times!=0){
                tmp=undo();
                times--;
            }
        }
        void intialize(){
            while(ind) undo();
        }
        //根っこを返す
        int root(int a){
            assert(0<=a&&a<_n);
            if(a==par[a]) return a;
            return root(par[a]);
        }
        //trueなら1,falseなら0
        int same(int a,int b){
            assert(0<=a&&a<_n);
            assert(0<=b&&b<_n);
            if(root(a)==root(b)) return 1;
            else return 0;
        }
        //a,bが違う根っこの元なら結合する,結合したらtrueを返す
        bool unite(int a,int b){
            a=root(a),b=root(b);
            if(a==b) return false;
            if(wei[a]<wei[b]) std::swap(a,b);
            par[b]=a;
            if(ind==(int)(q.size())) q.push_back(b);
            else q[ind]=b;
            ind++;
            wei[a]+=wei[b];
            component--;
            return true;
        }
        int size(int a){
            return wei[root(a)];
        }
    private:
        std::vector<int> par;
    };
}
using po167::UFtree_undo;
