/*
    洛谷 P4195 【模板】扩展BSGS/exBSGS
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<ll, ll> mp;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    //  ax + by = gcd(a,b) x 最小的特解 x1,y1
    if (!b) {
        x = 1, y = 0;
        d = a;
    } else {
        exgcd(b, a % b, d, y, x);
        y -= (a / b) * x;
    }
}

ll ask_inv(ll a, ll m) {
    // 扩展 gcd 求逆元 ：ax = 1(Mod m) -> ax + my = 1  ( gcd(a,m) = 1 )最小正整数解
    ll d, x, y;
    exgcd(a, m, d, x, y);
    return d == 1 ? (x + m) % m : -1;
}

inline ll qpower(ll x, ll p, ll mod) {
    ll res = 1;

    while (p) {
        if (p & 1)
            res *= x, res %= mod;

        p >>= 1;
        x *= x, x %= mod;
    }

    return res;
}

inline ll bsgs(ll a, ll b, ll p) {  // 给定整数a,b,p 其中 a,p 互质，求方程 a^x ≡ b (mod p) 的最小整数解 x
    mp.clear();
    a %= p, b %= p;
    ll m = ceil(sqrt(p));
    ll tmp = b;

    for (int j = 1; j <= m; j++) {
        tmp *= a, tmp %= p;
        mp[tmp] = j;
    }

    ll am = qpower(a, m, p);
    tmp = 1;

    for (int i = 1; i <= m; i++) {
        tmp *= am, tmp %= p;

        if (mp.count(tmp))
            return i * m - mp[tmp];
    }

    return -1;
}

inline ll exbsgs(ll a, ll b, ll p) {    // 给定整数a,b,p 求方程 a^x ≡ b (mod p) 的最小整数解 x
    a %= p, b %= p;

    if (b == 1 || p == 1)
        return 0;

    ll na = 1, g = __gcd(a, p), k = 0;

    while (g > 1) {
        if (b % g != 0)
            return -1;

        b /= g, p /= g;
        na *= a / g, na %= p;
        k++;

        if (na == b)
            return k;

        g = __gcd(a, p);
    }

    ll t = bsgs(a, b * ask_inv(na, p), p);

    if (t == -1)
        return -1;

    return k + t;
}

int main() {
    ll a, p, b;

    while (cin >> a >> p >> b) {
        if (!a)
            return 0;

        ll ans = exbsgs(a, b, p);

        if (~ans)
            cout << ans << "\n";
        else
            cout << "No Solution" << "\n";
    }

    return 0;
}

/*
5 58 33
2 4 3
0 0 0

9
No Solution
*/