/*
    洛谷 P1433 吃奶酪
*/
#include <bits/stdc++.h>

using namespace std;

double x[20], y[20], f[20][35000];
const int INF = 127;

double dis(int a, int b) {
    return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}

inline void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    memset(f, 127, sizeof(f));
    for (int s = 1; s <= (1 << n) - 1; s++)            //遍历全集合
        for (int i = 1; i <= n; i++)                   //从 i 点出发遍历 空集-全集 (前提：i在集合s里)
        {
            if ((s & (1 << (i - 1))) == 0) continue;     //i点不在集合里
            if (s == (1 << (i - 1))) {
                f[i][s] = 0;
                continue;
            }     //s集合就只有i
            for (int j = 1; j <= n; j++)                   //枚举集合里面的j（j！=i）点来试图更新 i出发遍历集合s的点的最小距离
            {
                if ((s & (1 << (j - 1))) == 0 || i == j) continue;   //集合内不是i的j
                f[i][s] = min(f[i][s], f[j][s - (1 << (i - 1))] + dis(i, j));       //点 j 出发到不包含点i的集合s的最短距离+上 i与j的最短距离
            }
        }
    double ans = -1;
    for (int i = 1; i <= n; i++) {
        double s = f[i][(1 << n) - 1] + dis(i, 0);           //加上出发点后找最短距离
        if (ans == -1 || ans > s) ans = s;
    }
    cout << fixed << setprecision(2) << ans << "\n";
    return;
}

int main() {
    solve();
    return 0;
}

/*
4
1 1
1 -1
-1 1
-1 -1

7.41
*/