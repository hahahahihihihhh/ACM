/*
    洛谷 P1191 矩形 （单调栈优化dp，统计白色矩形数）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const int MAXN = 5005;

int mp[MAXN][MAXN];
int dp[MAXN][MAXN];
int s[MAXN], cnt = 0;

inline void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            mp[i][j] = (c == 'W');
        }

    for (int i = 1; i <= n; i++) // 向上延伸多少
        for (int j = 1; j <= n; j++)
            if (mp[i][j])
                mp[i][j] = mp[i - 1][j] + 1;

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        s[1] = n + 1, cnt = 1;
        for (int j = n; j >= 1; j--) {
            while (mp[i][s[cnt]] > mp[i][j])
                cnt--;
            dp[i][j] = mp[i][j] * (s[cnt] - j) + dp[i][s[cnt]];
            s[++cnt] = j;
            ans += dp[i][j];
        }
    }
    cout << ans << "\n";

    return;
}

int main() {
    closeSync;
    // int T;  cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
4
WWBW
BBWB
WBWW
WBWB

15
*/