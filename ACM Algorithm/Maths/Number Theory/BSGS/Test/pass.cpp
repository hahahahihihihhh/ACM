/*
    hdu 2021“MINIEYE杯”中国大学生算法设计超级联赛(1) G_Pass!
*/
#include <bits/stdc++.h>

using namespace std;

#define closeSync ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
typedef long long ll;
const ll mod = 998244353;

unordered_map<ll, ll> mp;
ll n, x;

inline ll qpower(ll x, ll p, ll mod) {
    ll res = 1;
    while (p) {
        if (p & 1) res *= x, res %= mod;
        x *= x, x %= mod;
        p >>= 1;
    }
    return res;
}

inline ll bsgs(ll a, ll p) {
    if (((n * x % p - n + 1 + p) % p) == 1 || p == 1) return 0;
    mp.clear();
    int m = ceil(sqrt(p));
    a %= p;

    ll am = qpower(a, m, p), tmp = 1;
    for (int i = 1; i <= m; i++) {
        tmp *= am, tmp %= p;
        mp[tmp] = i;
    }

    ll tmp1 = (n * x + n - 1) % p, tmp2 = (n * x % p - n + 1 + p) % p;
    ll mn = 1e18;
    for (int j = 1; j <= m; j++) {
        tmp1 *= a, tmp1 %= p;
        tmp2 *= a, tmp2 %= p;
        if (mp.count(tmp1) && ((mp[tmp1] * m - j) & 1)) mn = min(mp[tmp1] * m - j, mn);
        if (mp.count(tmp2) && !((mp[tmp2] * m - j) & 1)) mn = min(mp[tmp2] * m - j, mn);
    }
    return mn == 1e18 ? -1 : mn;
}

inline void solve() {
    cin >> n >> x;
    cout << bsgs(n - 1, mod) << "\n";
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
5
11 1
11 0
11 10
11 76805204
11 2

0
1
2
233333
-1
*/