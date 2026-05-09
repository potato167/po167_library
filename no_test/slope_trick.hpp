namespace po167{
    template<class T>
    struct slope_trick{
        std::priority_queue<T> left_pq;
        std::priority_queue<T,std::vector<T>,std::greater<T>> right_pq;
        T min_f;
        T add_l,add_r;
        slope_trick():min_f(0),add_l(0),add_r(0){};

        //f(x)=min(f(i)) i<=x
        void left_min(){
            right_pq={};
            add_r=0;
        }
        //f(x)=min(f(i)) i>=x
        void right_min(){
            left_pq={};
            add_l=0;
        }
        void add_constant_function(T d){
            min_f+=d;
        }
        //f(x)<- f(x)+max(x-a,0)
        void add_x_minus_a(T a){
            a-=add_l;
            if(!left_pq.empty()){
                min_f+=std::max(left_pq.top()-a,(T)0);
            }
            left_pq.push(a);
            right_pq.push(left_pq.top()+add_l-add_r);
            left_pq.pop();
        }

        //f(x) <- f(x)+max(a-x,0)
        void add_a_minus_x(T a){
            a-=add_r;
            if(!right_pq.empty()){
                min_f+=std::max(a-right_pq.top(),(T)0);
            }
            right_pq.push(a);
            left_pq.push(right_pq.top()+add_r-add_l);
            right_pq.pop();
        }

        //f(x) <- f(x) + |x-a|
        void add_abs_x_minus_a(T a){
            add_a_minus_x(a);
            add_x_minus_a(a);
        }

        //f(x) <- f(x-a)
        void shift(T a){
            add_l+=a;
            add_r+=a;
        }

        //f(x) <- min(f(x-i)) i= a~b
        //need: a<=b
        void sliding_min(T a,T b){
            assert(a<=b);
            add_l+=a;
            add_r+=b;
        }

        // return f(x)
        // O(|pq|)
        T get(T x){
            auto tmp = left_pq;
            T res = min_f;
            while (!tmp.empty()){
                res += std::max(T(0), tmp.top() + add_l - x);
                tmp.pop();
            }
            auto tmp2 = right_pq;
            while (!tmp2.empty()){
                res += std::max(T(0), x - tmp2.top() - add_r);
                tmp2.pop();
            }
            return res;
        }

        void merge_and_break(slope_trick &S){
            min_f+=S.min_f;
            T tmp;
            while(!S.left_pq.empty()){
                tmp=S.left_pq.top();
                S.left_pq.pop();
                add_a_minus_x(S.add_l+tmp);
            }
            while(!S.right_pq.empty()){
                tmp=S.right_pq.top();
                S.right_pq.pop();
                add_x_minus_a(S.add_r+tmp);
            }
        }
        void merge_and_remain(slope_trick S){
            merge_and_break(S);
        }
    };
}
using po167::slope_trick;
