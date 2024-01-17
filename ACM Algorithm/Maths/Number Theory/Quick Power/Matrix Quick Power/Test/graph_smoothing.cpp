/*
    Atcoder abc199 F_Graph-Smoothing
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const ll MOD = 1e9 + 7;
const int MAXN = 105;

int n, m, k;
ll A[MAXN], B[MAXN], down = 1;
ll mp[MAXN][MAXN];

struct Mat {
    ll a[MAXN][MAXN];
    int n;

    Mat(int _n = 0) {
        n = _n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = 0;
    }

    Mat operator*(const Mat &x) const {
        Mat res(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    res.a[i][j] += a[i][k] * x.a[k][j], res.a[i][j] %= MOD;
        return res;
    }

    void ones() {
        for (int i = 1; i <= n; i++) a[i][i] = 1;
    }
};

inline Mat mpower(Mat x, ll p) {
    Mat res(n);
    res.ones();
    while (p) {
        if (p & 1) res = res * x;
        p >>= 1;
        x = x * x;
    }
    return res;
}

inline ll qpower(ll x, ll p, ll mod) {
    ll res = 1;
    while (p) {
        if (p & 1) res *= x, res %= mod;
        p >>= 1;
        x *= x;
        x %= mod;
    }
    return res;
}

inline void solve() {
    cin >> n >> m >> k;
    Mat help(n);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        mp[u][v] = mp[v][u] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (mp[i][j]) cnt++, help.a[i][j]++, help.a[i][i]++;
        help.a[i][i] += ((m - cnt) << 1);
    }

    Mat tmp = mpower(help, k);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            B[i] += tmp.a[i][j] * A[j], B[i] %= MOD;

    down *= (qpower(2LL, k, MOD) * qpower(m, k, MOD) % MOD);
    down %= MOD;
    for (int i = 1; i <= n; i++)
        cout << (B[i] * qpower(down, MOD - 2, MOD) % MOD) << "\n";
}

int main() {
    closeSync;
    // int T;
    // cin >> T;
    // while (T--)
    solve();
    return 0;
}

/*
3 2 2
12 48 36
1 2
1 3

750000036   
36          
250000031
*/