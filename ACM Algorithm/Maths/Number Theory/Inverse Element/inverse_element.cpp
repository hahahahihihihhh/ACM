/*
    【模板】批量求逆元
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll fac[MAXN + 5];
ll facInv[MAXN + 5];
ll inv[MAXN + 5];

inline ll qpower(ll x, ll p, ll mod) {
    //快速幂
    ll re = 1LL;

    while (p) {
        if (p & 1)
            re = (re * x) % mod;

        x = (x * x) % mod;
        p >>= 1;
    }

    return re;
}

inline ll ask_invv(ll a) {
    //快速幂 求逆元
    return qpower(a, MOD - 2, MOD);
}
inline void build_facInv(int n) {
    //批量求逆：线性递推求阶乘逆元 1! —— n!
    fac[0] = fac[1] = 1LL;

    for (int i = 2; i <= n; i++)
        fac[i] = fac[i - 1] * i % MOD;

    facInv[n] = qpower(fac[n], MOD - 2, MOD);

    for (int i = n - 1; i >= 1; i--) {
        facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    }

    return;
}
inline void build_inv(int n) {
    //批量求逆：线性递推求逆元 1 —— min(MOD-1,n)（此方法仅适用于模数为素数的情况）
    inv[1] = 1LL;

    for (int i = 2; i <= MOD - 1 && i <= n; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD; // 此处乘法 注意规避爆int
    }
}

int main() {
    ll LIM = 100;
    build_facInv(LIM);
    build_inv(LIM);

    for (int i = 1; i <= LIM; i++)
        cout << "# " << i << "\t" << inv[i] << " " << ask_invv(i) << endl;

    return 0;
}