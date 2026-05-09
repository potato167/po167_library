vector<ll> candy(vector<ll> v, int K){
    int N = v.size();
    vector<int> L(N), R(N);
    rep(i, 0, N) L[i] = i - 1, R[i] = i + 1;
    auto del = [&](int ind) -> void {
        if (ind == -1 || ind == N) return;
        if (L[ind] == -1){
            if (R[ind] != N) L[R[ind]] = -1;
        }
        else{
            if (R[ind] == N) R[L[ind]] = N;
            else{
                int l = L[ind];
                int r = R[ind];
                R[l] = r;
                L[r] = l;
            }
        }
        R[ind] = -1;
    };
    vector<ll> ans = {0};
    priority_queue<pair<ll, int>> pq;
    rep(i, 0, N) pq.push({v[i], i});
    rep(rp, 0, (N + 1) / 2){
    	if ((int)ans.size() > K) break;
        while (true){
            auto [val, ind] = pq.top();
            pq.pop();
            if (R[ind] == -1 || v[ind] != val){
                continue;
            }
            ans.push_back(ans.back() + val);
            int l = L[ind];
            int r = R[ind];
            del(ind);
            if (l == -1 || r == N){
                del(l), del(r);
            }
            else{
                del(r);
                v[l] = v[l] - v[ind] + v[r];
                pq.push({v[l], l});
            }
            break;
        }
    }
    return ans;
}