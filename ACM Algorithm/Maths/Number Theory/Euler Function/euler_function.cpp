/*
    洛谷 P5091 【模板】扩展欧拉定理（求欧拉函数 phi(x)）
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 10000005;

/*
	扩展欧拉定理 x<eular(mod) x%=eular(mod) else x=eular(mod)+x%eular(mod);
*/
int p[MAXN], np[MAXN], phi[MAXN], cnt = 0;
inline void init() {
    // 筛出1-n内所有数的欧拉函数
    int n = MAXN - 2;
    phi[1] = np[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!np[i])
            phi[i] = i - 1, p[++cnt] = i;

        for (int j = 1; j <= cnt && (ll) i * p[j] <= n; j++) {
            np[i * p[j]] = 1;

            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }

            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
}
inline ll getPhi(ll x) {
    // 获得x的欧拉函数
    ll ans = x;

    for (int i = 2; (ll) i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0)
                x /= i;

            ans -= ans / i;
        }
    }

    if (x > 1)
        ans -= ans / x;

    return ans;
}
inline ll getPhi2(ll x) {
    // 需要事先筛出根号x内的质数
    ll ans = 1;

    for (int i = 1; p[i] <= x; i++) {
        if (!np[x])
            break;

        if (x % p[i] == 0) {
            ans *= p[i] - 1;
            x /= p[i];

            while (x % p[i] == 0) {
                x /= p[i];
                ans *= p[i];
            }
        }
    }

    if (x > 1)
        ans *= x - 1;

    return ans;
}
inline ll qpower(ll x, ll p, ll mod) {
    ll res = 1;

    while (p) {
        if (p & 1)
            res *= x, res %= mod;

        x *= x, x %= mod;
        p >>= 1;
    }

    return res % mod;
}

int main() {
    ll a, m;
    string b;
    cin >> a >> m >> b;
    ll phi = getPhi(m);
    int len = b.size();
    b = " " + b;
    ll p = 0;
    bool le = false;          // b >= phi(m) ?

    for (int i = 1; i <= len; i++) {
        p = p * 10 + b[i] - '0';

        if (p >= phi) {
            le = true;
            break;
        }
    }

    p = 0;

    for (int i = 1; i <= len; i++) {
        p = p * 10 + b[i] - '0';
        p %= phi;
    }

    p = le ? phi + p : p;

    cout << qpower(a, p, m) << "\n";

    return 0;
}

/*
2 7 4
2

998244353 12345 98765472103312450233333333333
5333
*/
