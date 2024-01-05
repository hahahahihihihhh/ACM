/*
    洛谷 P3807 【模板】卢卡斯定理（O(logp(n) * p)）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100005;

ll fac[MAXN], invfac[MAXN];

inline ll qpower(ll x, ll p, ll mod) {
    ll re = 1;

    while (p) {
        if (p & 1)
            re *= x, re %= mod;

        x *= x;
        x %= mod;
        p >>= 1;
    }

    return re;
}

inline void init(int p) {
    fac[0] = 1LL;

    for (int i = 1; i <= p - 1; i++)
        fac[i] = fac[i - 1] * i % p;

    invfac[p - 1] = qpower(fac[p - 1], p - 2, p);

    for (int i = p - 2; i >= 0; i--)
        invfac[i] = invfac[i + 1] * (i + 1) % p;
}

inline ll C(int n, int m, ll p) {
    if (n < m)
        return 0;

    return fac[n] * invfac[n - m] % p * invfac[m] % p;
}

ll lucas(ll n, ll m, ll p) {
    if (n < p && m < p)
        return C(n, m, p);

    return lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}

inline void solve() {
    ll n, m, p;
    cin >> n >> m >> p;
    init(p);
    cout << lucas(n + m, n, p) << "\n";
}

int main() {
    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}

/*
2
1 2 5
2 1 5
3
3
*/