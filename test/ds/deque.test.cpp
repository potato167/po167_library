#define PROBLEM "https://yukicoder.me/problems/no/3199"


#include "../../ds/Deque.hpp"

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
const int INF = 2100000000;
template<class T> bool chmin(T &a, T b){return (a > b ? a = b, 1 : 0);}

void solve();
// POP'N ROLL MUSIC / TOMOO
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    rep(i, 0, t) solve();
}

void solve(){
    int H, W, M;
    cin >> H >> W >> M;
    vector<string> S(H);
    rep(i, 0, H) cin >> S[i];
    int sx, sy, gx, gy;
    rep(i, 0, H) rep(j, 0, W){
            if (S[i][j] == 'S') sx = i, sy = j;
            if (S[i][j] == 'G') gx = i, gy = j;
        }
    vector dp(M + 1, vector(H, vector<int>(W, INF)));
    po167::Deque<tuple<int, int, int>> q;
    q.push_back({0, sx, sy});
    dp[0][sx][sy] = 0;
    vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
    while (!q.empty()){
        auto [c, x, y] = q.front();
        q.pop_front();
        if ('1' <= S[x][y] && S[x][y] <= '9' && S[x][y] != (char)('0' + c)){
            int d = S[x][y] - '0';
            if (dp[d][x][y] == INF){
                dp[d][x][y] = dp[c][x][y];
                q.push_front({d, x, y});
            }
            continue;
        }
        if ('a' <= S[x][y] && S[x][y] <= 'z' && S[x][y] != (char)('a' + c - 1)) continue;
        rep(k, 0, 4){
            int s = dx[k] + x;
            int t = dy[k] + y;
            if (s < 0 || H <= s || t < 0 || W <= t) continue;
            if (S[s][t] == '#') continue;
            if (chmin(dp[c][s][t], dp[c][x][y] + 1)){
                q.push_back({c, s, t});
                continue;
            }
        }
    }
    int ans = INF;
    rep(i, 0, M + 1) chmin(ans, dp[i][gx][gy]);
    if (ans == INF) ans = -1;
    cout << ans << "\n";
}
