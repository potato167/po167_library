namespace po167{
std::random_device po_seed_gen;
std::mt19937 po_random_gen(po_seed_gen());
long long randLong(long long l = 0, long long r = (1ll << 62)){
    return std::uniform_int_distribution<long long>(l, r - 1)(po_random_gen);
}
template<class T>
std::vector<T> rand_vec(int sz, long long l =0, long long r = (1ll << 62)){
    std::vector<T> res(sz);
    for(auto &x: res) x = T(randLong(l, r));
    return res;
}

//https://ikatakos.com/pot/programming_algorithm/number_theory/barlekamp_massey
template<class T>
std::vector<T> Berlekamp_Massey(std::vector<T> s){
    std::vector<T> C={1}, B={1};
    int L = 0;
    int m = 1;
    T b = 1;
    for (int n = 0; n < int(s.size()); n++){
        T d = 0;
        for (int j = 0; j < L + 1; j++){
            d += C[j] * s[n - j];
        }
        if (d == 0){
            m++;
            continue;
        }
        T iv = d / b;
        if (2 * L <= n){
            auto tC = C;
            while (int(C.size()) <= n + 1 - L) C.push_back(0);
            for (int i = 0; i < int(B.size()); i++) C[i + m] -= iv * B[i];
            B = tC;
            L = n + 1 - L;
            b = d;
            m = 1;
        }
        else{
            for(int i = 0; i < int(B.size()); i++){
                C[i + m] -= iv * B[i];
            }
            m++;
        }
    }
    return C;
}

// https://nyaannyaan.github.io/library/matrix/black-box-linear-algebra.hpp

template<class T>
T det_sparse_matrix(std::vector<std::vector<T>> A, T mj = 0){
    int n = A.size();
    std::vector<T> D;
    struct pos_mat{
        int x;
        int y;
        T val;
    };
    std::vector<pos_mat> p;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) if (A[i][j] != mj) {
            p.push_back({i, j, A[i][j] - mj});
        }
    }
    while (true){
        while (true){
            D = rand_vec<T>(n);
            bool ok = 1;
            for (auto x: D) if (x == 0) ok = 0;
            if (ok) break;
        }
        std::vector<pos_mat> AD = p;
        for (int i = 0; i < int(AD.size()); i++) AD[i].val *= D[AD[i].y];
        std::vector<T> u = rand_vec<T>(n), v = rand_vec<T>(n);
        std::vector<T> b(n);
        std::vector<T> a(2 * n + 1);
        b = u;
        for (int  i = 0; i < 2 * n + 1; i++){
            T sum = 0;
            for (int j = 0; j < n; j++){
                sum += u[j] * D[j];
                a[i] += u[j] * v[j];
            }
            sum *= mj;
            for (int j = 0; j < n; j++){
                u[j] = sum;
            }
            for (pos_mat tmp: AD){
                u[tmp.x] += tmp.val * b[tmp.y]; 
            }
            b = u;
        }
        auto mp = Berlekamp_Massey(a);
        if (mp.back() == 0) return 0;
        if (int(mp.size()) != n + 1) continue;
        T res = mp.back();
        if (n & 1) res *= -1;
        T tmp = 1;
        for (auto d: D) tmp *= d;
        return res / tmp;
    }
}
}
