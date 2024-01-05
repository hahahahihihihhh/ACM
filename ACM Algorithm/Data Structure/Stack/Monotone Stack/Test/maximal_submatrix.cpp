/*
    hdu 2021"MINIEYE杯"中国大学生算法设计超级联赛1 H_Maximal-submatrix
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 2005;

int dpl[MAXN], dpr[MAXN];
int stk[MAXN], cnt = 0;
int mp[MAXN][MAXN], up[MAXN][MAXN];

inline void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m + 1; j++)
            up[i][j] = mp[i][j] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
            if (mp[i - 1][j] > mp[i][j])
                up[i][j] = 1;
            else
                up[i][j] = up[i - 1][j] + 1;
        }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        cnt = 0, stk[++cnt] = 0;
        for (int j = 1; j <= m; j++) {
            while (up[i][stk[cnt]] >= up[i][j])
                cnt--;
            dpl[j] = j - stk[cnt];
            stk[++cnt] = j;
        }
        cnt = 0, stk[++cnt] = m + 1;
        for (int j = m; j >= 1; j--) {
            while (up[i][stk[cnt]] >= up[i][j])
                cnt--;
            dpr[j] = stk[cnt] - j;
            stk[++cnt] = j;
        }
        for (int j = 1; j <= m; j++)
            ans = max(ans, (dpl[j] + dpr[j] - 1) * up[i][j]);
    }
    cout << ans << "\n";
    return;
}

int main() {
    closeSync;
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
1
2 3
1 2 4
2 3 3

4
*/