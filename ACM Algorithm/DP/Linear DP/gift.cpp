/*
    牛客 第45届国际大学生程序设计竞赛亚洲区域赛（昆明） G_Gift
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int N = 505;  // 人数
const int M = 20;  // 礼物
const int D = 370; // 天数
const int INF = 0x3f3f3f3f;

namespace io {
const int L = (1 << 22) | 1;
char ibuf[L], *iS, *iT, c;
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, L, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
template<class I>
inline void gi(I &x) {
    for (c = gc(); c < '0' || c > '9'; c = gc());
    for (x = 0; c >= '0' && c <= '9'; c = gc())
        x = x * 10 + (c & 15);
}
}
using io::gi;

struct Per {
    int bir;
    int cday;
    int imp;
    bool operator<(const Per &x) const {
        return bir < x.bir;
    }
} p[N];

int mon[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int c[N], v[N], a[M], b[M];
int dp[D][N][M];
int g[M];

inline bool isleapyear(int year) {
    return year % 4 == 0;
}

inline int daysg(int month, int day) {
    int sum = 0;
    for (int i = 1; i < month; i++)
        sum += mon[i];
    sum += day;
    return sum;
}

inline void solve() {
    int n, m, w;
    gi(n);
    gi(m);
    gi(w);
    int year, month, day;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        gi(year);
        gi(month);
        gi(day);
        gi(c[i]);
        gi(v[i]);
        if (isleapyear(year) && month == 2 && day == 29)
            continue;
        p[++cnt] = {daysg(month, day), c[i], v[i]};
    }
    n = cnt;

    for (int i = 1; i <= m; i++)
        gi(a[i]), gi(b[i]);

    sort(p + 1, p + n + 1);

    memset(g, 0, sizeof(g));
    for (int i = 0; i < (1 << m); i++) {// 二进制枚举买了哪些礼物
        int cnt = 0, sum = 0, cst = 0;
        for (int j = 1; j <= m; j++)
            if ((i >> (j - 1)) & 1)
                sum += b[j], cst += a[j], cnt++;
        if (cst <= w)
            g[cnt] = max(g[cnt], sum);
    }

    for (int i = 0; i <= 365; i++)
        for (int j = 0; j <= n; j++) {
            for (int k = 1; k <= m; k++)
                dp[i][j][k] = -INF;
            dp[i][j][0] = 0;
        }

    for (int i = 1; i <= 365; i++) {// 前 i 天
        for (int j = 1; j <= n; j++) {// 为前 j 个人
            for (int k = 0; k <= min(j, m); k++) {// 剩下 >= k个人没做蛋糕   (不是所有没给他做蛋糕的人都能收到礼物)
                dp[i][j][k] = max(dp[i][j - 1][k], dp[i - 1][j][k]); //不给 j 做
                if (k) dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1]);
                if (i - p[j].cday >= 0 && p[j].bir >= i) // 给 j 做
                    dp[i][j][k] = max(dp[i - p[j].cday][j - 1][k] + p[j].imp, dp[i][j][k]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= min(m, n); i++)
        ans = max(ans, g[i] + dp[365][n][i]);

    printf("%d\n", ans);

    return;
}

int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

/*
1
2 2 100
2000-01-01 10 13
2000-12-31 30 92
99 46
2 2

138
*/

/*
2
2 2 100
2000-01-01 10 13
2000-12-31 30 92
99 46
2 2
2 2 100
2004-02-28 10 30
2001-10-31 20 10
10 1000000
1 1000

138
1001000
*/