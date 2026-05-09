// subset sum
// input vector<int> A, int B
// return t
// s.t : t[i] \in {0, 1}
// s.t : B = \sum A[i] * t[i]
// O(|A| \max(A))
std::vector<int> subset_sum(std::vector<int> A, int B){
    int ma = 0;
    int n = (int)A.size();
    for (auto a : A) ma = std::max(ma, a);
    int si = 0;
    while (si != n && B >= A[si]) B -= A[si++];
    if (si == n && B > 0) return {};
    std::vector dp(n - si + 1, std::vector<int>(ma * 2 + 1, -1));
    dp[0][B] = si;
    for (int i = 0; i < n - si; i++){
        // unuse left value
        for (int j = 0; j <= ma * 2; j++){
            for (int k = dp[i][j] - 1; k >= (i == 0 ? 0 : std::max(0, dp[i - 1][j])); k--){
                if (j + A[k] <= ma * 2){
                    dp[i][j + A[k]] = std::max(dp[i][j + A[k]], k);
                }
            }
        }
        // use A[i + si]
        dp[i + 1] = dp[i];
        for (int j = A[i + si]; j <= ma * 2; j++){
            dp[i + 1][j - A[i + si]] = std::max(dp[i + 1][j - A[i + si]], dp[i + 1][j]);
        }
    }
    if (dp[n - si][0] == -1) return {};
    std::vector<int> res(n);
    for (int i = 0; i < si; i++) res[i] = 1;
    int x = n - si, y = 0;
    while (x != 0 || y != B){
        int j = dp[x][y];
        if (j != si && A[j] <= y && dp[x][y - A[j]] > j){
            res[j] ^= 1;
            y -= A[j];
        }
        else{
            x--;
            if (dp[x][y] != j){
                res[x + si] ^= 1;
                y += A[x + si];
            }
        }
    }
    return res;
}