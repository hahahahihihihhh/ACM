/*
	洛谷 P3195 [HNOI2008]玩具装箱（斜率优化dp模板）
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MAXN = 400005;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
const ll INF = 1e18;

ll sum[MAXN], a[MAXN], b[MAXN];
ll L;
ll dp[MAXN];

inline ll sqr(ll x) { return x * x; }

inline ll Y(int j) { return dp[j] + sqr(b[j]); }

inline ll X(int j) { return b[j]; }

inline ll k(int i) { return 2LL * a[i]; }

inline ld slope(int i, int j) { return (ld) (Y(j) - Y(i)) / (X(j) - X(i)); }     // 斜率

int Q[MAXN];

inline void solve() {
    int n;
    cin >> n >> L;
    b[0] = 1 + L;
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] = sum[i - 1] + sum[i];
        a[i] = i + sum[i];
        b[i] = i + 1 + sum[i] + L;
    }

    int head = 1, tail = 1;    // 左闭 右闭
    for (int i = 1; i <= n; i++) {
        while (head < tail && slope(Q[head], Q[head + 1]) < k(i))    // 决策单调性 （线性规划）
            head++;
        int j = Q[head];
        dp[i] = dp[j] + sqr(a[i] - b[j]);
        while (head < tail && slope(i, Q[tail - 1]) < slope(Q[tail], Q[tail - 1]))    // 下凸包优化
            tail--;
        Q[++tail] = i;
    }
    cout << dp[n] << "\n";
    return;
}

int main() {
    closeSync;

    solve();

    return 0;
}

/*
5 4
3
4
2
1
4

1
*/